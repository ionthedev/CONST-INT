//
// Created by IonTheDev on 5/12/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//
#include "ActorBase.h"

void CONST_INT::ActorBase::_bind_methods() {

}
void CONST_INT::ActorBase::_process(const double delta) {
	CharacterBody3D::_process(delta);
}
void CONST_INT::ActorBase::_ready() {
	ActorBase::MakeAttachments();
	ActorBase::physicsServer = PhysicsServer3D::get_singleton();
	e_input = Input::get_singleton();
	actor_vars.speed = 3.0f;
	actor_vars.mouse_sensitivity = 0.19f;
	SetMouseMode(Input::MOUSE_MODE_CAPTURED);
}
void CONST_INT::ActorBase::_physics_process(const double delta) {
	if(is_on_floor()) actor_vars._last_frame_was_on_floor = Engine().get_physics_frames();



	//ApplyGravity(delta);
	CalculateWishDirection(delta);

	move_and_slide();
	SnapDownToStairsCheck();
}
void CONST_INT::ActorBase::_unhandled_input(const godot::Ref<godot::InputEvent> &p_event) {
	if (p_event->is_class("InputEventMouseMotion")) {
		auto *mouseMotionEvent = dynamic_cast<InputEventMouseMotion *>(*p_event);
		ActorBase::MouseLook(mouseMotionEvent);
	}
}

void CONST_INT::ActorBase::MouseLook(const Ref<InputEventMouseMotion> &p_event) {

	if(Engine::get_singleton()->is_editor_hint()) return;
	actor_vars.mouse_motion = p_event->get_relative();
	// Handle Horizontal Rotation
	attachments.head_h->rotate_y(Math::deg_to_rad(-actor_vars.mouse_motion.x * actor_vars.mouse_sensitivity));

	actor_vars.mouse_rotation.x += Math::deg_to_rad(-actor_vars.mouse_motion.y * actor_vars.mouse_sensitivity);
	actor_vars.mouse_rotation.x = Math::clamp(actor_vars.mouse_rotation.x, Math::deg_to_rad(-89.0f), Math::deg_to_rad(89.0f));

	actor_vars.mouse_rotation.z += Math::deg_to_rad(-actor_vars.mouse_motion.y * actor_vars.mouse_sensitivity * actor_vars.inputDir.length());
	actor_vars.mouse_rotation.z = Math::clamp(actor_vars.mouse_rotation.z, Math::deg_to_rad(-85.0f), Math::deg_to_rad(85.0f));



	// Handle Vertical Rotation
	actor_vars.mouse_rotation.z = Math::lerp(actor_vars.mouse_rotation.z, 0.0f, static_cast<float>(get_physics_process_delta_time()) * 7.0f);

	Transform3D t = attachments.head_v->get_transform();
	t.basis = get_basis();
	attachments.head_v->set_transform(t);

	attachments.head_v->rotate_object_local(Vector3(1, 0, 0), actor_vars.mouse_rotation.x);

	UtilityFunctions::print(actor_vars.mouse_motion);

}

void CONST_INT::ActorBase::CalculateWishDirection(double delta) {

	if (Engine::get_singleton()->is_editor_hint())
		return;

	actor_vars.inputDir = e_input->get_vector("MoveLeft","MoveRight","MoveBackward","MoveForward").normalized();


	if(actor_vars.inputDir != Vector2(0,0)) {
		const Vector3 forward = -attachments.head_h->get_transform().basis.get_column(2).normalized();
		const Vector3 right = attachments.camera->get_global_transform().basis.get_column(0).normalized();

        // Combine vectors based on input direction
        actor_vars.wishDir = forward * actor_vars.inputDir.y + right * actor_vars.inputDir.x;
		if(!is_on_floor())actor_vars.wishDir.y += -9.8f;
	}
	else {
		actor_vars.wishDir = Vector3(0,0,0);
	}

	set_velocity(actor_vars.wishDir * actor_vars.speed);


	UtilityFunctions::print("WishDir: " + actor_vars.wishDir + " | MoveDir: " + actor_vars.inputDir);

}

void CONST_INT::ActorBase::MakeAttachments() {
	if (actor_vars.initialized)
		return;

	CreateCollider();
	CreateHeadHorizontal();
	CreateHeadVertical();
	CreateCamera();
	CreateBody();
	CreateStepRays();

	actor_vars.initialized = true;
}
void CONST_INT::ActorBase::SetMouseMode(Input::MouseMode _mode) {
	e_input->set_mouse_mode(_mode);
}

void CONST_INT::ActorBase::ApplyGravity(const double delta) {
	const auto gravity = Vector3(0.0, -9.8, 0.0); // You can make this a member variable to adjust gravity as needed
	Vector3 v = get_velocity();
	v.y += gravity.y * delta;
	set_velocity(v);
}
bool CONST_INT::ActorBase::IsSurfaceTooSteep(Vector3 _normal) {
	return _normal.angle_to(Vector3(0.0f, 1.0f, 0.0f)) > get_floor_max_angle();
}


void CONST_INT::ActorBase::CreateCollider() {
	attachments.collider = new CollisionShape3D();
	attachments.collider->set_name("_col");

	Ref<CylinderShape3D> colShape;
	colShape.instantiate();
	colShape->set_height(2.0f);
	colShape->set_radius(0.5f);

	attachments.collider->set_shape(colShape);
	attachments.collider->set_position(Vector3(0.0f, 1.0f, 0.0f));
	this->add_child(attachments.collider);
}
void CONST_INT::ActorBase::CreateHeadHorizontal() {
	attachments.head_h = new Node3D;
	attachments.head_h->set_name("_head_h");
	attachments.head_h->set_position(Vector3(0.0f, 1.0f, 0.0f));
	attachments.collider->add_child(attachments.head_h);
}
void CONST_INT::ActorBase::CreateHeadVertical() {
	attachments.head_v = new Node3D;
	attachments.head_v->set_name("_head_v");
	attachments.head_v->set_position(Vector3(0.0f, 0.0f, 0.0f));
	attachments.head_h->add_child(attachments.head_v);
}
void CONST_INT::ActorBase::CreateCamera() {

	attachments.camera = new Camera3D;
	attachments.camera->set_name("_camera");
	attachments.head_v->add_child(attachments.camera);
}
void CONST_INT::ActorBase::CreateBody() {
	attachments.body = new MeshInstance3D;
	attachments.body->set_name("_body");
	attachments.body->set_cast_shadows_setting(godot::GeometryInstance3D::ShadowCastingSetting::SHADOW_CASTING_SETTING_ON);
	attachments.body->set_position(Vector3(0.0f, 0.0f, 0.0f));
	attachments.collider->add_child(attachments.body);Ref<MeshLibrary> meshLibrary = ResourceLoader::get_singleton()->load("res://bin/CONST_INT/Resources/CI_MeshLibrary.tres");
	if (meshLibrary.is_valid())
	{
		const Ref<Mesh> bodyMesh = meshLibrary->get_item_mesh(0);
		attachments.body->set_mesh(bodyMesh);
	}

}
void CONST_INT::ActorBase::CreateStepRays() {
	attachments.stepDownRay = new RayCast3D;
	attachments.stepDownRay->set_name("_stepDownRay");
	attachments.stepDownRay->set_position(Vector3(0.0f, 0.0f, 0.0f));
	attachments.stepDownRay->set_target_position(Vector3(0, -1, 0));
	attachments.body->add_child(attachments.stepDownRay);

	attachments.stepAheadRay = new RayCast3D;
	attachments.stepAheadRay->set_name("_stepAheadRay");
	attachments.stepAheadRay->set_position(Vector3(0.0f, 0.55f, -0.55f));
	attachments.stepAheadRay->set_target_position(Vector3(0, -0.55f, 0));
	attachments.stepAheadRay->set_target_position(Vector3(0, -0.55f, 0));
	attachments.body->add_child(attachments.stepAheadRay);
}
bool CONST_INT::ActorBase::RunBodyTest(Transform3D from, Vector3 motion, Ref<PhysicsTestMotionResult3D> result) {
	auto* params = new PhysicsTestMotionParameters3D;
	params->set_from(from);
	params->set_motion(motion);
	return physicsServer->body_test_motion(get_rid(), params, result);
}
void CONST_INT::ActorBase::SnapDownToStairsCheck() {
	bool did_snap = false;
	uint64_t was_on_floor_last_frame = Engine().get_physics_frames() - actor_vars._last_frame_was_on_floor == 1;

	if(!is_on_floor() && get_velocity().y <= 0 && (was_on_floor_last_frame || actor_vars._snapped_to_stairs_last_frame))
	{
		PhysicsTestMotionResult3D* body_test_result = new PhysicsTestMotionResult3D();
		if(RunBodyTest(get_global_transform(), Vector3(0, -actor_vars.max_step_height, 0), body_test_result))
		{
			float translate_y = body_test_result->get_travel().y;
			Vector3 pos = get_position();
			pos.y += translate_y;
			set_position(pos);
			apply_floor_snap();
			did_snap = true;
		}
		actor_vars._snapped_to_stairs_last_frame = did_snap;
	}
}
