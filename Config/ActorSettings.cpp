//
// Created by IonTheDev on 6/16/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//

#include "ActorSettings.h"
void ActorSettings::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_WalkSpeed"), &ActorSettings::get_WalkSpeed);
	ClassDB::bind_method(D_METHOD("set_WalkSpeed", "_speed"), &ActorSettings::set_WalkSpeed);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "walk_speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_WalkSpeed", "get_WalkSpeed");

	ClassDB::bind_method(D_METHOD("get_CrouchSpeed"), &ActorSettings::get_CrouchSpeed);
	ClassDB::bind_method(D_METHOD("set_CrouchSpeed", "_speed"), &ActorSettings::set_CrouchSpeed);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "crouch_speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_CrouchSpeed", "get_CrouchSpeed");

	ClassDB::bind_method(D_METHOD("get_CanCrouch"), &ActorSettings::get_CanCrouch);
	ClassDB::bind_method(D_METHOD("set_CanCrouch", "_value"), &ActorSettings::set_CanCrouch);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::BOOL, "can_crouch"), "set_CanCrouch", "get_CanCrouch");

	ClassDB::bind_method(D_METHOD("get_SprintSpeed"), &ActorSettings::get_SprintSpeed);
	ClassDB::bind_method(D_METHOD("set_SprintSpeed", "_speed"), &ActorSettings::set_SprintSpeed);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "sprint_speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_SprintSpeed", "get_SprintSpeed");

	ClassDB::bind_method(D_METHOD("get_CanSprint"), &ActorSettings::get_CanSprint);
	ClassDB::bind_method(D_METHOD("set_CanSprint", "_value"), &ActorSettings::set_CanSprint);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::BOOL, "can_sprint"), "set_CanSprint", "get_CanSprint");

	//ClassDB::bind_method(D_METHOD("get_ProneSpeed"), &ActorSettings::get_ProneSpeed);
	//ClassDB::bind_method(D_METHOD("set_ProneSpeed", "_speed"), &ActorSettings::set_ProneSpeed);
	//ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "prone_speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_ProneSpeed", "get_ProneSpeed");

	ClassDB::bind_method(D_METHOD("get_CanProne"), &ActorSettings::get_CanProne);
	ClassDB::bind_method(D_METHOD("set_CanProne", "_value"), &ActorSettings::set_CanProne);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::BOOL, "can_prone"), "set_CanProne", "get_CanProne");

	ClassDB::bind_method(D_METHOD("get_jumpForce"), &ActorSettings::get_jumpForce);
	ClassDB::bind_method(D_METHOD("set_jumpForce", "_force"), &ActorSettings::set_jumpForce);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "jump_force", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_jumpForce", "get_jumpForce");

	ClassDB::bind_method(D_METHOD("get_CanJump"), &ActorSettings::get_CanJump);
	ClassDB::bind_method(D_METHOD("set_CanJump", "_value"), &ActorSettings::set_CanJump);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::BOOL, "can_jump"), "set_CanJump", "get_CanJump");

	ClassDB::bind_method(D_METHOD("get_Mass"), &ActorSettings::get_Mass);
	ClassDB::bind_method(D_METHOD("set_Mass", "_mass"), &ActorSettings::set_Mass);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "mass", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_Mass", "get_Mass");

	ClassDB::bind_method(D_METHOD("get_CanHeadBob"), &ActorSettings::get_CanHeadBob);
	ClassDB::bind_method(D_METHOD("set_CanHeadBob", "_value"), &ActorSettings::set_CanHeadBob);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::BOOL, "can_headbob"), "set_CanHeadBob", "get_CanHeadBob");

	ClassDB::bind_method(D_METHOD("get_ClimbSpeed"), &ActorSettings::get_ClimbSpeed);
	ClassDB::bind_method(D_METHOD("set_ClimbSpeed", "_speed"), &ActorSettings::set_ClimbSpeed);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "climb_speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_ClimbSpeed", "get_ClimbSpeed");


	ClassDB::bind_method(D_METHOD("get_CanClimbLadder"), &ActorSettings::get_CanClimbLadder);
	ClassDB::bind_method(D_METHOD("set_CanClimbLadder", "_value"), &ActorSettings::set_CanClimbLadder);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::BOOL, "can_climbladder"), "set_CanClimbLadder", "get_CanClimbLadder");


	ClassDB::bind_method(D_METHOD("get_interactDistance"), &ActorSettings::get_interactDistance);
	ClassDB::bind_method(D_METHOD("set_interactDistance", "_value"), &ActorSettings::set_interactDistance);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "interact_distance"), "set_interactDistance", "get_interactDistance");


	ClassDB::bind_method(D_METHOD("get_crouchAmount"), &ActorSettings::get_crouchAmount);
	ClassDB::bind_method(D_METHOD("set_crouchAmount", "_value"), &ActorSettings::set_crouchAmount);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "crouch_amount"), "set_crouchAmount", "get_crouchAmount");


	ClassDB::bind_method(D_METHOD("get_crouchJumpMultiplier"), &ActorSettings::get_crouchJumpMultiplier);
	ClassDB::bind_method(D_METHOD("set_crouchJumpMultiplier", "_value"), &ActorSettings::set_crouchJumpMultiplier);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "crouch_jump_multiplier"), "set_crouchJumpMultiplier", "get_crouchJumpMultiplier");


	ClassDB::bind_method(D_METHOD("get_HeadBobAmount"), &ActorSettings::get_HeadBobAmount);
	ClassDB::bind_method(D_METHOD("set_HeadBobAmount", "_value"), &ActorSettings::set_HeadBobAmount);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "headbob_amount"), "set_HeadBobAmount", "get_HeadBobAmount");


	ClassDB::bind_method(D_METHOD("get_HeadBobFrequency"), &ActorSettings::get_HeadBobFrequency);
	ClassDB::bind_method(D_METHOD("set_HeadBobFrequency", "_value"), &ActorSettings::set_HeadBobFrequency);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "headbob_frequency"), "set_HeadBobFrequency", "get_HeadBobFrequency");


	ClassDB::bind_method(D_METHOD("get_CanClimbStairs"), &ActorSettings::get_CanClimbStairs);
	ClassDB::bind_method(D_METHOD("set_CanClimbStairs", "_value"), &ActorSettings::set_CanClimbStairs);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::BOOL, "canClimbStairs"), "set_CanClimbStairs", "get_CanClimbStairs");


	ClassDB::bind_method(D_METHOD("get_maxStairHeight"), &ActorSettings::get_maxStairHeight);
	ClassDB::bind_method(D_METHOD("set_maxStairHeight", "_value"), &ActorSettings::set_maxStairHeight);
	ClassDB::add_property("ActorSettings", PropertyInfo(Variant::FLOAT, "max_step_height"), "set_maxStairHeight", "get_maxStairHeight");
}


void ActorSettings::set_CrouchSpeed(const float _speed) {
	crouchSpeed = _speed;
}
float ActorSettings::get_CrouchSpeed() const {
	return crouchSpeed;
}

void ActorSettings::set_crouchAmount(float _value) {
	crouch_amount = _value;
}

float ActorSettings::get_crouchAmount() const {
	return crouch_amount;
}

void ActorSettings::set_crouchJumpMultiplier(float _value) {
	crouch_jump_multiplier = _value;
}

float ActorSettings::get_crouchJumpMultiplier() {
	return crouch_jump_multiplier;
}

float ActorSettings::get_crouchJumpValue() const {
	return crouch_amount * crouch_jump_multiplier;
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
void ActorSettings::set_ClimbSpeed(const float _speed) {
	climbSpeed = _speed;
}
float ActorSettings::get_ClimbSpeed() const {
	return climbSpeed;
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
	//canProne = _value;
}
bool ActorSettings::get_CanProne() const {
	return true;
}
void ActorSettings::set_CanJump(const bool _value) {
	canJump = _value;
}
bool ActorSettings::get_CanJump() const {
	return canJump;
}
void ActorSettings::set_CanHeadBob(const bool _value) {
	canHeadBob = _value;
}
bool ActorSettings::get_CanHeadBob() const {
	return canHeadBob;
}

void ActorSettings::set_HeadBobAmount(float _value) {
	headbob_amount = _value;
}

float ActorSettings::get_HeadBobAmount() const {
	return headbob_amount;
}

void ActorSettings::set_HeadBobFrequency(float _value) {
	headbob_frequency = _value;
}

float ActorSettings::get_HeadBobFrequency() const {
	return headbob_frequency;
}

void ActorSettings::set_CanClimbLadder(const bool _value) {
	canClimbLadder = _value;
}
bool ActorSettings::get_CanClimbLadder() const {
	return canClimbLadder;
}

void ActorSettings::set_CanClimbStairs(bool _value) {
	canClimbStairs = _value;
}

bool ActorSettings::get_CanClimbStairs() const {
	return canClimbStairs;
}

void ActorSettings::set_maxStairHeight(float _value) {
	max_step_height = _value;
}

float ActorSettings::get_maxStairHeight() const {
	return max_step_height;
}

void ActorSettings::set_interactDistance(float _value) {
	interactDistance = _value;
}

float ActorSettings::get_interactDistance() const {
	return interactDistance;
}
