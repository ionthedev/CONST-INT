//
// Created by IonThgDev on 5/12/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//

#ifndef CONST_INT_ACTORBASE_H
#define CONST_INT_ACTORBASE_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace CONST_INT {
using namespace godot;

class ActorBase : public CharacterBody3D {
	GDCLASS(ActorBase, CharacterBody3D)


protected:
	static void _bind_methods();

// Godot Methods
	void _process(double delta) override;

	void _ready() override;

	void _physics_process(double delta) override;

	void _unhandled_input(const Ref<InputEvent> &p_event) override;


//CONST_INT Methods
	void MouseLook(double delta);
	Vector3 CalculateWishDirection();


public:
	ActorBase() {}
	~ActorBase() {}
};

}

#endif //CONST_INT_ACTORBASE_H
