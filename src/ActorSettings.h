//
// Created by IonTheDev on 5/20/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//

#ifndef CONST_INT_ACTORSETTINGS_H
#define CONST_INT_ACTORSETTINGS_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>

using namespace godot;
class ActorSettings : public Resource {
	GDCLASS(ActorSettings, Resource)

public:
	void set_WalkSpeed(const float _speed);
	float get_WalkSpeed() const;

	void set_CrouchSpeed(const float _speed);
	float get_CrouchSpeed() const;

	void set_SprintSpeed(const float _speed);
	float get_SprintSpeed() const;

	void set_ProneSpeed(const float _speed);
	float get_ProneSpeed() const;

	void set_ClimbSpeed(const float _speed);
	float get_ClimbSpeed() const;


	void set_jumpForce(const float _force);
	float get_jumpForce() const;

	void set_Mass(const float _mass);
	float get_Mass() const;

	void set_CanCrouch(const bool _value);
	bool get_CanCrouch() const;

	void set_CanSprint(const bool _value);
	bool get_CanSprint() const;

	void set_CanProne(const bool _value);
	bool get_CanProne() const;

	void set_CanJump(const bool _value);
	bool get_CanJump() const;

	void set_CanHeadBob(const bool _value);
	bool get_CanHeadBob() const;

	void set_CanClimbLadder(const bool _value);
	bool get_CanClimbLadder() const;



protected:
	static void _bind_methods();

private:
	float walkSpeed = 3.0f;
	float crouchSpeed = 1.5f;
	float sprintSpeed = 6.0f;
	float proneSpeed = 0.75f;
	float jumpForce = 0.75f;
	float climbSpeed = 3.0f;
	float mass = 1.25f;
	bool canCrouch = true;
	bool canSprint = true;
	bool canProne = true;
	bool canJump = true;
	bool canHeadBob = true;
	bool canClimbLadder = true;
};

#endif //CONST_INT_ACTORSETTINGS_H
