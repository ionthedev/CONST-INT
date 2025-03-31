use godot::prelude::*;

mod air_movement_settings;
mod ground_movement_settings;
mod player;

struct CI;

#[gdextension]
unsafe impl ExtensionLibrary for CI {}
