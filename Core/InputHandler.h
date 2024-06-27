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
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


using namespace godot;

class InputHandler : public Object {
    GDCLASS(InputHandler, Object)

protected:
    static void _bind_methods();



public:
    InputHandler(const InputHandler& obj) = delete; // Delete copy constructor

    void UpdateKeyMapping(const StringName &key_name, Key key);

    static InputHandler* get_singleton();




    // Method to process input events
    void _input(const Ref<InputEvent> &event);

private:

    InputHandler() {} // Constructor
    // Singleton instance


    Key key_to_map;
    bool is_mapping;

    // Key mappings
    Key k_move_forward;
    Key k_move_backward;
    Key k_move_left;
    Key k_move_right;
    Key k_jump;
    Key k_sprint;
    Key k_crouch;
    Key k_interact;
    Key k_inventory;
    Key k_pause;

    // Initialize default key mappings
    void initialize_default_keys();

    String get_key_as_string(const StringName &key_name);

    void print_test();
};

#endif // INPUTHANDLER_H
