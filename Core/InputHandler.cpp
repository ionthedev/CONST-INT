//
// Created by IonTheDev on 6/17/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//

#include "InputHandler.h"

InputHandler* InputHandler::input_instance = nullptr; // Initialize static member

void InputHandler::_bind_methods() {
    // Bind custom methods if any
}

void InputHandler::UpdateKeyMapping(StringName key_name, Key key) {
    InputMap* input_map = InputMap::get_singleton();
    input_map->load_from_project_settings();
    TypedArray<StringName> keys = InputMap::get_singleton()->get_actions();

    if(keys.has (key_name)) {

        Ref<InputEventKey> key_event;
        key_event->set_keycode(key);
        input_map->erase_action(key_name);
        input_map->action_add_event(key_name, key_event);
    }
}


InputHandler* InputHandler::get_singleton() {
    if (input_instance == nullptr) {
        input_instance = new InputHandler();
    }
    return input_instance;
}
