//
// Created by IonTheDev on 6/16/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//

#include "Player.h"


void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_Settings"), &Player::get_Settings);
	ClassDB::bind_method(D_METHOD("set_Settings", "_settings"), &Player::set_Settings);
	ClassDB::add_property("Player", PropertyInfo(Variant::OBJECT, "settings", PROPERTY_HINT_RESOURCE_TYPE, "ActorSettings"), "set_Settings", "get_Settings");
	ClassDB::bind_method(D_METHOD("MouseLook", "p_event"), &Player::MouseLook);
	ClassDB::bind_method(D_METHOD("CalculateDirection"), &Player::CalculateDirection);
	ClassDB::bind_method(D_METHOD("MakeAttachments"), &Player::MakeAttachments);
	ClassDB::bind_method(D_METHOD("ApplyGravity", "delta"), &Player::ApplyGravity);
	ClassDB::bind_method(D_METHOD("ProcessJump"), &Player::ProcessJump);
	ClassDB::bind_method(D_METHOD("SetMouseMode", "_mode"), &Player::SetMouseMode);
	ClassDB::bind_method(D_METHOD("IsSurfaceTooSteep", "_normal"), &Player::IsSurfaceTooSteep);
	ClassDB::bind_method(D_METHOD("HandleGroundPhysics", "delta"), &Player::HandleGroundPhysics);
	ClassDB::bind_method(D_METHOD("HandleAirPhysics", "delta"), &Player::HandleAirPhysics);
	ClassDB::bind_method(D_METHOD("HandleLadderPhysics"), &Player::HandleLadderPhysics);
	ClassDB::bind_method(D_METHOD("SnapDownToStairsCheck"), &Player::SnapDownToStairsCheck);
	ClassDB::bind_method(D_METHOD("StepUpStairsCheck", "delta"), &Player::StepUpStairsCheck);
	ClassDB::bind_method(D_METHOD("PushAwayRigidBodies"), &Player::PushAwayRigidBodies);
	ClassDB::bind_method(D_METHOD("CI_Move"), &Player::CI_Move);
	ClassDB::bind_method(D_METHOD("SaveCamPosForSmoothing"), &Player::SaveCamPosForSmoothing);
	ClassDB::bind_method(D_METHOD("SmoothCamera", "delta"), &Player::SmoothCamera);
	ClassDB::bind_method(D_METHOD("HeadBob", "delta"), &Player::HeadBob);
	ClassDB::bind_method(D_METHOD("HandleCrouch", "delta"), &Player::HandleCrouch);
	ClassDB::bind_method(D_METHOD("CreateCollider"), &Player::CreateCollider);
	ClassDB::bind_method(D_METHOD("CreateSkull"), &Player::CreateSkull);
	ClassDB::bind_method(D_METHOD("CreateHeadHorizontal"), &Player::CreateHeadHorizontal);
	ClassDB::bind_method(D_METHOD("CreateHeadVertical"), &Player::CreateHeadVertical);
	ClassDB::bind_method(D_METHOD("CreateCamera"), &Player::CreateCamera);
	ClassDB::bind_method(D_METHOD("CreateBody"), &Player::CreateBody);
	ClassDB::bind_method(D_METHOD("CreateStepRays"), &Player::CreateStepRays);

}

void Player::_process(const double delta) {
	CharacterBody3D::_process(delta);
}
void Player::_ready() {
	MakeAttachments();
	physicsServer = PhysicsServer3D::get_singleton();
	e_input = Input::get_singleton();
	actor_vars.speed = 3.0f;
	actor_vars.mouse_sensitivity = 0.19f;
	SetMouseMode(Input::MOUSE_MODE_CAPTURED);
}
void Player::_physics_process(const double delta) {
	CI_Move();
	SmoothCamera(delta);
}
void Player::_unhandled_input(const Ref<InputEvent> &p_event) {
	if (p_event->is_class("InputEventMouseMotion")) {
		auto *mouseMotionEvent = dynamic_cast<InputEventMouseMotion *>(*p_event);
		MouseLook(mouseMotionEvent);
	}
}

void Player::MouseLook(const Ref<InputEventMouseMotion> &p_event) {

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

void Player::CalculateDirection() {

	if (Engine::get_singleton()->is_editor_hint())
		return;

	actor_vars.inputDir = e_input->get_vector("MoveLeft","MoveRight","MoveBackward","MoveForward").normalized();
	Vector3 v = get_velocity();

	if(actor_vars.inputDir != Vector2(0,0)) {
		const Vector3 forward = -attachments.head_h->get_transform().basis.get_column(2).normalized();
		const Vector3 right = attachments.camera->get_global_transform().basis.get_column(0).normalized();

		const Vector3 _dir = forward * actor_vars.inputDir.y + right * actor_vars.inputDir.x;
        // Combine vectors based on input direction
        actor_vars.moveDir.x = _dir.x * actor_vars.speed;
		actor_vars.moveDir.z = _dir.z * actor_vars.speed;

		actor_vars.wishDir = get_transform().basis.xform(Vector3(actor_vars.moveDir.x, 0, -actor_vars.moveDir.z));
	}
	else {
		actor_vars.moveDir = Vector3(0,0,0);
	}

	v.x = actor_vars.moveDir.x;
	v.z = actor_vars.moveDir.z;
	set_velocity(v);



}

void Player::MakeAttachments() {
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
void Player::SetMouseMode(const Input::MouseMode _mode) const {
	if(Engine().is_editor_hint()) return;
	e_input->set_mouse_mode(_mode);
}

void Player::ApplyGravity(const double delta) {

	if(is_on_floor()) return;
	Vector3 v = get_velocity();
	v.y -= actor_vars.gravity * static_cast<float>(delta);
	set_velocity(v);

}

void Player::ProcessJump() {

	if(Engine().is_editor_hint()) return;
	if(!settings->get_CanJump()) return;
	if(e_input->is_action_just_pressed("Jump"))
	{
	Vector3 v = get_velocity();
	v.y = actor_vars.jump_velocity;
	set_velocity(v);
	}

}

bool Player::IsSurfaceTooSteep(const Vector3 _normal) const {
	return _normal.angle_to(Vector3(0.0f, 1.0f, 0.0f)) > get_floor_max_angle();
}


void Player::CreateCollider() {
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

void Player::CreateSkull() {
	attachments.skull = new Node3D;
	attachments.skull->set_name("skull");
	attachments.skull->set_position(Vector3(0.0f, 1.0f, 0.0f));
	attachments.collider->add_child(attachments.skull);
}


void Player::CreateHeadHorizontal() {
	attachments.head_h = new Node3D;
	attachments.head_h->set_name("_head_h");
	attachments.head_h->set_position(Vector3(0.0f, 0.0f, 0.0f));
	attachments.skull->add_child(attachments.head_h);
}
void Player::CreateHeadVertical() {
	attachments.head_v = new Node3D;
	attachments.head_v->set_name("_head_v");
	attachments.head_v->set_position(Vector3(0.0f, 0.0f, 0.0f));
	attachments.head_h->add_child(attachments.head_v);
}
void Player::CreateCamera() {

	attachments.camera = new Camera3D;
	attachments.camera->set_name("_camera");
	attachments.head_v->add_child(attachments.camera);
}
void Player::CreateBody() {
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
void Player::CreateStepRays() {
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

void Player::SnapDownToStairsCheck() {
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
bool Player::StepUpStairsCheck(const double delta) {
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
void Player::CI_Move() {
	const double delta = get_physics_process_delta_time();
	if(Engine::get_singleton()->is_editor_hint()) return;
	actor_vars.speed = GetMoveSpeed();
	if(!HandleLadderPhysics())
	{

	if(!is_on_floor())
	{
			HandleAirPhysics(delta);
	}
	else
	{

		HandleGroundPhysics(delta);
	}

	HandleCrouch(delta);

	}
}
float Player::GetMoveSpeed() const { //This is supposed to be ugly for right now
	if (actor_vars.is_crouched)
		return settings->get_CrouchSpeed();

	if(e_input->is_action_pressed("Sprint") && settings->get_CanSprint())
		return settings->get_SprintSpeed();
	return settings->get_WalkSpeed();
}


void Player::HandleCrouch(double delta) {


	if(Engine::get_singleton()->is_editor_hint()) return;
	if(!settings->get_CanCrouch()) return;
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
	colPos.y = (float)colShape->get_height() / 2.0f;
	attachments.collider->set_position(colPos);
	//UtilityFunctions::print(actor_vars._snapped_to_stairs_last_frame);

}
void Player::HandleGroundPhysics(double delta) {
	actor_vars._last_frame_was_on_floor = Engine().get_physics_frames();
	CalculateDirection();
	ProcessJump();
	if(!StepUpStairsCheck(delta))
	{
		PushAwayRigidBodies();

		move_and_slide();

		SnapDownToStairsCheck();
	}

	HeadBob(delta);
}
void Player::HandleAirPhysics(double delta) {
	move_and_slide();
	ApplyGravity(delta);
}
void Player::SaveCamPosForSmoothing() {
	if(SavedCameraPos != attachments.head_h->get_position())
	{
		SavedCameraPos = attachments.head_h->get_global_position();
	}
}
void Player::SmoothCamera(double delta) {
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
void Player::HeadBob(double delta) {
	actor_vars.headbob_time += (float)delta * get_velocity().length();
	Transform3D _t = attachments.camera->get_transform();
	Vector3 o;

	double t = actor_vars.headbob_time;
	double f = actor_vars.headbob_frequency;
	double a = actor_vars.headbob_amount;

	double x = cos(t * f * 0.5f) * a;
	double y = sin(t * f) * a;
	o = Vector3((float)x, (float)y ,0);
	_t.set_origin(o);
	attachments.camera->set_transform(_t);
}
void Player::PushAwayRigidBodies() {
	for(int i = 0; i < get_slide_collision_count(); i++)
	{
		Ref<KinematicCollision3D> c = get_slide_collision(i);
		if(c->get_collider()->is_class("RigidBody3D"))
		{
			auto *rb = Object::cast_to<RigidBody3D>(c->get_collider());
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

void Player::InteractionCast() {
	Camera3D cam = *attachments.camera;
	PhysicsDirectSpaceState3D space_state = *cam.get_world_3d()->get_direct_space_state();
	/*Ref<Viewport> viewport = get_tree()->get_root();
	Vector2 viewport_size = viewport->get_visible_rect().size;
	Vector2 screen_center = viewport_size / 2;
	Vector3 origin = cam.project_ray_normal(screen_center);
	Vector3 end = origin + cam.project_ray_normal(screen_center) * get_Settings()->get_interactDistance();
	Ref<PhysicsRayQueryParameters3D> query = PhysicsRayQueryParameters3D::create(origin, end);
	query->set_collide_with_bodies(true);
	Dictionary result = space_state.intersect_ray(query);*/
}

Ref<ActorSettings> Player::get_Settings() const {
	return settings;
}
void Player::set_Settings(const Ref<ActorSettings> &_settings) {
	settings = _settings;
}
bool Player::HandleLadderPhysics() {
	bool was_climbing_ladder = actor_vars.currentLadder && actor_vars.currentLadder->overlaps_body(this);
	CalculateDirection();

	// Check if we are currently climbing a ladder. If not, check if we are overlapping a ladder
	if (!was_climbing_ladder) {
		actor_vars.currentLadder = nullptr;
		SceneTree *scene = get_tree();
		TypedArray<Node> ladder_group = scene->get_nodes_in_group("ladder_area3d");
		for (int i = 0; i < ladder_group.size(); i++) {
			auto *ladder = Object::cast_to<Area3D>(ladder_group[i]);
			if (ladder && ladder->overlaps_body(this)) {
				actor_vars.currentLadder = ladder;
				break;
			}
		}
	}
	if (actor_vars.currentLadder == nullptr)
		return false;

	// Variable creation for ladder calculations
	Transform3D ladder_global_t = actor_vars.currentLadder->get_global_transform();
	Vector3 rel_pos_to_ladder = ladder_global_t.affine_inverse().xform(get_global_position());

	float forward_move = actor_vars.inputDir.y;
	float side_move = actor_vars.inputDir.x;

	// Transform these movements to the ladder's local space
	Vector3 ladder_forward_move = ladder_global_t.affine_inverse().basis.xform(attachments.camera->get_global_transform().basis.xform(Vector3(0,0,-forward_move)));
	Vector3 ladder_side_move = ladder_global_t.affine_inverse().basis.xform(attachments.camera->get_global_transform().basis.xform(Vector3(side_move,0,0)));

	// Calculate strafing and climbing velocities
	float ladder_strafe_vel = settings->get_ClimbSpeed() * (ladder_side_move.x + ladder_forward_move.x);
	float ladder_climb_vel = settings->get_ClimbSpeed() * -ladder_forward_move.z;

	// Camera bias checks to determine if the player wants to move up or down the ladder
	float cam_forward_amount = attachments.camera->get_global_transform().basis.get_column(2).normalized().dot(actor_vars.currentLadder->get_basis().get_column(2).normalized());
	float up_wish = Vector3(0, 1, 0).rotated(Vector3(1, 0, 0), Math::deg_to_rad(-45 * cam_forward_amount)).dot(ladder_forward_move);
	ladder_climb_vel += settings->get_ClimbSpeed() * up_wish;


	// Only climb ladder when moving towards ladder and not being trapped forever within its bounds.
	bool should_dismount = false;
	if(!was_climbing_ladder)
	{
		bool mounting_from_top = rel_pos_to_ladder.y > actor_vars.currentLadder->get_node<Node3D>("Ladder_Top")->get_position().y;
		if(mounting_from_top)
		{
			if(ladder_climb_vel > 0) should_dismount = true;
		}
		else
		{
			// If not mounting from top, they are either falling or on the floor
			if(ladder_global_t.affine_inverse().basis.xform(actor_vars.wishDir).z >= 0) should_dismount = true;
		}

		// Only stick to ladder if close

		if(Math::abs(rel_pos_to_ladder.z) > 0.1f) should_dismount = true;
	}

	if(is_on_floor() && ladder_climb_vel <= 0) should_dismount = true;

	if(should_dismount)
	{
		actor_vars.currentLadder = nullptr;
		return false;
	}

	if(was_climbing_ladder && e_input->is_action_just_pressed("Jump"))
	{
		actor_vars.velocity = ladder_global_t.basis.get_column(Vector3::AXIS_Z) * settings->get_jumpForce() * 1.5f;

		actor_vars.currentLadder = nullptr;
		return false;
	}

	// Apply the calculated velocity
	set_velocity(ladder_global_t.basis.xform(Vector3(ladder_strafe_vel, ladder_climb_vel, 0)));

	// Adjust the position to remain aligned with the ladder
	rel_pos_to_ladder.z = 0; // Ensure the player does not drift along the Z axis
	set_global_position(ladder_global_t.xform(rel_pos_to_ladder));
	move_and_slide();

	return true;
}

