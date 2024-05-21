//
// Created by IonTheDev on 5/20/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//

#ifndef CONST_INT_ACTORSETTINGS_H
#define CONST_INT_ACTORSETTINGS_H

#include "ActorBase.h"

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



protected:
	static void _bind_methods();
	float walkSpeed = 3.0f;
	float crouchSpeed = 1.5f;
	float sprintSpeed = 6.0f;
	float proneSpeed = 0.75f;
	float jumpForce = 0.75f;
	float mass = 1.25f;
	bool canCrouch = true;
	bool canSprint = true;
	bool canProne = true;
	bool canJump = true;
};

#endif //CONST_INT_ACTORSETTINGS_H
