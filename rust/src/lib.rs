use godot::prelude::*;

mod air_movement_settings;
mod ground_movement_settings;
mod interaction_component;
mod juice_settings;
mod stat_component;
mod stat_setting;

mod player;

struct CI;

#[gdextension]
unsafe impl ExtensionLibrary for CI {}
