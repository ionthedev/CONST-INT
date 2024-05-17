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
	actor_vars.speed = GetMoveSpeed();
	HandleCrouch(delta);
	CI_Move();
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


}

void CONST_INT::ActorBase::CalculateWishDirection(double delta) {

	if (Engine::get_singleton()->is_editor_hint())
		return;

	actor_vars.inputDir = e_input->get_vector("MoveLeft","MoveRight","MoveBackward","MoveForward").normalized();
	Vector3 v = get_velocity();

	if(actor_vars.inputDir != Vector2(0,0)) {
		const Vector3 forward = -attachments.head_h->get_transform().basis.get_column(2).normalized();
		const Vector3 right = attachments.camera->get_global_transform().basis.get_column(0).normalized();

		Vector3 _dir = forward * actor_vars.inputDir.y + right * actor_vars.inputDir.x;
        // Combine vectors based on input direction
        actor_vars.wishDir.x = _dir.x * actor_vars.speed;
		actor_vars.wishDir.z = _dir.z * actor_vars.speed;
	}
	else {
		actor_vars.wishDir = Vector3(0,0,0);
	}

	v.x = actor_vars.wishDir.x;
	v.z = actor_vars.wishDir.z;
	set_velocity(v);



}

void CONST_INT::ActorBase::MakeAttachments() {
	if (ActorBase::actor_vars.initialized)
		return;

	ActorBase::CreateCollider();
	ActorBase::CreateSkull();
	ActorBase::CreateHeadHorizontal();
	ActorBase::CreateHeadVertical();
	ActorBase::CreateCamera();
	ActorBase::CreateBody();
	ActorBase::CreateStepRays();

	ActorBase::actor_vars.initialized = true;
}
void CONST_INT::ActorBase::SetMouseMode(Input::MouseMode _mode) {
	e_input->set_mouse_mode(_mode);
}

void CONST_INT::ActorBase::ApplyGravity(const double delta) {
	if(is_on_floor()) return;

	Vector3 v = get_velocity();
	v.y += actor_vars.gravity * delta;
	set_velocity(v);

}
bool CONST_INT::ActorBase::IsSurfaceTooSteep(Vector3 _normal) {
	return _normal.angle_to(Vector3(0.0f, 1.0f, 0.0f)) > get_floor_max_angle();
}


void CONST_INT::ActorBase::CreateCollider() {
	attachments.collider = new CollisionShape3D();
	attachments.collider->set_name("_col");

	Ref<CapsuleShape3D> colShape;
	colShape.instantiate();
	colShape->set_height(2.0f);
	colShape->set_radius(0.5f);
	ActorBase::actor_vars.original_height = (float)colShape->get_height();
	attachments.collider->set_shape(colShape);
	attachments.collider->set_position(Vector3(0.0f, 1.0f, 0.0f));
	this->add_child(attachments.collider);
}

void CONST_INT::ActorBase::CreateSkull() {
	attachments.skull = new Node3D;
	attachments.skull->set_name("skull");
	attachments.skull->set_position(Vector3(0.0f, 1.0f, 0.0f));
	attachments.collider->add_child(attachments.skull);
}


void CONST_INT::ActorBase::CreateHeadHorizontal() {
	attachments.head_h = new Node3D;
	attachments.head_h->set_name("_head_h");
	attachments.head_h->set_position(Vector3(0.0f, 0.0f, 0.0f));
	attachments.skull->add_child(attachments.head_h);
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
	add_child(attachments.stepDownRay);

	attachments.stepAheadRay = new RayCast3D;
	attachments.stepAheadRay->set_name("_stepAheadRay");
	attachments.stepAheadRay->set_position(Vector3(0.0f, 0.55f, -0.55f));
	attachments.stepAheadRay->set_target_position(Vector3(0, -0.55f, 0));
	attachments.stepAheadRay->set_target_position(Vector3(0, -0.55f, 0));
	add_child(attachments.stepAheadRay);
}

void CONST_INT::ActorBase::SnapDownToStairsCheck() {
	bool did_snap = false;
	attachments.stepDownRay->force_raycast_update();
	bool floor_below = (attachments.stepDownRay->is_colliding() && !IsSurfaceTooSteep(attachments.stepDownRay->get_collision_normal()));
	uint64_t was_on_floor_last_frame = Engine().get_physics_frames() - actor_vars._last_frame_was_on_floor == 1;

	if(!is_on_floor() && get_velocity().y <= 0 && (was_on_floor_last_frame || actor_vars._snapped_to_stairs_last_frame) && floor_below)
	{

		KinematicCollision3D* body_test_result = new KinematicCollision3D();

		if(test_move(get_global_transform(), Vector3(0, -actor_vars.max_step_height, 0), body_test_result))
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
bool CONST_INT::ActorBase::StepUpStairsCheck(double delta) {
	if(!is_on_floor() && !actor_vars._snapped_to_stairs_last_frame) return false;
	Vector3 expected_move_motion = get_velocity() * Vector3(1,0,1) * (float)delta;

	//Makes sure you can't step up if something is blocking you
	Transform3D step_pos_with_clearance = get_global_transform().translated(expected_move_motion + Vector3(0, actor_vars.max_step_height *2, 0));
	KinematicCollision3D* down_check_result = new KinematicCollision3D();
	if(test_move(step_pos_with_clearance, Vector3(0, -actor_vars.max_step_height*2.0f, 0), down_check_result))
	{
		//how much higher is the step_height
		float step_height = ((step_pos_with_clearance.origin + down_check_result->get_travel()) - get_global_position()).y;
		if(step_height > actor_vars.max_step_height || step_height <= 0.01f || (down_check_result->get_position() - get_global_position()).y > actor_vars.max_step_height) return false;
		attachments.stepAheadRay->set_global_position(down_check_result->get_position() + Vector3(0, actor_vars.max_step_height, 0) + expected_move_motion.normalized() * 0.025f);
		attachments.stepAheadRay->force_raycast_update();
		UtilityFunctions::print(step_height);
		if(attachments.stepAheadRay->is_colliding() && !IsSurfaceTooSteep(attachments.stepAheadRay->get_collision_normal()))
		{
			set_global_position(step_pos_with_clearance.origin + down_check_result->get_travel());
			apply_floor_snap();
			actor_vars._snapped_to_stairs_last_frame = true;
			return true;
		}
	}
	return false;
}
void CONST_INT::ActorBase::CI_Move() {
	double delta = get_physics_process_delta_time();
	if(is_on_floor() || actor_vars._snapped_to_stairs_last_frame) actor_vars._last_frame_was_on_floor = Engine().get_physics_frames();

	ApplyGravity(delta);
	CalculateWishDirection(delta);
	if(!StepUpStairsCheck(delta))
	{

		move_and_slide();

		SnapDownToStairsCheck();
	}

}
float CONST_INT::ActorBase::GetMoveSpeed() {                      //This is supposed to be ugly for right now
	if(actor_vars.is_crouched) 		return (3.0f * 0.8);
	else 					   		return 3.0f;
}
void CONST_INT::ActorBase::HandleCrouch(double delta) {
	actor_vars.is_crouched = e_input->is_action_pressed("Crouch");
	if(actor_vars.is_crouched)
	{
		attachments.skull->set_position(Vector3(0,-actor_vars.crouch_translate, 0));
	}
	else
	{

		attachments.skull->set_position(Vector3(0, 1, 0));
	}

}
