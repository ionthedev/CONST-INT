//
// Created by IonTheDev on 5/20/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//

#include "ActorSettings.h"
void ActorSettings::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_WalkSpeed"), &ActorSettings::get_WalkSpeed);
	ClassDB::bind_method(D_METHOD("set_WalkSpeed", "_speed"), &ActorSettings::set_WalkSpeed);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "Walk Speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_WalkSpeed", "get_WalkSpeed");

	ClassDB::bind_method(D_METHOD("get_CrouchSpeed"), &ActorSettings::get_CrouchSpeed);
	ClassDB::bind_method(D_METHOD("set_CrouchSpeed", "_speed"), &ActorSettings::set_CrouchSpeed);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "Crouch Speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_CrouchSpeed", "get_CrouchSpeed");

	ClassDB::bind_method(D_METHOD("get_CanCrouch"), &ActorSettings::get_CanCrouch);
	ClassDB::bind_method(D_METHOD("set_CanCrouch", "_value"), &ActorSettings::set_CanCrouch);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::BOOL, "Crouch Enabled"), "set_CanCrouch", "get_CanCrouch");

	ClassDB::bind_method(D_METHOD("get_SprintSpeed"), &ActorSettings::get_SprintSpeed);
	ClassDB::bind_method(D_METHOD("set_SprintSpeed", "_speed"), &ActorSettings::set_SprintSpeed);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "Sprint Speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_SprintSpeed", "get_SprintSpeed");

	ClassDB::bind_method(D_METHOD("get_CanSprint"), &ActorSettings::get_CanSprint);
	ClassDB::bind_method(D_METHOD("set_CanSprint", "_value"), &ActorSettings::set_CanSprint);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::BOOL, "Sprint Enabled"), "set_CanSprint", "get_CanSprint");

	ClassDB::bind_method(D_METHOD("get_ProneSpeed"), &ActorSettings::get_ProneSpeed);
	ClassDB::bind_method(D_METHOD("set_ProneSpeed", "_speed"), &ActorSettings::set_ProneSpeed);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "Prone Speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_ProneSpeed", "get_ProneSpeed");

	ClassDB::bind_method(D_METHOD("get_CanProne"), &ActorSettings::get_CanProne);
	ClassDB::bind_method(D_METHOD("set_CanProne", "_value"), &ActorSettings::set_CanProne);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::BOOL, "Prone Enabled"), "set_CanProne", "get_CanProne");

	ClassDB::bind_method(D_METHOD("get_jumpForce"), &ActorSettings::get_jumpForce);
	ClassDB::bind_method(D_METHOD("set_jumpForce", "_force"), &ActorSettings::set_jumpForce);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "Jump Force", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_jumpForce", "get_jumpForce");

	ClassDB::bind_method(D_METHOD("get_CanJump"), &ActorSettings::get_CanJump);
	ClassDB::bind_method(D_METHOD("set_CanJump", "_value"), &ActorSettings::set_CanJump);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::BOOL, "Jump Enabled"), "set_CanJump", "get_CanJump");

	ClassDB::bind_method(D_METHOD("get_Mass"), &ActorSettings::get_Mass);
	ClassDB::bind_method(D_METHOD("set_Mass", "_mass"), &ActorSettings::set_Mass);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "Mass", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_Mass", "get_Mass");
}
void ActorSettings::set_CrouchSpeed(const float _speed) {
	crouchSpeed = _speed;
}
float ActorSettings::get_CrouchSpeed() const {
	return crouchSpeed;
}
float ActorSettings::get_WalkSpeed() const {
	return walkSpeed;
}
void ActorSettings::set_WalkSpeed(const float _speed) {
	walkSpeed = _speed;
}
void ActorSettings::set_SprintSpeed(const float _speed) {
	sprintSpeed = _speed;
}
float ActorSettings::get_SprintSpeed() const {
	return sprintSpeed;
}
void ActorSettings::set_ProneSpeed(const float _speed) {
	proneSpeed = _speed;
}
float ActorSettings::get_ProneSpeed() const {
	return proneSpeed;
}
void ActorSettings::set_jumpForce(const float _force) {
	jumpForce = _force;
}
float ActorSettings::get_jumpForce() const {
	return jumpForce;
}
void ActorSettings::set_Mass(const float _mass) {
	mass = _mass;
}
float ActorSettings::get_Mass() const {
	return mass;
}
void ActorSettings::set_CanCrouch(const bool _value) {
	canCrouch = _value;
}
bool ActorSettings::get_CanCrouch() const {
	return canCrouch;
}
void ActorSettings::set_CanSprint(const bool _value) {
	canSprint = _value;
}
bool ActorSettings::get_CanSprint() const {
	return canSprint;
}
void ActorSettings::set_CanProne(const bool _value) {
	canProne = _value;
}
bool ActorSettings::get_CanProne() const {
	return canProne;
}
void ActorSettings::set_CanJump(const bool _value) {
	canJump = _value;
}
bool ActorSettings::get_CanJump() const {
	return canJump;
}
