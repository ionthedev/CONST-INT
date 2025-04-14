use godot::classes::{CurveXyzTexture, Resource};
use godot::obj::{NewAlloc, NewGd};
use godot::prelude::*;

#[derive(GodotClass)]
#[class(tool, base=Resource)]
pub struct StatSettings {
    base: Base<Resource>,

    #[export]
    pub stat_name: GString,

    #[export]
    pub max_value: f32,

    #[export]
    pub current_value: f32,
}

#[godot_api]
impl IResource for StatSettings {
    fn init(base: Base<Resource>) -> Self {
        Self {
            base,
            max_value: 100.0,
            stat_name: GString::from("Stat"),
            current_value: 100.0,
        }
    }

    fn set_property(&mut self, property: StringName, value: Variant) -> bool {
        let property_str = property.to_string();
        godot_print!("[CONST-INT] {} set to {}", property_str, value);

        match property_str.as_str() {
            "current_value" => {
                if let Ok(v) = value.try_to::<f32>() {
                    self.current_value = v;
                    return true;
                }
            }
            "max_value" => {
                if let Ok(v) = value.try_to::<f32>() {
                    self.max_value = v;
                    return true;
                }
            }
            "stat_name" => {
                if let Ok(v) = value.try_to::<GString>() {
                    self.stat_name = v;
                    return true;
                }
            }
            _ => return false,
        }

        false
    }
}
