//
// Created by ion on 6/21/24.
//

#include "InteractionComponent.h"

#include <godot_cpp/variant/utility_functions.hpp>

void InteractionComponent::_bind_methods() {

    ADD_SIGNAL(MethodInfo("in_focus"));
    ADD_SIGNAL(MethodInfo("out_focus"));
    ADD_SIGNAL(MethodInfo("start_interact"));
    ADD_SIGNAL(MethodInfo("end_interact"));
}



void InteractionComponent::_ready() {
    ComponentNode::_ready();
    parent = get_parent();
    connect_signals();
}

void InteractionComponent::connect_signals() {
    if (!parent) {
        UtilityFunctions::print("Parent is null, cannot add signals.");
        return;
    }

    UtilityFunctions::print("Adding signals to " + parent->get_name());

    // Ensure that parent is a Node and can have signals added
    if (Node *parent_node = Object::cast_to<Node>(parent)) {
        UtilityFunctions::print("Parent is a valid Node.");

        if (!parent_node->has_user_signal("in_focus")) {
            UtilityFunctions::print("Adding signal: in_focus");
            parent_node->add_user_signal("in_focus");
            connect("in_focus", Callable(parent_node, "is_focus"));
        } else {
            UtilityFunctions::print("Signal in_focus already exists");
        }

        if (!parent_node->has_user_signal("out_focus")) {
            UtilityFunctions::print("Adding signal: out_focus");
            parent_node->add_user_signal("out_focus");
        } else {
            UtilityFunctions::print("Signal out_focus already exists");
        }

        if (!parent_node->has_user_signal("start_interact")) {
            UtilityFunctions::print("Adding signal: start_interact");
            parent_node->add_user_signal("start_interact");
        } else {
            UtilityFunctions::print("Signal start_interact already exists");
        }

        if (!parent_node->has_user_signal("end_interact")) {
            UtilityFunctions::print("Adding signal: end_interact");
            parent_node->add_user_signal("end_interact");
        } else {
            UtilityFunctions::print("Signal end_interact already exists");
        }
    } else {
        UtilityFunctions::print("Parent is not a Node, cannot add signals.");
    }
}