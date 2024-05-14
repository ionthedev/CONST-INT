//
// Created by IonTheDev on 5/12/24.
// Copyright (c) 2024 Friendly Studios, LLC. All rights reserved.
//
#include "ActorBase.h"

void CONST_INT::ActorBase::_bind_methods() {

}
void CONST_INT::ActorBase::_process(double delta) {
	CharacterBody3D::_process(delta);
}
void CONST_INT::ActorBase::_ready() {
	ActorBase::MakeAttachments();
	ActorBase::physicsServer = PhysicsServer3D::get_singleton();
	e_input = Input::get_singleton();
	actor_vars.speed = 3.0f;
	actor_vars.mouse_sensitivity = 0.19f;
}
void CONST_INT::ActorBase::_physics_process(double delta) {
	ApplyGravity(delta);
	CalculateWishDirection(delta);

	move_and_slide();
}
void CONST_INT::ActorBase::_unhandled_input(const godot::Ref<godot::InputEvent> &p_event) {
	if(p_event->is_class("InputEventMouseMotion")) {
		InputEventMouseMotion *mouseMotionEvent = static_cast<InputEventMouseMotion *>(*p_event);
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
	actor_vars.mouse_rotation.z = Math::lerp(actor_vars.mouse_rotation.z, 0.0f, (float)get_physics_process_delta_time() * 7.0f);

	Transform3D t = attachments.head_v->get_transform();
	t.basis = get_basis();
	attachments.head_v->set_transform(t);

	attachments.head_v->rotate_object_local(Vector3(1, 0, 0), actor_vars.mouse_rotation.x);

	UtilityFunctions::print(actor_vars.mouse_motion);

}
void CONST_INT::ActorBase::CalculateWishDirection(double delta) {

	if (Engine::get_singleton()->is_editor_hint())
		return;

	actor_vars.inputDir = e_input->get_vector("MoveRight","MoveLeft","MoveBackward","MoveForward").normalized();


	if(actor_vars.inputDir != Vector2(0,0)) {
		actor_vars.wishDir = (attachments.camera->get_basis().rows[2] * Vector3(actor_vars.inputDir.x, 0, actor_vars.inputDir.y).normalized());

		set_velocity(actor_vars.wishDir * actor_vars.speed);
	}



	UtilityFunctions::print("WishDir: " + actor_vars.wishDir + " | MoveDir: " + actor_vars.inputDir);

}
void CONST_INT::ActorBase::MakeAttachments() {
	if(actor_vars.initialized) return;
	//Collision Creation
	attachments.collider = new CollisionShape3D();
	attachments.collider->set_name("_col");

	Ref<CylinderShape3D> colShape;
	colShape.instantiate();
	colShape->set_height(2.0f);
	colShape->set_radius(0.5f);

	attachments.collider->set_shape(colShape);
	attachments.collider->set_position(Vector3(0.0f, 1.0f, 0.0f));
	this->add_child(attachments.collider);


	//horizontal head creation;
	attachments.head_h = new Node3D;
	attachments.head_h->set_name("_head_h");
	attachments.head_h->set_position(Vector3(0.0f, 1.75f, 0.0f));
	attachments.collider->add_child(attachments.head_h);

	//vertical head creation
	attachments.head_v = new Node3D;
	attachments.head_v->set_name("_head_v");
	attachments.head_v->set_position(Vector3(0.0f, 0.0f, 0.0f));
	attachments.head_h->add_child(attachments.head_v);

	//camera creation
	attachments.camera = new Camera3D;
	attachments.camera->set_name("_camera");
	attachments.head_v->add_child(attachments.camera);

	//body creation
	attachments.body = new MeshInstance3D;
	attachments.body->set_name("_body");
	attachments.body->set_cast_shadows_setting(godot::GeometryInstance3D::ShadowCastingSetting::SHADOW_CASTING_SETTING_ON);
	attachments.body->set_position(Vector3(0.0f, 0.0f, 0.0f));
	attachments.collider->add_child(attachments.body);
	actor_vars.initialized = true;

	Ref<MeshLibrary> meshLibrary = ResourceLoader::get_singleton()->load("res://bin/CONST_INT/Resources/CI_MeshLibrary.tres");
	if(meshLibrary.is_valid())
	{

		Ref<Mesh> bodyMesh = meshLibrary->get_item_mesh(0);
		attachments.body->set_mesh(bodyMesh);
	}


}

void CONST_INT::ActorBase::ApplyGravity(double delta) {
	if(is_on_floor()) return;
	Vector3 gravity = Vector3(0.0, -9.8, 0.0); // You can make this a member variable to adjust gravity as needed
	UpdateVelocity(gravity, delta);
}
void CONST_INT::ActorBase::UpdateVelocity(Vector3 newV,double delta) {

	Vector3 v = get_velocity();
	v += newV * (float)delta;
	set_velocity(v);
}
