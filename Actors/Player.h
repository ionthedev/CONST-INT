//
// Created by IonTheDev on 5/12/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//

#ifndef CONST_INT_Player_H
#define CONST_INT_Player_H

#include "Config/ActorSettings.h"
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/capsule_shape3d.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/cylinder_shape3d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/mesh_library.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/physics_body3d.hpp>
#include <godot_cpp/classes/physics_server3d.hpp>
#include <godot_cpp/classes/physics_test_motion_parameters3d.hpp>
#include <godot_cpp/classes/physics_test_motion_result3d.hpp>
#include <godot_cpp/classes/ray_cast3d.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/rigid_body3d.hpp>
#include <godot_cpp/classes/shape3d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>

using namespace godot;

	struct attachments_t {
	Camera3D* camera = nullptr;
	Node3D* skull = nullptr; //contains head_h, which contains head_v, which contains camera
	Node3D* head_h = nullptr;
	Node3D* head_v = nullptr;
	MeshInstance3D* body = nullptr;
	AnimationPlayer* animationPlayer = nullptr;
	CollisionShape3D* collider = nullptr;
	RayCast3D* stepDownRay = nullptr;
	RayCast3D* stepAheadRay = nullptr;
};

	struct actor_vars_t{
	Vector2 mouse_motion;
	Vector2 inputDir;
	Vector3 wishDir;
	Vector3 moveDir;
	Vector3 velocity;
	float speed;
	float jump_velocity = 5.0f;
	float acceleration;
	Vector3 mouse_rotation;
	float mouse_sensitivity;
	bool initialized;
	const float gravity = 9.85f;
	const float crouch_translate = 0.125f;
	const float crouch_jump_add = crouch_translate * 0.9f;
	bool is_crouched = false;
	const float max_step_height = 0.25f;
	float original_height;
	bool _snapped_to_stairs_last_frame = false;
	uint64_t _last_frame_was_on_floor;
	const float headbob_amount = 0.06f;
	const float headbob_frequency = 2.4f;
	float headbob_time;
	Area3D* currentLadder = nullptr;


};

class Player : public CharacterBody3D {
	GDCLASS(Player, CharacterBody3D)

protected:

	static void _bind_methods();

	//CONST_INT Methods
	void MouseLook(const Ref<InputEventMouseMotion> &p_event);
	void CalculateDirection();
	void ApplyGravity(double delta);
	void ProcessJump();
	void MakeAttachments();
	void HandleGroundPhysics(double delta);
	void HandleAirPhysics(double delta);
	void SetMouseMode(Input::MouseMode _mode) const;
	bool IsSurfaceTooSteep(Vector3 _normal) const;
	Ref<ActorSettings> get_Settings() const;
	void set_Settings(const Ref<ActorSettings>& _settings);
	bool HandleLadderPhysics();



	//CONST_INT Variables
	PhysicsServer3D *physicsServer;

	Input *e_input;


public:


	attachments_t attachments{};
	actor_vars_t actor_vars{};


	// Godot Methods
	void _process(double delta) override;
	void _ready() override;
	void _physics_process(double delta) override;
	void _unhandled_input(const Ref<InputEvent> &p_event) override;

	void CI_Move();
	float GetMoveSpeed() const;

private:
	Ref<ActorSettings> settings;
	void CreateCollider();
	void CreateSkull();
	void CreateHeadHorizontal();
	void CreateHeadVertical();
	void CreateCamera();
	void CreateBody();
	void CreateStepRays();
	void SnapDownToStairsCheck();
	bool StepUpStairsCheck(double delta);
	void HandleCrouch(double delta);
	Vector3 SavedCameraPos = Vector3(0,0,0);
	void SaveCamPosForSmoothing();
	void SmoothCamera(double delta);
	void HeadBob(double delta);
	void PushAwayRigidBodies();
	void InteractionCast();




};



#endif //CONST_INT_Player_H