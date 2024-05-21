//
// Created by IonTheDev on 5/12/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//
#include "ActorBase.h"

void CONST_INT::ActorBase::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_Settings"), &CONST_INT::ActorBase::get_Settings);
	ClassDB::bind_method(D_METHOD("set_Settings", "_settings"), &ActorBase::set_Settings);
	ClassDB::add_property("ActorBase", PropertyInfo(Variant::Type(), "Settings"), "set_Settings", "get_Settings");

}
void CONST_INT::ActorBase::_process(const double delta) {
	CharacterBody3D::_process(delta);
}
void CONST_INT::ActorBase::_ready() {
	MakeAttachments();
	physicsServer = PhysicsServer3D::get_singleton();
	e_input = Input::get_singleton();
	actor_vars.speed = 3.0f;
	actor_vars.mouse_sensitivity = 0.19f;
	SetMouseMode(Input::MOUSE_MODE_CAPTURED);
}
void CONST_INT::ActorBase::_physics_process(const double delta) {
	CI_Move();
	SmoothCamera(delta);
}
void CONST_INT::ActorBase::_unhandled_input(const Ref<InputEvent> &p_event) {
	if (p_event->is_class("InputEventMouseMotion")) {
		auto *mouseMotionEvent = dynamic_cast<InputEventMouseMotion *>(*p_event);
		MouseLook(mouseMotionEvent);
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

void CONST_INT::ActorBase::CalculateWishDirection() {

	if (Engine::get_singleton()->is_editor_hint())
		return;

	actor_vars.inputDir = e_input->get_vector("MoveLeft","MoveRight","MoveBackward","MoveForward").normalized();
	Vector3 v = get_velocity();

	if(actor_vars.inputDir != Vector2(0,0)) {
		const Vector3 forward = -attachments.head_h->get_transform().basis.get_column(2).normalized();
		const Vector3 right = attachments.camera->get_global_transform().basis.get_column(0).normalized();

		const Vector3 _dir = forward * actor_vars.inputDir.y + right * actor_vars.inputDir.x;
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
	if (actor_vars.initialized)
		return;

	CreateCollider();
	CreateSkull();
	CreateHeadHorizontal();
	CreateHeadVertical();
	CreateCamera();
	//CreateBody();
	CreateStepRays();

	actor_vars.initialized = true;
}
void CONST_INT::ActorBase::SetMouseMode(const Input::MouseMode _mode) const {
	e_input->set_mouse_mode(_mode);
}

void CONST_INT::ActorBase::ApplyGravity(const double delta) {

	if(is_on_floor()) return;
	Vector3 v = get_velocity();
	v.y -= actor_vars.gravity * static_cast<float>(delta);
	set_velocity(v);

}

void CONST_INT::ActorBase::ProcessJump(const double delta) {

	if(Engine().is_editor_hint()) return;
	//if(!settings->get_CanJump()) return;
	if(e_input->is_action_just_pressed("Jump"))
	{
	Vector3 v = get_velocity();
	v.y = actor_vars.jump_velocity;
	set_velocity(v);
	}

}

bool CONST_INT::ActorBase::IsSurfaceTooSteep(const Vector3 _normal) const {
	return _normal.angle_to(Vector3(0.0f, 1.0f, 0.0f)) > get_floor_max_angle();
}


void CONST_INT::ActorBase::CreateCollider() {
	attachments.collider = new CollisionShape3D();
	attachments.collider->set_name("_col");

	Ref<CapsuleShape3D> colShape;
	colShape.instantiate();
	colShape->set_height(2.0f);
	colShape->set_radius(0.5f);
	actor_vars.original_height = static_cast<float>(colShape->get_height());
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
	attachments.body->set_cast_shadows_setting(GeometryInstance3D::ShadowCastingSetting::SHADOW_CASTING_SETTING_ON);
	attachments.body->set_position(Vector3(0.0f, 0.0f, 0.0f));
	attachments.collider->add_child(attachments.body);
	if (const Ref<MeshLibrary> meshLibrary = ResourceLoader::get_singleton()->load("res://bin/CONST_INT/Resources/CI_MeshLibrary.tres"); meshLibrary.is_valid())
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
	const bool floor_below = attachments.stepDownRay->is_colliding() && !IsSurfaceTooSteep(attachments.stepDownRay->get_collision_normal());
	bool was_on_floor_last_frame = Engine().get_physics_frames() == actor_vars._last_frame_was_on_floor;
	if(!is_on_floor() && get_velocity().y <= 0 && (was_on_floor_last_frame || actor_vars._snapped_to_stairs_last_frame) && floor_below)
	{
		Ref<KinematicCollision3D> body_test_result = new KinematicCollision3D();
		if(test_move(get_global_transform(), Vector3(0, -actor_vars.max_step_height, 0), body_test_result))
		{
			SaveCamPosForSmoothing();
			{
				float translate_y = body_test_result->get_travel().y;
				Vector3 pos = get_position();
				pos.y += translate_y;
				set_position(pos);
				apply_floor_snap();
				did_snap = true;
			}
		}
	}
	actor_vars._snapped_to_stairs_last_frame = did_snap;

}
bool CONST_INT::ActorBase::StepUpStairsCheck(const double delta) {
	if (!is_on_floor() && !actor_vars._snapped_to_stairs_last_frame)
		return false;
	const Vector3 expected_move_motion = get_velocity() * Vector3(1,0,1) * static_cast<float>(delta);

	//Makes sure you can't step up if something is blocking you
	const Transform3D step_pos_with_clearance = get_global_transform().translated(expected_move_motion + Vector3(0, actor_vars.max_step_height *2, 0));
	if (auto *down_check_result = new KinematicCollision3D(); test_move(step_pos_with_clearance, Vector3(0, -actor_vars.max_step_height*2.0f, 0), down_check_result))
	{
		//how much higher is the step_height
		const float step_height = (step_pos_with_clearance.origin + down_check_result->get_travel() - get_global_position()).y;
		if(step_height > actor_vars.max_step_height || step_height <= 0.01f || (down_check_result->get_position() - get_global_position()).y > actor_vars.max_step_height) return false;
		attachments.stepAheadRay->set_global_position(down_check_result->get_position() + Vector3(0, actor_vars.max_step_height, 0) + expected_move_motion.normalized() * 0.025f);
		attachments.stepAheadRay->force_raycast_update();
		//UtilityFunctions::print(step_height);
		if(attachments.stepAheadRay->is_colliding() && !IsSurfaceTooSteep(attachments.stepAheadRay->get_collision_normal()))
		{

			SaveCamPosForSmoothing();
			set_global_position(step_pos_with_clearance.origin + down_check_result->get_travel());
			apply_floor_snap();
			actor_vars._snapped_to_stairs_last_frame = true;
			return true;
		}
	}
	return false;
}
void CONST_INT::ActorBase::CI_Move() {
	const double delta = get_physics_process_delta_time();
	actor_vars.speed = GetMoveSpeed();
	HandleCrouch(delta);
	if(!is_on_floor())
	{
		HandleAirPhysics(delta);
	}
	else
	{

		HandleGroundPhysics(delta);
	}

}
float CONST_INT::ActorBase::GetMoveSpeed() const { //This is supposed to be ugly for right now
	if (actor_vars.is_crouched)
		return 1.5f;
	return 3.0f;
}


void CONST_INT::ActorBase::HandleCrouch(double delta) {


	if(Engine::get_singleton()->is_editor_hint()) return;
	//if(!settings->get_CanCrouch()) return;
	bool was_crouched_last_frame = actor_vars.is_crouched;



	Vector3 colPos = attachments.collider->get_position();
	Ref<CapsuleShape3D> colShape = attachments.collider->get_shape();

	if(e_input->is_action_pressed("Crouch"))
	{
		actor_vars.is_crouched = true;
	}
	else if (actor_vars.is_crouched && !test_move(get_transform(), Vector3(0, actor_vars.crouch_translate,0)))
	{
		actor_vars.is_crouched = false;
	}

	float translate_y_if_possible = 0;

	if(was_crouched_last_frame != actor_vars.is_crouched && !is_on_floor() && !actor_vars._snapped_to_stairs_last_frame)
	{
		translate_y_if_possible = (actor_vars.is_crouched) ? actor_vars.crouch_jump_add : -actor_vars.crouch_jump_add;
	}

	Vector3 cPos = attachments.skull->get_position();
	if(translate_y_if_possible != 0)
	{
		Ref<KinematicCollision3D> result = new KinematicCollision3D();
		test_move(get_transform(), Vector3(0, translate_y_if_possible, 0), result);
		Vector3 pos = get_position();
		pos.y += result->get_travel().y;
		set_position(pos);
		cPos.y -= result->get_travel().y;
		cPos.y = Math::clamp(cPos.y, -actor_vars.crouch_translate, 1.0f);
		attachments.skull->set_position(cPos);
	}


	attachments.skull->set_position(Vector3(0, Math::move_toward(attachments.skull->get_position().y, (actor_vars.is_crouched) ? actor_vars.crouch_translate : 1 , 3.0f * (float)delta),0));
	colShape->set_height((actor_vars.is_crouched) ? actor_vars.original_height - actor_vars.crouch_translate : actor_vars.original_height);

	attachments.collider->set_shape(colShape);
	colPos.y = colShape->get_height() / 2;
	attachments.collider->set_position(colPos);
	//UtilityFunctions::print(actor_vars._snapped_to_stairs_last_frame);

}
void CONST_INT::ActorBase::HandleGroundPhysics(double delta) {
	actor_vars._last_frame_was_on_floor = Engine().get_physics_frames();
	CalculateWishDirection();
	ProcessJump(delta);
	if(!StepUpStairsCheck(delta))
	{
		PushAwayRigidBodies();

		move_and_slide();

		SnapDownToStairsCheck();
	}

	HeadBob(delta);
}
void CONST_INT::ActorBase::HandleAirPhysics(double delta) {
	move_and_slide();
	ApplyGravity(delta);
}
void CONST_INT::ActorBase::SaveCamPosForSmoothing() {
	if(SavedCameraPos != attachments.head_h->get_position())
	{
		SavedCameraPos = attachments.head_h->get_global_position();
	}
}
void CONST_INT::ActorBase::SmoothCamera(double delta) {
	if(SavedCameraPos == attachments.head_h->get_position()) return;
	attachments.head_h->set_global_position(SavedCameraPos);
	Vector3 camSmoothPos = attachments.camera->get_position();
	camSmoothPos.y = Math::clamp(attachments.camera->get_position().y, -actor_vars.crouch_translate, actor_vars.crouch_translate);
	float moveAmount = Math::max(get_velocity().length() * (float)delta, actor_vars.speed/2 * (float)delta);
	camSmoothPos.y = Math::move_toward(camSmoothPos.y, 0.0f, moveAmount);
	attachments.head_h->set_position(camSmoothPos);
	camSmoothPos = attachments.head_h->get_position();
	SavedCameraPos = attachments.head_h->get_global_position();
	if(camSmoothPos.y == 0)
	{
		SavedCameraPos = attachments.head_h->get_position();
	}
}
void CONST_INT::ActorBase::HeadBob(double delta) {
	actor_vars.headbob_time += (float)delta * get_velocity().length();
	Transform3D _t = attachments.camera->get_transform();
	Vector3 o = _t.origin;

	double t = actor_vars.headbob_time;
	double f = actor_vars.headbob_frequency;
	double a = actor_vars.headbob_amount;

	double x = cos(t * f * 0.5f) * a;
	double y = sin(t * f) * a;
	o = Vector3((float)x, (float)y ,0);
	_t.set_origin(o);
	attachments.camera->set_transform(_t);
}
void CONST_INT::ActorBase::PushAwayRigidBodies() {
	for(int i = 0; i < get_slide_collision_count(); i++)
	{
		Ref<KinematicCollision3D> c = get_slide_collision(i);
		if(c->get_collider()->is_class("RigidBody3D"))
		{
			RigidBody3D *rb = Object::cast_to<RigidBody3D>(c->get_collider());
			Vector3 push_dir = -c->get_normal();
			real_t velocity_diff_in_push_dir = get_velocity().dot(push_dir) - rb->get_linear_velocity().dot(push_dir);
			velocity_diff_in_push_dir = Math::max(0.0f, velocity_diff_in_push_dir);

			const float my_mass = 1.25f;
			float mass_ratio = Math::min(1.0f, my_mass / (float)rb->get_mass());
			push_dir.y = 0;
			float push_force = mass_ratio * 5.0f;
			rb->apply_impulse(push_dir * velocity_diff_in_push_dir * push_force, rb->get_position() - rb->get_global_position());
		}
	}
}
godot::Ref<ActorSettings> *CONST_INT::ActorBase::get_Settings() {
	return settings;
}
void CONST_INT::ActorBase::set_Settings(godot::Ref<ActorSettings> *_settings) {
	settings = _settings;
}
