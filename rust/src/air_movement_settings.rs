use godot::classes::Resource;
use godot::prelude::*;

#[derive(GodotClass)]
#[class(tool, base=Resource)]
pub struct AirMovementSettings {
    base: Base<Resource>,

    #[export]
    pub speed: f32,
    #[export]
    pub acceleration: f32,
    #[export]
    pub airCap: f32,
}

#[godot_api]
impl IResource for AirMovementSettings {
    fn init(base: Base<Resource>) -> Self {
        Self {
            base,
            speed: 500.0,
            acceleration: 800.0,
            airCap: 0.85,
        }
    }

    // This method is automatically called by Godot
    fn set_property(&mut self, property: StringName, value: Variant) -> bool {
        let property_str = property.to_string();
        godot_print!("[CONST-INT] {} set to {}", property_str, value);

        match property_str.as_str() {
            "speed" => {
                if let Ok(v) = value.try_to::<f32>() {
                    self.speed = v;
                    return true;
                }
            }
            "acceleration" => {
                if let Ok(v) = value.try_to::<f32>() {
                    self.acceleration = v;
                    return true;
                }
            }
            "airCap" => {
                if let Ok(v) = value.try_to::<f32>() {
                    self.airCap = v;
                    return true;
                }
            }
            _ => {}
        }

        false
    }
}
