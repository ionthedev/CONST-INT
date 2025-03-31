use crate::air_movement_settings::AirMovementSettings;
use crate::ground_movement_settings::GroundMovementSettings;
use godot::classes::{CharacterBody3D, ICharacterBody3D, Input, Resource};
use godot::prelude::*;

#[derive(GodotClass)]
#[class(base=CharacterBody3D)]
pub struct Player {
    base: Base<CharacterBody3D>,

    // Instead of using Gd<GroundMovementSettings> directly as an export
    #[export]
    ground_settings: Option<Gd<GroundMovementSettings>>,
    #[export]
    air_settings: Option<Gd<AirMovementSettings>>,
}

#[godot_api]
impl Player {}

#[godot_api]
impl ICharacterBody3D for Player {
    fn init(base: Base<CharacterBody3D>) -> Self {
        godot_print!("[CONST-INT] Initializing Player Class");

        // Start with no settings, will be set later
        Self {
            base,
            ground_settings: None,
            air_settings: None,
        }
    }

    fn ready(&mut self) {
        // Create default settings if none are set
        if self.ground_settings.is_none() {
            let settings = Gd::<GroundMovementSettings>::default();
            self.ground_settings = Some(settings);
        }
        if self.air_settings.is_none() {
            let settings = Gd::<AirMovementSettings>::default();
            self.air_settings = Some(settings);
        }
    }

    fn physics_process(&mut self, delta: f64) {
        // Safely access the settings
        if let Some(settings) = &self.ground_settings {
            let settings = settings.bind();
            let input = Input::singleton();
            let walk_speed = settings.walk_speed;
            let sprint_speed = settings.sprint_speed;

            // Now you can use these values in your physics logic
            let mut speed = walk_speed;
            if input.is_action_pressed("Sprint") {
                speed = sprint_speed;
            }

            // Your movement code here using the speed value...
            godot_print!("Current speed: {}", speed);
        } else {
            godot_print!("Warning: No ground settings available");
        }
    }
}
