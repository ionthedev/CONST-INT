//
// Created by IonTheDev on 6/17/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class InputHandler : public Input {
    GDCLASS(InputHandler, Input)

protected:
    static void _bind_methods();

    InputHandler() {} // Constructor


public:
    InputHandler(const InputHandler& obj) = delete; // Delete copy constructor

    static void UpdateKeyMapping(StringName key_name, Key key);
    static InputHandler* get_singleton();

private:
    static InputHandler* input_instance;

    Key key_to_map = KEY_UNKNOWN; // Key to map to
    MouseButton mouse_button_to_map = MOUSE_BUTTON_LEFT; // Mouse button to map to
    bool is_mapping = false; // If we are currently mapping a key
    bool is_mouse_mapping = false; // If we are currently mapping a mouse button
    bool is_key_mapped = false; // If a key is mapped
    bool is_mouse_mapped = false; // If a mouse button is mapped


    Key last_key_pressed = KEY_UNKNOWN;

    Key k_move_forward = KEY_W;
    Key k_move_backward = KEY_S;
    Key k_move_left = KEY_A;
    Key k_move_right = KEY_D;
    Key k_jump = KEY_SPACE;
    Key k_sprint = KEY_SHIFT;
    Key k_crouch = KEY_CTRL;
    Key k_interact = KEY_E;
    Key k_inventory = KEY_TAB;
    Key k_pause = KEY_ESCAPE;
    MouseButton k_PrimaryUse = MOUSE_BUTTON_LEFT;
    MouseButton k_SecondaryUse = MOUSE_BUTTON_RIGHT;


};

#endif // INPUTHANDLER_H
