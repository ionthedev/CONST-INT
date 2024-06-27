//
// Created by IonTheDev on 6/16/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//

#ifndef ACTORSETTINGS_H
#define ACTORSETTINGS_H


#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>

using namespace godot;
class ActorSettings : public Resource {
    GDCLASS(ActorSettings, Resource)

public:
    void set_WalkSpeed(float _speed);
    float get_WalkSpeed() const;


    void set_SprintSpeed(float _speed);
    float get_SprintSpeed() const;

    void set_ProneSpeed(float _speed);
    float get_ProneSpeed() const;

    void set_ClimbSpeed(float _speed);
    float get_ClimbSpeed() const;


    void set_jumpForce(float _force);
    float get_jumpForce() const;

    void set_Mass(float _mass);
    float get_Mass() const;

    void set_CanCrouch(bool _value);
    bool get_CanCrouch() const;
    void set_CrouchSpeed(float _speed);
    float get_CrouchSpeed() const;
    void set_crouchAmount(float _value);
    float get_crouchAmount() const;
    void set_crouchJumpMultiplier(float _value);
    float get_crouchJumpMultiplier();
    float get_crouchJumpValue() const;

    void set_CanSprint(bool _value);
    bool get_CanSprint() const;

    void set_CanProne(bool _value);
    bool get_CanProne() const;

    void set_CanJump(bool _value);
    bool get_CanJump() const;

    void set_CanHeadBob(bool _value);
    bool get_CanHeadBob() const;
    void set_HeadBobAmount(float _value);
    float get_HeadBobAmount() const;
    void set_HeadBobFrequency(float _value);
    float get_HeadBobFrequency() const;


    void set_CanClimbLadder(bool _value);
    bool get_CanClimbLadder() const;

    void set_CanClimbStairs(bool _value);
    bool get_CanClimbStairs() const;
    void set_maxStairHeight(float _value);
    float get_maxStairHeight() const;

    void set_interactDistance(float _value);
    float get_interactDistance() const;





protected:
    static void _bind_methods();

private:
    float walkSpeed = 3.0f;
    float proneSpeed = 0.75f;
    float jumpForce = 0.75f;
    float climbSpeed = 3.0f;
    float interactDistance = 3.0f;
    float mass = 1.25f;

    bool canCrouch = true;
    float crouchSpeed = 1.5f;
    float crouch_amount = 0.125f;
    float crouch_jump_multiplier = 0.9f;


    bool canSprint = true;
    float sprintSpeed = 6.0f;

    //bool canProne = true;
    bool canJump = true;

    bool canClimbLadder = true;

    bool canClimbStairs = true;
    float max_step_height = 0.25f;

    bool canHeadBob = true;
    float headbob_amount = 0.06f;
    float headbob_frequency = 2.4f;
};

#endif //ACTORSETTINGS_H
