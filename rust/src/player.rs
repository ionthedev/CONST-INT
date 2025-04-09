use std::f32::INFINITY;
use std::f64::MIN;
use std::ops::Mul;
use std::str;

use godot::classes::character_body_3d::MotionMode;
use godot::classes::input::MouseMode;
use godot::classes::{
    Camera3D, CapsuleMesh, CapsuleShape3D, CharacterBody3D, CollisionShape3D, Engine,
    ICharacterBody3D, Input, InputEvent, InputEventMouseButton, InputEventMouseMotion,
    MeshInstance3D, ProjectSettings, RayCast3D,
};
use godot::global::deg_to_rad;
use godot::prelude::*;

use crate::air_movement_settings::AirMovementSettings;
use crate::ground_movement_settings::{self, GroundMovementSettings};
use crate::juice_settings::JuiceSettings;

#[derive(GodotClass)]
#[class(tool, base=CharacterBody3D)]
pub struct Player {
    base: Base<CharacterBody3D>,

    // Settings
    #[export]
    ground_settings: Option<Gd<GroundMovementSettings>>,
    #[export]
    air_settings: Option<Gd<AirMovementSettings>>,
    #[export]
    juice_settings: Option<Gd<JuiceSettings>>,
    #[export]
    gravity: f32,
    #[export]
    look_sensitivity: f32,

    // Movement state
    #[export]
    curr_speed: f32,
    input_dir: Vector2,
    wish_dir: Vector3,
    cam_aligned_wish_dir: Vector3,
    last_frame_grounded: u64,

    // Player state
    noclip: bool,
    crouched: bool,
    noclip_speed_mult: f32,
    snapped_stair_last_frame: bool,
    original_height: f32,
    was_on_floor: bool,

    // Node references
    #[var]
    pub stairs_ahead_raycast: Option<Gd<RayCast3D>>,
    head: Option<Gd<Node3D>>,
    lean_pivot: Option<Gd<Node3D>>,
    head_pivot: Option<Gd<Node3D>>,
    eyes: Option<Gd<Node3D>>,
    camera: Option<Gd<Camera3D>>,
    collision: Option<Gd<CollisionShape3D>>,
    skin: Option<Gd<MeshInstance3D>>,
}

#[godot_api]
impl ICharacterBody3D for Player {
    fn init(base: Base<CharacterBody3D>) -> Self {
        godot_print!("[CONST-INT] Initializing Player Class");

        Self {
            base,
            ground_settings: None,
            air_settings: None,
            juice_settings: None,
            stairs_ahead_raycast: None,
            curr_speed: 0.0,
            input_dir: Vector2::default(),
            wish_dir: Vector3::default(),
            cam_aligned_wish_dir: Vector3::default(),
            snapped_stair_last_frame: false,
            last_frame_grounded: 0,
            noclip: false,
            crouched: false,
            noclip_speed_mult: 0.0,
            camera: None,
            collision: None,
            eyes: None,
            head: None,
            head_pivot: None,
            lean_pivot: None,
            original_height: 1.75,
            skin: None,
            gravity: -9.75,
            look_sensitivity: 0.006,
            was_on_floor: true,
        }
    }

    fn ready(&mut self) {
        godot_print!("Player ready function called");

        // Create default settings if none are set
        if self.ground_settings.is_none() {
            self.ground_settings = Some(Gd::<GroundMovementSettings>::default());
        }
        if self.air_settings.is_none() {
            self.air_settings = Some(Gd::<AirMovementSettings>::default());
        }
        if self.juice_settings.is_none() {
            self.juice_settings = Some(Gd::<JuiceSettings>::default());
        }
        if self.stairs_ahead_raycast.is_none() {
            self.make_step_ahead_ray();
        }
        self.make_children();
        self.was_on_floor = false;
    }

    fn physics_process(&mut self, delta: f64) {
        if Engine::singleton().is_editor_hint() {
            return;
        }

        self.wish_dir = self.calc_wish_dir();

        self.handle_movement(delta);
        self.base_mut().move_and_slide();
    }

    fn unhandled_input(&mut self, event: Gd<InputEvent>) {
        let sens = self.get_look_sensitivity();
        let cam = self.camera.clone();

        // Make a clone of the event for each type check
        let event_for_button = event.clone();
        let event_for_motion = event.clone();

        // Now we can use try_cast on each copy
        if event_for_button.try_cast::<InputEventMouseButton>().is_ok() {
            Input::singleton().set_mouse_mode(MouseMode::CAPTURED);
        } else if Input::singleton().is_action_pressed("ui_cancel") {
            Input::singleton().set_mouse_mode(MouseMode::VISIBLE);
        }

        // Check if mouse is captured and event is mouse motion
        if Input::singleton().get_mouse_mode() == MouseMode::CAPTURED {
            if let Ok(motion_event) = event_for_motion.try_cast::<InputEventMouseMotion>() {
                let relative = motion_event.get_relative();
                self.base_mut().rotate_y(-relative.x * sens);

                // Get camera node and rotate it
                if let Some(mut camera) = cam {
                    camera.rotate_x(-relative.y * self.look_sensitivity);

                    // Clamp the camera rotation
                    let mut rotation = camera.get_rotation();
                    rotation.x = rotation
                        .x
                        .clamp((deg_to_rad(-90.0) as f32), (deg_to_rad(90.0) as f32));
                    camera.set_rotation(rotation);
                }
            }
        }
    }
}

#[godot_api]
impl Player {
    // Node setup functions
    #[func]
    fn make_step_ahead_ray(&mut self) {
        if self.stairs_ahead_raycast.is_some() {
            return;
        }
        godot_print!("Starting to create raycast...");
        let mut ray = RayCast3D::new_alloc();
        godot_print!("RayCast3D allocated");

        ray.set_target_position(Vector3::new(0.0, 0.0, 1.0));
        ray.set_enabled(true);
        ray.set_collision_mask(1);
        ray.set_debug_shape_thickness(5);
        ray.set_debug_shape_custom_color(Color::from_rgb(1.0, 0.0, 0.0));
        ray.set_name("StairsAheadRaycast");
        godot_print!("RayCast3D configured with name: {}", ray.get_name());

        self.base_mut().add_child(&ray.clone());
        godot_print!("RayCast3D added as child");

        self.stairs_ahead_raycast = Some(ray);
        godot_print!("RayCast3D stored in stairs_ahead_raycast");

        if let Some(ray_ref) = &self.stairs_ahead_raycast {
            godot_print!(
                "Created raycast with position: {:?}",
                ray_ref.get_target_position()
            );
        }
    }

    pub fn make_children(&mut self) {
        if !Engine::singleton().is_editor_hint() {
            // Make Head Nodes
            let mut _head = Node3D::new_alloc();
            let mut _h_pivot = Node3D::new_alloc();
            let mut _l_pivot = Node3D::new_alloc();
            let mut _eyes = Node3D::new_alloc();

            _l_pivot.add_child(&_h_pivot);
            _h_pivot.add_child(&_head);
            _head.add_child(&_eyes);

            // Make camera
            let mut _cam = Camera3D::new_alloc();
            _eyes.add_child(&_cam);

            // Add tree to character
            self.base_mut().add_child(&_l_pivot);

            // Position head pivot
            _h_pivot.set_position(Vector3 {
                x: 0.0,
                y: 1.5,
                z: 0.0,
            });

            self.lean_pivot = Some(_l_pivot);
            self.head_pivot = Some(_h_pivot);
            self.head = Some(_head);
            self.eyes = Some(_eyes);
            self.camera = Some(_cam);
        }

        // Make capsule
        let mut _skin = MeshInstance3D::new_alloc();
        let mut _capsule_m = CapsuleMesh::new_gd();
        _skin.set_mesh(&_capsule_m);
        self.base_mut().add_child(&_skin);
        _skin.set_position(Vector3 {
            x: 0.0,
            y: 1.0,
            z: 0.0,
        });

        // Make collision
        let mut _col = CollisionShape3D::new_alloc();
        let mut _col_shape = CapsuleShape3D::new_gd();
        _col_shape.set_height(self.original_height);
        _col_shape.set_radius(0.4);
        _col.set_shape(&_col_shape);
        self.base_mut().add_child(&_col);

        self.collision = Some(_col);
        self.skin = Some(_skin);
    }

    // Input handling functions

    #[func]
    pub fn calc_input_dir(&mut self) -> Vector2 {
        if Engine::singleton().is_editor_hint() {
            return Vector2::default();
        }
        let input = Input::singleton();

        let dir = input.get_vector("Left", "Right", "Backward", "Forward");
        if dir != Vector2::ZERO {
            return dir.normalized();
        } else {
            return Vector2::ZERO;
        }
    }

    #[func]
    pub fn calc_wish_dir(&mut self) -> Vector3 {
        if Engine::singleton().is_editor_hint() {
            return Vector3::ZERO;
        }
        if self.calc_input_dir() != Vector2::ZERO {
            return self.base().get_global_transform().basis
                * Vector3::new(self.calc_input_dir().x, 0.0, -self.calc_input_dir().y);
        } else {
            return Vector3::ZERO;
        }
    }

    // Physics handling functions
    fn handle_movement(&mut self, delta: f64) {
        if self.ground_settings.is_none() || self.air_settings.is_none() {
            return;
        }

        let ground_settings = self.ground_settings.as_ref().unwrap().clone();
        let air_settings = self.air_settings.as_ref().unwrap().clone();

        if self.base().is_on_floor() {
            // When on ground, explicitly set current speed to ground values
            if Input::singleton().is_action_pressed("Sprint") {
                self.curr_speed = ground_settings.bind().get_sprint_speed();
            } else {
                self.curr_speed = ground_settings.bind().get_walk_speed();
            }

            // Handle jumping
            if Input::singleton().is_action_pressed("Jump") {
                let mut jump_v = self.base().get_velocity();
                jump_v.y = ground_settings.bind().jump_velocity;
                self.base_mut().set_velocity(jump_v);
            }

            self.handle_ground_physics(ground_settings.clone(), air_settings.clone(), delta);
        } else {
            // When in air, explicitly set current speed to air value
            self.curr_speed = air_settings.bind().get_speed();
            self.handle_air_physics(air_settings.clone(), delta);
        }
    }

    pub fn handle_ground_physics(
        &mut self,
        ground_settings: Gd<GroundMovementSettings>,
        air_settings: Gd<AirMovementSettings>,
        delta: f64,
    ) {
        // Continue with the regular ground physics...
        let mut v = self.base().get_velocity();

        // Update current speed based on input

        // Get all needed parameters
        let curr_speed = self.curr_speed;
        let deceleration = ground_settings.bind().get_deceleration();
        let friction = ground_settings.bind().get_friction();
        let acceleration = ground_settings.bind().get_acceleration();

        // Get current velocity properties
        let player_velocity_length = v.length();

        // Handle stopping when no input
        if self.wish_dir.length_squared() < 0.01 {
            // Apply strong damping to quickly stop movement when no input
            v *= (1.0 - (friction * 10.0 * delta as f32)).max(0.0);
        } else {
            // Apply friction first
            let control = f32::max(player_velocity_length, deceleration);
            let drop = control * friction * (delta as f32);
            let new_speed = f32::max(player_velocity_length - drop, 0.0);

            // Scale velocity by friction effect
            if player_velocity_length > 0.01 {
                // Avoid division by very small numbers
                v *= new_speed / player_velocity_length;
            }

            // Then add acceleration in wish direction
            let cur_speed_in_wish_dir: f32 = v.dot(self.wish_dir);
            let add_speed_til_cap: f32 = curr_speed - cur_speed_in_wish_dir;

            if add_speed_til_cap > 0.0 {
                let accel_speed: f32 = f32::min(
                    acceleration * self.curr_speed * (delta as f32),
                    add_speed_til_cap,
                );
                v += self.wish_dir * accel_speed;
            }
        }

        // Apply final velocity
        self.update_player_velocity(v);
        self.headbob_effect(delta);
    }

    fn handle_air_physics(&mut self, air_settings: Gd<AirMovementSettings>, delta: f64) {
        // Get the current velocity
        let mut velocity = self.base().get_velocity();

        // Get the gravity value from project settings
        let gravity_variant =
            ProjectSettings::singleton().get_setting("physics/3d/default_gravity");

        // Use try_to to convert the Variant to f32
        let gravity: f32 = match gravity_variant.try_to::<f32>() {
            Ok(value) => value,
            Err(_) => 9.8, // Default fallback value if conversion fails
        };

        // Apply gravity
        velocity.y -= gravity * delta as f32;

        let cur_speed_in_wish_dir: f32 = velocity.dot(self.wish_dir);
        let capped_speed: f32 = f32::min(
            (air_settings.bind().speed * self.wish_dir).length(),
            air_settings.bind().airCap,
        );

        let air_speed_til_cap: f32 = capped_speed - cur_speed_in_wish_dir;
        if air_speed_til_cap > 0.0 {
            let mut accel_speed: f32 =
                (air_settings.bind().acceleration * air_settings.bind().speed) * (delta as f32);
            accel_speed = f32::min(accel_speed, air_speed_til_cap);
            velocity += accel_speed * self.wish_dir;
        }
        if self.base().is_on_wall() {
            if self.is_surface_too_steep(self.base().get_wall_normal()) {
                self.base_mut().set_motion_mode(MotionMode::FLOATING);
            } else {
                self.base_mut().set_motion_mode(MotionMode::GROUNDED);
            }
        }

        // Update the velocity
        self.update_player_velocity(velocity);
    }

    fn is_surface_too_steep(&mut self, normal: Vector3) -> bool {
        let max_slope_angle_dot: f32 = Vector3::new(0.0, 1.0, 0.0)
            .rotated(
                Vector3::new(1.0, 0.0, 0.0),
                self.base().get_floor_max_angle(),
            )
            .dot(Vector3::new(0.0, 1.0, 0.0));

        if normal.dot(Vector3::new(0.0, 1.0, 0.0)) < max_slope_angle_dot {
            return true;
        }
        false
    }

    fn apply_gravity(&mut self) {
        if !self.base().is_on_floor() {
            let mut v = self.base().get_velocity();
            v.y -= self.gravity * 0.016; // Apply gravity (using default delta if needed)
            self.update_player_velocity(v);
        }
    }

    // Helper functions
    fn update_player_velocity(&mut self, new_velocity: Vector3) {
        self.base_mut().set_velocity(new_velocity);
    }

    fn headbob_effect(&mut self, delta: f64) {
        let mut juice_settings = self.juice_settings.as_ref().unwrap().clone();
        let v = self.base().get_velocity().clone();
        let cam = self.camera.clone();
        let previous_y: f32 = f32::sin(
            (juice_settings.bind().headbob_time
                - (delta as f32) * juice_settings.bind().get_headbob_move_amount()),
        );

        juice_settings.bind_mut().headbob_time += (delta as f32) * v.length();
        let current_y: f32 = f32::sin(
            juice_settings.bind().headbob_time * juice_settings.bind().get_headbob_move_freq(),
        ) * juice_settings.bind().get_headbob_move_amount();

        let cam_pos: Vector3 = Vector3::new(
            f32::cos(
                juice_settings.bind().headbob_time
                    * juice_settings.bind().get_headbob_move_freq()
                    * 0.5,
            ) * juice_settings.bind().get_headbob_move_amount(),
            current_y,
            0.0,
        );

        if let Some(mut camera) = cam {
            camera.set_position(cam_pos);
        }

        if previous_y < 0.0 && current_y > 0.0 { //play footstep sound
        }
    }
}
