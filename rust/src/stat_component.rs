use std::ops::Deref;

use crate::stat_setting::StatSettings;
use godot::classes::Node;
use godot::prelude::*;

#[derive(GodotClass)]
#[class(tool, base=Node)]
pub struct StatComponent {
    base: Base<Node>,

    #[export]
    stats: Array<Option<Gd<StatSettings>>>,
}

#[godot_api]
impl INode for StatComponent {
    fn init(base: Base<Node>) -> Self {
        godot_print!("[CONST-INT] Stats Component added to scene");
        Self {
            base,
            stats: Array::new(),
        }
    }
}

#[godot_api]
impl StatComponent {
    #[func]
    fn find_stat_by_name(&self, name: GString) -> Option<Gd<StatSettings>> {
        // Your existing implementation
        for stat in self.stats.iter_shared() {
            if let Some(stat_setting) = stat.clone() {
                let stat_setting_binding = stat_setting.bind();
                if stat_setting_binding.stat_name == name {
                    return Some(stat_setting.clone());
                }
            }
        }
        None
    }
    // This is registered as a static method on the class
    #[func]
    pub fn find_stat_by_name_static(
        component: Gd<StatComponent>,
        name: GString,
    ) -> Option<Gd<StatSettings>> {
        component.bind().find_stat_by_name(name)
    }

    #[func]
    pub fn set_stat_max_value(&mut self, name: GString, new_v: f32) {
        if let Some(mut stat) = self.find_stat_by_name(name).clone() {
            stat.bind_mut().set_max_value(new_v);
        }
    }

    #[func]
    pub fn get_stat_max_value(&mut self, name: GString) -> f32 {
        if let Some(mut stat) = self.find_stat_by_name(name).clone() {
            return stat.bind_mut().get_max_value();
        }
        f32::NAN
    }

    #[func]
    pub fn set_stat_value(&mut self, name: GString, new_v: f32) {
        if let Some(mut stat) = self.find_stat_by_name(name).clone() {
            stat.bind_mut().set_current_value(new_v);
        }
    }

    #[func]
    pub fn modify_stat_value(&mut self, name: GString, new_v: f32) {
        if let Some(mut stat) = self.find_stat_by_name(name).clone() {
            let max = stat.bind().get_max_value();
            let current = stat.bind().get_current_value();
            let modified = current + new_v;

            // Clamp the modified value between 0 and max
            let clamped = modified.max(0.0).min(max);

            stat.bind_mut().set_current_value(clamped);
        }
    }

    #[func]
    pub fn get_stat_value(&mut self, name: GString) -> f32 {
        if let Some(mut stat) = self.find_stat_by_name(name).clone() {
            return stat.bind_mut().get_current_value();
        }
        f32::NAN
    }
}
