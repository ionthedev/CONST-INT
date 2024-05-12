//
// Created by IonThgDev on 5/12/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//
#include "ActorBase.h"

void CONST_INT::ActorBase::_bind_methods() {
}
void CONST_INT::ActorBase::_process(double delta) {
	Node::_process(delta);
}
void CONST_INT::ActorBase::_ready() {
	Node::_ready();
}
void CONST_INT::ActorBase::_physics_process(double delta) {
	Node::_physics_process(delta);
}
void CONST_INT::ActorBase::_unhandled_input(const godot::Ref<godot::InputEvent> &p_event) {
	Node::_unhandled_input(p_event);
}
void CONST_INT::ActorBase::MouseLook(double delta) {
}
godot::Vector3 CONST_INT::ActorBase::CalculateWishDirection() {
	return godot::Vector3();
}
