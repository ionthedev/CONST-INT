use godot::classes::Resource;
use godot::register::*;
use godot::{prelude::*, register};

#[derive(GodotClass)]
#[class(tool, base=Resource)]
pub struct GroundMovementSettings {
    base: Base<Resource>,

    #[export]
    pub walk_speed: f32,
    #[export]
    pub sprint_speed: f32,
    #[export]
    pub crouch_speed: f32,
    #[export]
    pub acceleration: f32,
    #[export]
    pub deceleration: f32,
    #[export]
    pub friction: f32,
    #[export]
    pub climb_speed: f32,
    #[export]
    pub jump_velocity: f32,
    #[export]
    pub auto_jump: bool,
    #[export]
    pub lean_speed: f32,
    #[export]
    pub lean_amount: f32,

    #[export]
    pub crouch_translate: f32,
    #[export]
    pub crouch_jump_add_mult: f32,
    #[export]
    pub max_step_height: f32,
}

#[godot_api]
impl GroundMovementSettings {
    // This is the virtual function that can be overridden in GDScript
    #[func(virtual)]
    fn walk_speed(&mut self, speed: f32) {
        self.walk_speed = speed;
        godot_print!("Rust: walk_speed set to {}", speed);
    }

    /// Updates the walk speed of the ground movement settings.
    ///
    /// Parameters:
    /// - speed: The new walk speed value in units per second.
    ///
    /// Example:
    /// ```gdscript
    /// # In GDScript
    /// settings.update_walk_speed(10.0)  # Sets walk speed to 10.0
    /// ```
    // This is a regular function that calls the virtual one
    #[func]
    pub fn update_walk_speed(&mut self, speed: f32) {
        self.walk_speed(speed);
    }
}

#[godot_api]
impl IResource for GroundMovementSettings {
    fn init(base: Base<Resource>) -> Self {
        Self {
            base,
            walk_speed: 7.0,
            sprint_speed: 8.5,
            crouch_speed: 4.0,
            acceleration: 11.0,
            deceleration: 7.0,
            friction: 6.0,
            climb_speed: 7.0,
            jump_velocity: 6.0,
            auto_jump: true,
            lean_speed: 2.5,
            lean_amount: 0.25,
            crouch_translate: 0.5,
            crouch_jump_add_mult: 0.9,
            max_step_height: 0.5,
        }
    }

    // This method is automatically called by Godot
    fn set_property(&mut self, property: StringName, value: Variant) -> bool {
        let property_str = property.to_string();
        godot_print!("[CONST-INT] {} set to {}", property_str, value);

        false
    }
}
