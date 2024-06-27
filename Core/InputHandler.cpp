//
// Created by IonTheDev on 6/17/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//

#include "InputHandler.h"


InputHandler* InputHandler::input_instance = nullptr; // Initialize static member


void InputHandler::_bind_methods() {
    ClassDB::bind_method(D_METHOD("UpdateKeyMapping", "key_name", "key"), &InputHandler::UpdateKeyMapping);
    ClassDB::bind_method(D_METHOD("get_key_as_string", "key_name"), &InputHandler::get_key_as_string);
    ClassDB::bind_static_method("get_singleton", InputHandler::get_singleton());
    ClassDB::bind_method(D_METHOD("_input", "event"), &InputHandler::_input);
}
void InputHandler::UpdateKeyMapping(const StringName &key_name, Key key) {
    if (key_name == StringName("move_forward")) k_move_forward = key;
    else if (key_name == StringName("move_backward")) k_move_backward = key;
    else if (key_name == StringName("move_left")) k_move_left = key;
    else if (key_name == StringName("move_right")) k_move_right = key;
    else if (key_name == StringName("jump")) k_jump = key;
    else if (key_name == StringName("sprint")) k_sprint = key;
    else if (key_name == StringName("crouch")) k_crouch = key;
    else if (key_name == StringName("interact")) k_interact = key;
    else if (key_name == StringName("inventory")) k_inventory  = key;
    else if (key_name == StringName("pause")) k_pause = key;
}

void InputHandler::_input(const Ref<InputEvent> &event) {
    if (is_mapping && event->is_class("InputEventKey")) {
        Ref<InputEventKey> key_event = event;
        key_to_map = key_event->get_keycode();
        is_mapping = false;
        UtilityFunctions::print("Key mapped: ", key_to_map);
    }
}


void InputHandler::initialize_default_keys() {
    k_move_forward = KEY_W;
    k_move_backward = KEY_S;
    k_move_left = KEY_A;
    k_move_right = KEY_D;
    k_jump = KEY_SPACE;
    k_sprint = KEY_SHIFT;
    k_crouch = KEY_CTRL;
    k_interact = KEY_E;
    k_inventory = KEY_TAB;
    k_pause = KEY_ESCAPE;
}

String InputHandler::get_key_as_string(const StringName &key_name) {
    Key key = KEY_UNKNOWN;

    if (key_name == StringName("move_forward")) key = k_move_forward;
    else if (key_name == StringName("move_backward")) key = k_move_backward;
    else if (key_name == StringName("move_left")) key = k_move_left;
    else if (key_name == StringName("move_right")) key = k_move_right;
    else if (key_name == StringName("jump")) key = k_jump;
    else if (key_name == StringName("sprint")) key = k_sprint;
    else if (key_name == StringName("crouch")) key = k_crouch;
    else if (key_name == StringName("interact")) key = k_interact;
    else if (key_name == StringName("inventory")) key = k_inventory ;
    else if (key_name == StringName("pause")) key = k_pause;

    Ref<InputEventKey> key_event;
    key_event->set_keycode(key);

    return key_event->as_text_keycode();
}


InputHandler* InputHandler::get_singleton() {
    if (input_instance == nullptr) {
        input_instance = new InputHandler();
    }
    return input_instance;
}
