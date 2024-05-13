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
	CharacterBody3D::_ready();
	ActorBase::MakeAttachments();
	ActorBase::physicsServer = PhysicsServer3D::get_singleton();
}
void CONST_INT::ActorBase::_physics_process(double delta) {
	ApplyGravity(delta);
	move_and_slide();
}
void CONST_INT::ActorBase::_unhandled_input(const godot::Ref<godot::InputEvent> &p_event) {
	CharacterBody3D::_unhandled_input(p_event);
}
void CONST_INT::ActorBase::MouseLook(double delta) {
}
godot::Vector3 CONST_INT::ActorBase::CalculateWishDirection() {
	return godot::Vector3();
}
void CONST_INT::ActorBase::MakeAttachments() {
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
	attachments.body->set_position(Vector3(0.0f, 0.0f, 0.0f));
	attachments.collider->add_child(attachments.body);

	Ref<MeshLibrary> meshLibrary = ResourceLoader::get_singleton()->load("res://bin/CONST_INT/Resources/CI_MeshLibrary.tres");
	if(meshLibrary.is_valid())
	{

		Ref<Mesh> bodyMesh = meshLibrary->get_item_mesh(0);
		attachments.body->set_mesh(bodyMesh);
	}


}
void CONST_INT::ActorBase::ApplyGravity(double delta) {
	Vector3 gravity = Vector3(0.0, -9.8, 0.0); // You can make this a member variable to adjust gravity as needed
	Vector3 v = get_velocity();
	v += gravity * (float)delta;
	set_velocity(v);
}