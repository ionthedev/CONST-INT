//
// Created by IonTheDev on 5/12/24.
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
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/cylinder_shape3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/mesh_library.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/physics_body3d.hpp>
#include <godot_cpp/classes/shape3d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/physics_server3d.hpp>


using namespace godot;
namespace CONST_INT {

typedef struct {
	Camera3D* camera = nullptr;
	Node3D* head_h = nullptr;
	Node3D* head_v = nullptr;
	MeshInstance3D* body = nullptr;
	AnimationPlayer* animationPlayer = nullptr;
	CollisionShape3D* collider = nullptr;
} attachments_t;


typedef struct {
	Vector2 mouse_motion;
	Vector2 inputDir;
	Vector3 wishDir;
	Vector3 moveDir;
	Vector3 velocity;
	float speed;
	float acceleration;
	Vector3 mouse_rotation;
	float mouse_sensitivity;
	bool initialized;

} actor_vars_t;

class ActorBase : public CharacterBody3D {
	GDCLASS(ActorBase, CharacterBody3D)

protected:



	static void _bind_methods();

	//CONST_INT Methods
	void MouseLook(const Ref<InputEventMouseMotion> &p_event);
	void CalculateWishDirection(double delta);
	void CalculateVelocity();
	void UpdateVelocity(Vector3 newV, double delta);
	void ApplyGravity(double delta);
	void MakeAttachments();



	//CONST_INT Variables
	PhysicsServer3D *physicsServer;

	Input *e_input;


public:
	ActorBase() {}
	~ActorBase() {}

	attachments_t attachments{};
	actor_vars_t actor_vars{};


	// Godot Methods
	void _process(double delta) override;

	void _ready() override;

	void _physics_process(double delta) override;

	void _unhandled_input(const Ref<InputEvent> &p_event) override;





};

}

#endif //CONST_INT_ACTORBASE_H