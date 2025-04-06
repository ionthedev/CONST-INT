use std::f32::INFINITY;

use crate::air_movement_settings::AirMovementSettings;
use crate::ground_movement_settings::GroundMovementSettings;
use crate::juice_settings::JuiceSettings;
use godot::classes::{
    Camera3D, CapsuleMesh, CapsuleShape3D, CharacterBody3D, CollisionShape3D, Engine,
    ICharacterBody3D, Input, MeshInstance3D, RayCast3D,
};
use godot::prelude::*;

#[derive(GodotClass)]
#[class(tool, base=CharacterBody3D)]
pub struct Player {
    base: Base<CharacterBody3D>,

    // Instead of using Gd<GroundMovementSettings> directly as an export
    #[export]
    ground_settings: Option<Gd<GroundMovementSettings>>,
    #[export]
    air_settings: Option<Gd<AirMovementSettings>>,
    #[export]
    juice_settings: Option<Gd<JuiceSettings>>,
    #[var]
    pub stairs_ahead_raycast: Option<Gd<RayCast3D>>,

    curr_speed: f32,
    input_dir: Vector2,
    wish_dir: Vector3,
    cam_aligned_wish_dir: Vector3,
    snapped_stair_last_frame: bool,
    last_frame_grounded: u64,
    noclip: bool,
    crouched: bool,
    noclip_speed_mult: f32,
    head: Option<Gd<Node3D>>,
    lean_pivot: Option<Gd<Node3D>>,
    head_pivot: Option<Gd<Node3D>>,
    eyes: Option<Gd<Node3D>>,
    camera: Option<Gd<Camera3D>>,
    collision: Option<Gd<CollisionShape3D>>,
    original_height: f32,
    skin: Option<Gd<MeshInstance3D>>,
}

#[godot_api]
impl Player {
    #[func]
    fn make_step_ahead_ray(&mut self) {
        if self.stairs_ahead_raycast.is_some() {
            return;
        }
        godot_print!("Starting to create raycast...");
        let mut ray = RayCast3D::new_alloc();
        godot_print!("RayCast3D allocated");

        // For built-in Godot classes, we use the direct methods instead of bind_mut()
        ray.set_target_position(Vector3::new(0.0, 0.0, 1.0));
        ray.set_enabled(true);
        ray.set_collision_mask(1);

        // Make the raycast visible in the editor/game
        ray.set_debug_shape_thickness(5);
        ray.set_debug_shape_custom_color(Color::from_rgb(1.0, 0.0, 0.0)); // Red color
        ray.set_name("StairsAheadRaycast");
        godot_print!("RayCast3D configured with name: {}", ray.get_name());

        // Add the child to the scene tree - use a clone here
        self.base_mut().add_child(&ray.clone());
        godot_print!("RayCast3D added as child");

        // Store the reference
        self.stairs_ahead_raycast = Some(ray);
        godot_print!("RayCast3D stored in stairs_ahead_raycast");

        // Debug output
        if let Some(ray_ref) = &self.stairs_ahead_raycast {
            godot_print!(
                "Created raycast with position: {:?}",
                ray_ref.get_target_position()
            );
        }
    }

    pub fn check_input(&mut self, &mut speed: f32) {
        let input = Input::singleton();

        if Engine::singleton().is_editor_hint() {
            return;
        }

        if self.base().is_on_floor() {
            // Properly unwrap the Option<Gd<GroundMovementSettings>>
            if let Some(settings) = &self.ground_settings {
                // Use a reference to borrow the settings
                // Access the settings through bind()
                speed = settings.bind().walk_speed;
            }
        }
    }

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
            return Vector2::default();
        }
    }
    #[func]
    pub fn calc_wish_dir(&mut self) -> Vector3 {
        if Engine::singleton().is_editor_hint() {
            return Vector3::default();
        }
        let dir = self.base().get_global_transform()
            * Vector3::new(self.calc_input_dir().x, 0.0, self.calc_input_dir().y);
        dir
    }

    // Giggity
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
            _l_pivot.set_position(Vector3 {
                x: 0.0,
                y: 1.5,
                z: 0.0,
            });
        }

        // Make capsule
        let mut _skin = MeshInstance3D::new_alloc();
        let mut _capsuleM = CapsuleMesh::new_gd();
        _skin.set_mesh(&_capsuleM);
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
    }
}

#[godot_api]
impl ICharacterBody3D for Player {
    fn init(base: Base<CharacterBody3D>) -> Self {
        // This print should appear for each Player instance
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
        }
    }

    fn ready(&mut self) {
        // Create default settings if none are set
        godot_print!("Player ready function called");

        // // Create default settings if none are set
        if self.ground_settings.is_none() {
            let settings = Gd::<GroundMovementSettings>::default();
            self.ground_settings = Some(settings);
        }
        if self.air_settings.is_none() {
            let settings = Gd::<AirMovementSettings>::default();
            self.air_settings = Some(settings);
        }
        if self.juice_settings.is_none() {
            let settings = Gd::<JuiceSettings>::default();
            self.juice_settings = Some(settings);
        }
        if self.stairs_ahead_raycast.is_none() {
            self.make_step_ahead_ray();
        }
        self.make_children();
    }

    fn physics_process(&mut self, delta: f64) {
        // Safely access the setting
        let speed = self.curr_speed;
        self.check_input(speed);
        let input_dir = self.calc_wish_dir();
        if !Engine::singleton().is_editor_hint() {
            godot_print!("Wish input Direction : {:?}", input_dir);
        }
    }
}
