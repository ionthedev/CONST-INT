use godot::classes::{CurveXyzTexture, Resource};
use godot::obj::NewGd;
use godot::prelude::*;

#[derive(GodotClass)]
#[class(tool, base=Resource)]
pub struct JuiceSettings {
    base: Base<Resource>,

    pub headbob_time: f32,
    pub breath_time: f32,

    #[export]
    headbob_move_amount: f32,

    #[export]
    headbob_move_freq: f32,

    #[var]
    pub breath_pos_curve: Gd<CurveXyzTexture>,

    #[var]
    pub breath_rot_curve: Gd<CurveXyzTexture>,

    #[export]
    pub breath_duration: f32,

    #[export]
    pub breath_velocity_magnitude: f32,
}

#[godot_api]
impl IResource for JuiceSettings {
    fn init(base: Base<Resource>) -> Self {
        Self {
            base,
            headbob_move_amount: 0.06,
            headbob_move_freq: 2.46,
            headbob_time: 0.0,
            breath_pos_curve: CurveXyzTexture::new_gd(),
            breath_rot_curve: CurveXyzTexture::new_gd(),
            breath_time: 0.0,
            breath_duration: 1.0,
            breath_velocity_magnitude: 1.0,
        }
    }

    // This method is automatically called by Godot
    fn set_property(&mut self, property: StringName, value: Variant) -> bool {
        let property_str = property.to_string();
        godot_print!("[CONST-INT] {} set to {}", property_str, value);

        match property_str.as_str() {
            "headbob_move_amount" => {
                if let Ok(v) = value.try_to::<f32>() {
                    self.headbob_move_amount = v;
                    return true;
                }
            }
            "headbob_move_freq" => {
                if let Ok(v) = value.try_to::<f32>() {
                    self.headbob_move_freq = v;
                    return true;
                }
            }
            "breath_pos_curve" => {
                if let Ok(v) = value.try_to::<Gd<CurveXyzTexture>>() {
                    self.breath_pos_curve = v;
                    return true;
                }
            }
            "breath_rot_curve" => {
                if let Ok(v) = value.try_to::<Gd<CurveXyzTexture>>() {
                    self.breath_rot_curve = v;
                    return true;
                }
            }
            "breath_duration" => {
                if let Ok(v) = value.try_to::<f32>() {
                    self.breath_duration = v;
                    return true;
                }
            }
            "breath_velocity_magnitude" => {
                if let Ok(v) = value.try_to::<f32>() {
                    self.breath_velocity_magnitude = v;
                    return true;
                }
            }
            _ => {}
        }

        false
    }
}
