//
// Created by Brandon Friend on 8/27/24.
//

#include "Player.h"
#include "Player.h"

#include <godot_cpp/variant/utility_functions.hpp>



void Player::_bind_methods()
    {

        ClassDB::bind_method(D_METHOD("get_Settings"), &Player::get_Settings);
        ClassDB::bind_method(D_METHOD("set_Settings", "_settings"), &Player::set_Settings);
        ClassDB::add_property("Player", PropertyInfo(Variant::OBJECT, "settings", PROPERTY_HINT_RESOURCE_TYPE, "ActorSettings"), "set_Settings", "get_Settings");


        ClassDB::bind_method(D_METHOD("get_headbob_move_amount"), &Player::get_headbob_move_amount);
        ClassDB::bind_method(D_METHOD("set_headbob_move_amount", "_speed"), &Player::set_headbob_move_amount);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "headbob_move_amount"), "set_headbob_move_amount", "get_headbob_move_amount");

        ClassDB::bind_method(D_METHOD("get_headbob_frequency"), &Player::get_headbob_frequency);
        ClassDB::bind_method(D_METHOD("set_headbob_frequency", "_speed"), &Player::set_headbob_frequency);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "headbob_frequency"), "set_headbob_frequency", "get_headbob_frequency");

        ClassDB::bind_method(D_METHOD("get_headbob_time"), &Player::get_headbob_time);
        ClassDB::bind_method(D_METHOD("set_headbob_time", "_speed"), &Player::set_headbob_time);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "headbob_time"), "set_headbob_time", "get_headbob_time");

        ClassDB::bind_method(D_METHOD("get_walk_speed"), &Player::get_walk_speed);
        ClassDB::bind_method(D_METHOD("set_walk_speed", "_speed"), &Player::set_walk_speed);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "walk_speed"), "set_walk_speed", "get_walk_speed");

        ClassDB::bind_method(D_METHOD("get_sprint_speed"), &Player::get_sprint_speed);
        ClassDB::bind_method(D_METHOD("set_sprint_speed", "_speed"), &Player::set_sprint_speed);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "sprint_speed"), "set_sprint_speed", "get_sprint_speed");

        ClassDB::bind_method(D_METHOD("get_ground_accel"), &Player::get_ground_accel);
        ClassDB::bind_method(D_METHOD("set_ground_accel", "_speed"), &Player::set_ground_accel);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "ground_accel"), "set_ground_accel", "get_ground_accel");

        ClassDB::bind_method(D_METHOD("get_ground_decel"), &Player::get_ground_decel);
        ClassDB::bind_method(D_METHOD("set_ground_decel", "_speed"), &Player::set_ground_decel);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "ground_decel"), "set_ground_decel", "get_ground_decel");

        ClassDB::bind_method(D_METHOD("get_ground_friction"), &Player::get_ground_friction);
        ClassDB::bind_method(D_METHOD("set_ground_friction", "_speed"), &Player::set_ground_friction);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "ground_friction"), "set_ground_friction", "get_ground_friction");

        ClassDB::bind_method(D_METHOD("get_air_cap"), &Player::get_air_cap);
        ClassDB::bind_method(D_METHOD("set_air_cap", "_speed"), &Player::set_air_cap);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "air_cap"), "set_air_cap", "get_air_cap");

        ClassDB::bind_method(D_METHOD("get_air_accel"), &Player::get_air_accel);
        ClassDB::bind_method(D_METHOD("set_air_accel", "_speed"), &Player::set_air_accel);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "air_accel"), "set_air_accel", "get_air_accel");

        ClassDB::bind_method(D_METHOD("get_air_move_speed"), &Player::get_air_move_speed);
        ClassDB::bind_method(D_METHOD("set_air_move_speed", "_speed"), &Player::set_air_move_speed);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "air_move_speed"), "set_air_move_speed", "get_air_move_speed");

        ClassDB::bind_method(D_METHOD("get_gravity"), &Player::get_gravity);
        ClassDB::bind_method(D_METHOD("set_gravity", "_speed"), &Player::set_gravity);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "gravity"), "set_gravity", "get_gravity");

        ClassDB::bind_method(D_METHOD("get_swim_up_speed"), &Player::get_swim_up_speed);
        ClassDB::bind_method(D_METHOD("set_swim_up_speed", "_speed"), &Player::set_swim_up_speed);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "swim_up_speed"), "set_swim_up_speed", "get_swim_up_speed");

        ClassDB::bind_method(D_METHOD("get_climb_speed"), &Player::get_climb_speed);
        ClassDB::bind_method(D_METHOD("set_climb_speed", "_speed"), &Player::set_climb_speed);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "climb_speed"), "set_climb_speed", "get_climb_speed");

        ClassDB::bind_method(D_METHOD("get_crouch_translate"), &Player::get_crouch_translate);
        ClassDB::bind_method(D_METHOD("set_crouch_translate", "_speed"), &Player::set_crouch_translate);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "crouch_translate"), "set_crouch_translate", "get_crouch_translate");

        ClassDB::bind_method(D_METHOD("get_crouch_jump_add"), &Player::get_crouch_jump_add);
        ClassDB::bind_method(D_METHOD("set_crouch_jump_add", "_speed"), &Player::set_crouch_jump_add);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "crouch_jump_add"), "set_crouch_jump_add", "get_crouch_jump_add");

        ClassDB::bind_method(D_METHOD("get_noclip_speed_mult"), &Player::get_noclip_speed_mult);
        ClassDB::bind_method(D_METHOD("set_noclip_speed_mult", "_speed"), &Player::set_noclip_speed_mult);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "noclip_speed_mult"), "set_noclip_speed_mult", "get_noclip_speed_mult");

        ClassDB::bind_method(D_METHOD("get_max_step_height"), &Player::get_max_step_height);
        ClassDB::bind_method(D_METHOD("set_max_step_height", "_speed"), &Player::set_max_step_height);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "max_step_height"), "set_max_step_height", "get_max_step_height");

        ClassDB::bind_method(D_METHOD("get_auto_bhop"), &Player::get_auto_bhop);
        ClassDB::bind_method(D_METHOD("set_auto_bhop", "_speed"), &Player::set_auto_bhop);
        ClassDB::add_property("Player", PropertyInfo(Variant::BOOL, "auto_bhop"), "set_auto_bhop", "get_auto_bhop");

        ClassDB::bind_method(D_METHOD("get_noclip"), &Player::get_noclip);
        ClassDB::bind_method(D_METHOD("set_noclip", "_speed"), &Player::set_noclip);
        ClassDB::add_property("Player", PropertyInfo(Variant::BOOL, "noclip"), "set_noclip", "get_noclip");

        ClassDB::bind_method(D_METHOD("get_controller_look_sensitivity"), &Player::get_controller_look_sensitivity);
        ClassDB::bind_method(D_METHOD("set_controller_look_sensitivity", "_speed"), &Player::set_controller_look_sensitivity);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "controller_sensitivity"), "set_controller_look_sensitivity", "get_controller_look_sensitivity");

        ClassDB::bind_method(D_METHOD("get_mouse_look_sensitivity"), &Player::get_mouse_look_sensitivity);
        ClassDB::bind_method(D_METHOD("set_mouse_look_sensitivity", "_speed"), &Player::set_mouse_look_sensitivity);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "mouse_sensitivity"), "set_mouse_look_sensitivity", "get_mouse_look_sensitivity");

        ClassDB::bind_method(D_METHOD("get_jump_velocity"), &Player::get_jump_velocity);
        ClassDB::bind_method(D_METHOD("set_jump_velocity", "_speed"), &Player::set_jump_velocity);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "jump_velocity"), "set_jump_velocity", "get_jump_velocity");

        ClassDB::bind_method(D_METHOD("get_player_height"), &Player::get_player_height);
        ClassDB::bind_method(D_METHOD("set_player_height", "_speed"), &Player::set_player_height);
        ClassDB::add_property("Player", PropertyInfo(Variant::VECTOR2, "player_height"), "set_player_height", "get_player_height");

        ClassDB::bind_method(D_METHOD("get_capsule_height"), &Player::get_capsule_height);
        ClassDB::bind_method(D_METHOD("set_capsule_height", "_speed"), &Player::set_capsule_height);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "capsule_height"), "set_capsule_height", "get_capsule_height");

        ClassDB::bind_method(D_METHOD("get_capsule_radius"), &Player::get_capsule_radius);
        ClassDB::bind_method(D_METHOD("set_capsule_radius", "_speed"), &Player::set_capsule_radius);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "capsule_radius"), "set_capsule_radius", "get_capsule_radius");

        ClassDB::bind_method(D_METHOD("get_speed_jump_mult"), &Player::get_speed_jump_mult);
        ClassDB::bind_method(D_METHOD("set_speed_jump_mult", "_speed"), &Player::set_speed_jump_mult);
        ClassDB::add_property("Player", PropertyInfo(Variant::FLOAT, "speed_jump_mult"), "set_speed_jump_mult", "get_speed_jump_mult");

    }

    Player::Player() {}

    void Player::CreateHead()
    {
        HeadOriginalPosition = memnew(Node3D);
        add_child(HeadOriginalPosition);
        Vector3 _headPos = HeadOriginalPosition->get_position();
        _headPos.y = ConvertImperialToMetric(PlayerHeight) - (6 * 0.0254f);
        HeadOriginalPosition->set_position(_headPos);
        //HeadOriginalPosition->set_position(Vector3(HeadOriginalPosition->get_position().x, HeadOriginalPosition->get_position().y-2.f, HeadOriginalPosition->get_position().z));
        Head = memnew(Node3D);
        HeadOriginalPosition->add_child(Head);

        CameraSmooth = memnew(Node3D);
        Head->add_child(CameraSmooth);
    }

    void Player::_ready()
    {
        CharacterBody3D::_ready();
        CreateHead();
        CreateCamera();
        CreateHitscan();
        CreateStepRays();
        CreateCollider();

        SetMouseMode(Input::MOUSE_MODE_CAPTURED);
    }
    void Player::CreateCamera()
    {
        camera = memnew(Camera3D);
        if (camera == nullptr) {
            UtilityFunctions::print("Camera creation failed!");
        } else {
            UtilityFunctions::print("Camera created successfully.");
        }
        camera->add_to_group("PlayerCamera");
        CameraSmooth->add_child(camera);

        if (camera->is_inside_tree()) {
            UtilityFunctions::print("Camera added to tree successfully.");
        } else {
            UtilityFunctions::print("Camera not added to tree.");
        }
    }

    void Player::CreateHitscan()
    {
        hitscan = memnew(RayCast3D);
        if (hitscan == nullptr) {
            UtilityFunctions::print("Hitscan creation failed!");
        } else {
            UtilityFunctions::print("Hitscan created successfully.");
        }
        hitscan->add_to_group("Hitscan");

        if (hitscan->is_inside_tree()) {
            UtilityFunctions::print("Hitscan added to tree successfully.");
        } else {
            UtilityFunctions::print("Hitscan not added to tree.");
        }
        camera->add_child(hitscan);
    }

    void Player::SetMouseMode(const Input::MouseMode _mode) const {
        if(Engine::get_singleton()->is_editor_hint()) return;
        Input::get_singleton()->set_mouse_mode(_mode);
    }

    void Player::_process(double p_delta)
    {
        CharacterBody3D::_process(p_delta);
        _handle_controller_look_input(p_delta);

    }




    void Player::_exit_tree()
    {
        CharacterBody3D::_exit_tree();
    }

    void Player::_physics_process(double p_delta)
    {
        CharacterBody3D::_physics_process(p_delta);
        if (Engine::get_singleton()->is_editor_hint()) return;

        if(is_on_floor())
            _last_frame_was_on_floor = Engine::get_singleton()->get_physics_frames();
        inputDir = Input::get_singleton()->get_vector("Left", "Right", "Forward", "Backward").normalized();
        wishDir = get_transform().basis.xform(Vector3(inputDir.x, 0, inputDir.y));
        cam_aligned_wish_dir = camera->get_global_transform().basis.xform(Vector3(inputDir.x, 0, inputDir.y));

    if(!HandleLadderPhysics())
    {

        _handle_crouch(p_delta);

        if(!_handle_noclip(p_delta))
        {
            if(!_handle_water_physics(p_delta))
            {
                    if(is_on_floor() || _snapped_to_stairs_last_frame)
                    {
                        if(Input::get_singleton()->is_action_just_pressed("Jump") || (auto_bhop && Input::get_singleton()->is_action_pressed("Jump")))
                        {
                            Vector3 v = this->get_velocity();

                               v.y += jump_velocity * (Vector2(get_velocity().x, get_velocity().z).length() >= sprint_speed ? Vector2(get_velocity().x, get_velocity().z).length()  * SPEED_JUMP_MULT : 23.444444444);
                            this->set_velocity(v);
                        }
                        _handle_ground_physics(p_delta);
                    }
                    else
                    {
                        _handle_air_physics(p_delta);
                    }
                }
            }

            if(!StepUpStairsCheck(p_delta))
            {
                _push_away_rigid_bodies();
                move_and_slide();
                SnapDownToStairsCheck();
            }
        }

        SmoothCamera(p_delta);

    }

    bool Player::HandleLadderPhysics() {
	if(!settings->get_CanClimbLadder()) return false;
	bool was_climbing_ladder = currentLadder && currentLadder->overlaps_body(this);
	//CalculateDirection();

	// Check if we are currently climbing a ladder. If not, check if we are overlapping a ladder
	if (!was_climbing_ladder) {
		currentLadder = nullptr;
		SceneTree *scene = get_tree();
		TypedArray<Node> ladder_group = scene->get_nodes_in_group("ladder_area3d");
		for (int i = 0; i < ladder_group.size(); i++) {
			auto *ladder = Object::cast_to<Area3D>(ladder_group[i]);
			if (ladder && ladder->overlaps_body(this)) {
				currentLadder = ladder;
				break;
			}
		}
	}
	if (currentLadder == nullptr)
		return false;

	// Variable creation for ladder calculations
	Transform3D ladder_global_t = currentLadder->get_global_transform();
	Vector3 rel_pos_to_ladder = ladder_global_t.affine_inverse().xform(get_global_position());

	float forward_move = -inputDir.y;
	float side_move = inputDir.x;

	// Transform these movements to the ladder's local space
	Vector3 ladder_forward_move = ladder_global_t.affine_inverse().basis.xform(camera->get_global_transform().basis.xform(Vector3(0,0,-forward_move)));
	Vector3 ladder_side_move = ladder_global_t.affine_inverse().basis.xform(camera->get_global_transform().basis.xform(Vector3(side_move,0,0)));

	// Calculate strafing and climbing velocities
	float ladder_strafe_vel = settings->get_ClimbSpeed() * (ladder_side_move.x + ladder_forward_move.x);
	float ladder_climb_vel = settings->get_ClimbSpeed() * -ladder_forward_move.z;

	// Camera bias checks to determine if the player wants to move up or down the ladder
	float cam_forward_amount = camera->get_global_transform().basis.get_column(2).normalized().dot(currentLadder->get_basis().get_column(2).normalized());
	float up_wish = Vector3(0, 1, 0).rotated(Vector3(1, 0, 0), Math::deg_to_rad(-45 * cam_forward_amount)).dot(ladder_forward_move);
	ladder_climb_vel += settings->get_ClimbSpeed() * up_wish;


	// Only climb ladder when moving towards ladder and not being trapped forever within its bounds.
	bool should_dismount = false;
	if(!was_climbing_ladder)
	{
		bool mounting_from_top = rel_pos_to_ladder.y > currentLadder->get_node<Node3D>("Ladder_Top")->get_position().y;
		if(mounting_from_top)
		{
			if(ladder_climb_vel > 0) should_dismount = true;
		}
		else
		{
			// If not mounting from top, they are either falling or on the floor
			if(ladder_global_t.affine_inverse().basis.xform(wishDir).z >= 0) should_dismount = true;
		}

		// Only stick to ladder if close

		if(Math::abs(rel_pos_to_ladder.z) > 0.1f) should_dismount = true;
	}

	if(is_on_floor() && ladder_climb_vel <= 0) should_dismount = true;

	if(should_dismount)
	{
		currentLadder = nullptr;
		return false;
	}

	if(was_climbing_ladder && Input::get_singleton()->is_action_just_pressed("Jump"))
	{
	    Vector3 v = get_velocity();
		v = ladder_global_t.basis.get_column(Vector3::AXIS_Z) * settings->get_jumpForce() * 1.5f;
        set_velocity(v);
		currentLadder = nullptr;
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


void Player::CalculateDirection() {

    if (Engine::get_singleton()->is_editor_hint())
        return;


    Vector3 v = get_velocity();

    if(inputDir != Vector2(0,0)) {
        const Vector3 forward = -camera->get_transform().basis.get_column(2).normalized();
        const Vector3 right = camera->get_global_transform().basis.get_column(0).normalized();

        const Vector3 _dir = -forward * inputDir.y + right * inputDir.x;
        // Combine vectors based on input direction
        wishDir.x = _dir.x * get_swim_up_speed();
        wishDir.z = _dir.z * get_swim_up_speed();

    }



}

    void Player::_enter_tree()
    {
        CharacterBody3D::_enter_tree();
    }


//TODO: Currently broken and needs re construction
    /*void Player::InteractionCast() {
        auto test = ;
        Camera3D *cam = Object::cast_to<Camera3D>(camera);
        PhysicsDirectSpaceState3D *space_state = Object::cast_to<PhysicsDirectSpaceState3D>(get_world_3d()->get_direct_space_state());
        Viewport *viewport = get_viewport();
        Vector2 viewport_size = viewport->get_visible_rect().get_size();
        Vector2 screen_center = viewport_size / 2;
        Vector3 origin = cam->project_ray_origin(screen_center);
        Vector3 end = origin + cam->project_ray_normal(screen_center) * get_Settings()->get_interactDistance();

        Ref<PhysicsRayQueryParameters3D> query = ::create(origin, end);
        query->set_from(origin);
        query->set_to(end);
        query->set_collide_with_bodies(true);
        query->set_exclude(Array::make(this)); // Exclude the player

        Dictionary result = space_state->intersect_ray(query);
        Variant current_cast_result = result.get("collider", Variant());


        if (current_cast_result != interact_cast_result) {

            if (interact_cast_result) {
                Node *interactable_node = Object::cast_to<Node>(interact_cast_result.operator Object *());
                if (interactable_node && interactable_node->has_user_signal("out_focus")) {
                    UtilityFunctions::print(interactable_node->get_name() + StringName(" unfocused"));
                    interactable_node->emit_signal("out_focus");
                }
            }

            interact_cast_result = current_cast_result;

            if (interact_cast_result) {
                Node *interactable_node = Object::cast_to<Node>(interact_cast_result.operator Object *());
                if (interactable_node && interactable_node->has_user_signal("in_focus")) {
                    UtilityFunctions::print(interactable_node->get_name() + StringName(" focused"));
                    interactable_node->emit_signal("in_focus");
                }
            }
        }
    }*/

    void Player::_unhandled_input(const Ref<InputEvent>& p_event)
    {
        if(Input::get_singleton()->is_action_just_pressed("Pause"))
        {
            get_tree()->quit();
        }
        if (p_event->is_class("InputEventMouseMotion")) {
            auto *mouseMotionEvent = dynamic_cast<InputEventMouseMotion *>(*p_event);
            rotate_y(-mouseMotionEvent->get_relative().x * look_sensitivity);
            camera->rotate_x(-mouseMotionEvent->get_relative().y * look_sensitivity);
            float camX = is_on_floor() ? Math::clamp(camera->get_rotation().x , Math::deg_to_rad(-90.f), Math::deg_to_rad(90.f)) : camera->get_rotation().x;
            camera->set_rotation(Vector3( camX , camera->get_rotation().y, camera->get_rotation().z));
        }

        if(p_event->is_class("InputEventMouseButton") && p_event->is_pressed())
        {

            auto *mouseMotionEvent = dynamic_cast<InputEventMouseButton *>(*p_event);
            if(mouseMotionEvent->get_button_index() == MOUSE_BUTTON_WHEEL_UP)
            {
                noclip_speed_mult = Math::min(100.0, noclip_speed_mult * 1.1);
            }
            else if(mouseMotionEvent->get_button_index() == MOUSE_BUTTON_WHEEL_DOWN)
            {
                noclip_speed_mult = Math::max(0.1, noclip_speed_mult * 0.9);

            }
        }

        if(p_event->is_action_released("Weapon_1"))
        {
            SwitchWeapon(1);
        }

        if(p_event->is_action_released("Weapon_2"))
        {
            SwitchWeapon(2);
        }

        if(p_event->is_action_released("Weapon_3"))
        {
            SwitchWeapon(3);
        }

        if(p_event->is_action_released("Weapon_4"))
        {
            SwitchWeapon(4);
        }

        if(p_event->is_action_released("Weapon_5"))
        {
            SwitchWeapon(5);
        }




    }

    void Player::_headbob_effect(float delta)
    {
        headbob_time += delta * this->get_velocity().length();
        Transform3D _t = camera->get_transform();
        Vector3 o;

        float t = headbob_time;
        float f = HEADBOB_FREQUENCY;
        float a = HEADBOB_MOVE_AMOUNT;

        float x = cos(t * f * 0.5f) * a;
        float y = sin(t * f) * a;
        o = Vector3(x, y ,0);
        _t.set_origin(o);
        camera->set_transform(_t);

    }

    void Player::_handle_controller_look_input(double delta)
    {
        if(Engine::get_singleton()->is_editor_hint()) return;
        Vector2 target_look = Input::get_singleton()->get_vector("look_left", "look_right", "look_down", "look_up").normalized();

        if (target_look.length() >= _cur_controller_look.length())
        {
            _cur_controller_look = _cur_controller_look.lerp(target_look, 5.0 * delta);
        }
        else
        {
            _cur_controller_look = target_look;
        }


        rotate_y(-_cur_controller_look.x * controller_look_sensitivity); // turn left and right
        camera->rotate_x(_cur_controller_look.y * controller_look_sensitivity); // look up and down

        float camX = is_on_floor() ? Math::clamp(camera->get_rotation().x , Math::deg_to_rad(-90.f), Math::deg_to_rad(90.f)) : camera->get_rotation().x;

        camera->set_rotation(Vector3( camX , camera->get_rotation().y, camera->get_rotation().z)); // clamp up and down range
    }



    void Player::_handle_ground_physics(double delta)
    {

        float fDelta = static_cast<float>(delta);
        float cur_speed_in_wish_dir = this->get_velocity().dot(wishDir);
        float add_speed_till_cap = get_move_speed() - cur_speed_in_wish_dir;
        if(add_speed_till_cap > 0)
        {
            float accel_speed = ground_accel * fDelta * get_move_speed();
            accel_speed = Math::min(accel_speed, add_speed_till_cap);
            Vector3 v = this->get_velocity();
            v += accel_speed * wishDir;
            this->set_velocity(v);
        }

        //Apply Friction
        float control = Math::max(this->get_velocity().length(), ground_decel);
        float drop = control * ground_friction * fDelta;
        float new_speed = Math::max(this->get_velocity().length() - drop, 0.0f);
        if(this->get_velocity().length() > 0)
        {
            new_speed /= this->get_velocity().length();
        }
        Vector3 v = this->get_velocity();
        v *= new_speed;
        this->set_velocity(v);

        _headbob_effect(fDelta);
    }

    void Player::_handle_air_physics(double delta)
    {
        float fDelta = static_cast<float>(delta);
        Vector3 v = this->get_velocity();
        v.y -= gravity * fDelta;
        this->set_velocity(v);
        float cur_speed_in_wish_dir = this->get_velocity().dot(wishDir);
        float add_speed_till_cap = get_move_speed() - cur_speed_in_wish_dir;
        if(add_speed_till_cap > 0)
        {
            float accel_speed = air_accel * air_move_speed * fDelta;
            accel_speed = Math::min(accel_speed, add_speed_till_cap);
            v += accel_speed * wishDir;
            this->set_velocity(v);
        }

        if (is_on_wall()) {
            if (IsSurfaceTooSteep(get_wall_normal())) {
                set_motion_mode(MOTION_MODE_FLOATING);  // Enables smoother surf movement
            } else {
                set_motion_mode(MOTION_MODE_GROUNDED);
            }
            clip_velocity(get_wall_normal(), 1.0f, fDelta);  // Clip velocity for surf
        }

    }


    bool Player::IsSurfaceTooSteep(const Vector3 _normal)
    {
    return _normal.angle_to(Vector3(0.0f, 1.0f, 0.0f)) > get_floor_max_angle();
    }

    void Player::CreateCollider() {
        col = memnew(CollisionShape3D);
        col->set_name("Collider");

        Ref<CapsuleShape3D> colShape;
        colShape.instantiate();
        colShape->set_height(ConvertImperialToMetric(PlayerHeight));
        colShape->set_radius(capsule_radius);
        col->set_shape(colShape);
        //col->set_transform(Transform3D(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0));
        this->add_child(col);

        playerInitialized = true;
    }

    void Player::CreateBody() {
        body = memnew(MeshInstance3D);
        body->set_name("_body");
        body->set_cast_shadows_setting(GeometryInstance3D::ShadowCastingSetting::SHADOW_CASTING_SETTING_ON);
        body->set_position(Vector3(0.0f, 0.0f, 0.0f));
        col->add_child(body);
        if (const Ref<MeshLibrary> meshLibrary = ResourceLoader::get_singleton()->load("res://bin/CONST_INT/Resources/CI_MeshLibrary.tres"); meshLibrary.is_valid())
        {
            const Ref<Mesh> bodyMesh = meshLibrary->get_item_mesh(0);
            body->set_mesh(bodyMesh);
        }

    }
    void Player::CreateStepRays() {
        stepDownRay = memnew(RayCast3D);
        stepDownRay->set_name("_stepDownRay");
        stepDownRay->set_position(Vector3(0.0f, 0.0f, 0.0f));
        stepDownRay->set_target_position(Vector3(0, -1, 0));
        add_child(stepDownRay);

        stepAheadRay = memnew(RayCast3D);
        stepAheadRay->set_name("_stepAheadRay");
        stepAheadRay->set_position(Vector3(0.0f, 0.55f, -0.55f));
        stepAheadRay->set_target_position(Vector3(0, -0.55f, 0));
        add_child(stepAheadRay);
    }

    void Player::SnapDownToStairsCheck()
    {
	    bool did_snap = false;


	    stepDownRay->force_raycast_update();
	    const bool floor_below = stepDownRay->is_colliding() && !IsSurfaceTooSteep(stepDownRay->get_collision_normal());
	    bool was_on_floor_last_frame = Engine::get_singleton()->get_physics_frames() == _last_frame_was_on_floor;
	    if(!is_on_floor() && this->get_velocity().y <= 0 && (was_on_floor_last_frame || _snapped_to_stairs_last_frame) && floor_below)
	    {
		    KinematicCollision3D* body_test_result = memnew(KinematicCollision3D);
		    if(test_move(get_global_transform(), Vector3(0, -MAX_STEP_HEIGHT, 0), body_test_result))
		    {
			    SaveCamPosForSmoothing();
			    float translate_y = body_test_result->get_travel().y;
			    Vector3 pos = get_position();
			    pos.y += translate_y;
			    set_position(pos);
			    apply_floor_snap();
		        did_snap = true;

		    }
	    }
	    _snapped_to_stairs_last_frame = did_snap;

}
bool Player::StepUpStairsCheck(const double delta) {
	if (!is_on_floor() && !_snapped_to_stairs_last_frame)
	{
	    return false;
	}
    if(get_velocity().y > 0 || (get_velocity() * Vector3(1,0,1)).length() == 0.f)
    {
        return false;
    }

	const Vector3 expected_move_motion = this->get_velocity() * Vector3(1,0,1) * static_cast<float>(delta);

	//Makes sure you can't step up if something is blocking you
	const Transform3D step_pos_with_clearance = get_global_transform().translated(expected_move_motion + Vector3(0, MAX_STEP_HEIGHT *2, 0));
    KinematicCollision3D* down_check_result = memnew(KinematicCollision3D);
	if (test_move(step_pos_with_clearance, Vector3(0, -MAX_STEP_HEIGHT*2.0f, 0), down_check_result) && (down_check_result->get_collider()->is_class("StaticBody3D") || down_check_result->get_collider()->is_class("CSGShape3D")))
	{
		//how much higher is the step_height
	    float step_height = ((step_pos_with_clearance.origin + down_check_result->get_travel()) - get_global_position()).y;
		if(step_height > MAX_STEP_HEIGHT || step_height <= 0.01f || (down_check_result->get_position() - get_global_position()).y > MAX_STEP_HEIGHT) return false;
		stepAheadRay->set_global_position(down_check_result->get_position() + Vector3(0, MAX_STEP_HEIGHT, 0) + expected_move_motion.normalized() * 0.025f);
		stepAheadRay->force_raycast_update();
		//UtilityFunctions::print(step_height);
		if(stepAheadRay->is_colliding() && !IsSurfaceTooSteep(stepAheadRay->get_collision_normal()))
		{

			SaveCamPosForSmoothing();
			set_global_position(step_pos_with_clearance.origin + down_check_result->get_travel());
			apply_floor_snap();
			_snapped_to_stairs_last_frame = true;
			return true;
		}
	}
	return false;
}

    void Player::SaveCamPosForSmoothing()
    {
        if(savedCameraPosition == Vector3(0,0,0))
        {
            savedCameraPosition = camera->get_global_position();
        }
    }


    void Player::SmoothCamera(double delta) {
        if (savedCameraPosition == Vector3(0,0,0)) return;
        Vector3 CS_GP = CameraSmooth->get_global_position();
        Vector3 CS_LP = CameraSmooth->get_position();
        CS_GP.y = savedCameraPosition.y;
        CS_LP.y = Math::clamp(CS_LP.y, -CROUCH_TRANSLATE, CROUCH_TRANSLATE);
        float move_amount = Math::max(get_velocity().length() * delta, walk_speed/2 * delta);
        CS_LP.y = Math::move_toward(CS_LP.y, 0.0f, move_amount);
        savedCameraPosition = CS_GP;
        if(CS_LP.y == 0)
        {
            savedCameraPosition = Vector3(0,0,0);
        }
        CameraSmooth->set_global_position(CS_GP);
        CameraSmooth->set_position(CS_LP);
    }

    void Player::_push_away_rigid_bodies()
    {
        for(int i = 0; i < get_slide_collision_count(); i++)
        {
            Ref<KinematicCollision3D> c = get_slide_collision(i);
            if(c->get_collider()->is_class("RigidBody3D"))
            {
                auto *rb = Object::cast_to<RigidBody3D>(c->get_collider());
                Vector3 push_dir = -c->get_normal();
                real_t velocity_diff_in_push_dir = this->get_velocity().dot(push_dir) - rb->get_linear_velocity().dot(push_dir);
                velocity_diff_in_push_dir = Math::max(0.0f, velocity_diff_in_push_dir);

                const float my_mass = 1.25f;
                float mass_ratio = Math::min(1.0f, my_mass / (float)rb->get_mass());
                push_dir.y = 0;
                float push_force = mass_ratio * 5.0f;
                rb->apply_impulse(push_dir * velocity_diff_in_push_dir * push_force, rb->get_position() - rb->get_global_position());
            }
        }
    }

    bool Player::_handle_water_physics(double delta)
    {
        return false;
        float fDelta = static_cast<float>(delta);


        if(!is_on_floor())
        {

            Vector3 v = this->get_velocity();
            v.y -= gravity * 0.1f * static_cast<float>(fDelta);
            this->set_velocity(v);
        }

            if(Input::get_singleton()->is_action_pressed("Jump"))
                _add_velocity_y(swim_up_speed * fDelta);

            this->set_velocity(this->get_velocity().lerp(Vector3(0,0,0), 2 * fDelta));
            return false;


    }


    void Player::_handle_crouch(double delta)
    {
        if(Engine::get_singleton()->is_editor_hint()) return;
        bool was_crouched_last_frame = is_crouched;

        Vector3 colPos = col->get_position();
        Ref<CapsuleShape3D> colShape = col->get_shape();

        if(Input::get_singleton()->is_action_pressed("Crouch"))
        {
            is_crouched = true;
        }
        else if (is_crouched && !test_move(get_transform(), Vector3(0, CROUCH_TRANSLATE,0)))
        {
            is_crouched = false;
        }

        float translate_y_if_possible = 0;

        if(was_crouched_last_frame != is_crouched && !is_on_floor() && !_snapped_to_stairs_last_frame)
        {
            translate_y_if_possible = (is_crouched) ? CROUCH_JUMP_ADD : -CROUCH_JUMP_ADD;
        }

        Vector3 hPos = Head->get_position();
        if(translate_y_if_possible != 0)
        {
            Ref result = memnew(KinematicCollision3D);
            test_move(get_global_transform(), Vector3(0, translate_y_if_possible, 0), result);
            Vector3 pos = get_position();
            pos.y += result->get_travel().y;
            set_position(pos);
            hPos.y -= result->get_travel().y;
            hPos.y = Math::clamp(hPos.y, -CROUCH_TRANSLATE, 0.0f);
            Head->set_position(hPos);
        }


        hPos.y = Math::move_toward(hPos.y, (is_crouched) ? -CROUCH_TRANSLATE : 0.f , 7.0f * (float)delta);
        colShape->set_height((is_crouched) ? ConvertImperialToMetric(PlayerHeight) - CROUCH_TRANSLATE : ConvertImperialToMetric(PlayerHeight));

        col->set_shape(colShape);
        colPos.y = (float)colShape->get_height() / 2.0f;
        col->set_position(colPos);
        Head->set_position(hPos);
        //UtilityFunctions::print(_snapped_to_stairs_last_frame);

    }

    bool Player::_handle_noclip(double delta)
    {
        if(Input::get_singleton()->is_action_just_pressed("Noclip") && OS::get_singleton()->has_feature("debug"))
        {
            noclip = !noclip;
            noclip_speed_mult = 3.f;
        }

        col->set_disabled(noclip);
        if(!noclip)
            return false;

        float speed = get_move_speed() * noclip_speed_mult;

        if(Input::get_singleton()->is_action_pressed("Sprint"))
        {
            speed *= 3.f;
        }
        this->set_velocity(cam_aligned_wish_dir * speed);
        Vector3 gp = get_global_position();
        gp += this->get_velocity() * delta;
        set_global_position(gp);
        return true;
    }

    void Player::clip_velocity(Vector3 normal, float overbounce, float _delta)
    {
        float backoff = this->get_velocity().dot(normal) * overbounce;

        if(backoff >= 0)
            return;

        Vector3 change = normal * backoff;
        Vector3 v = this->get_velocity();
        v -= change;
        this->set_velocity(v);

        // Second iteration to ensure no movement through the plane
        float adjust = this->get_velocity().dot(normal);
        if(adjust < 0.0f)
        {
            v -= normal * adjust;
            this->set_velocity(v);
        }
    }

    void Player::_mouse_look(const Ref<InputEventMouseMotion>& p_event)
    {
        if (camera == nullptr) {
            UtilityFunctions::print("Camera is null during mouse look!");
            return;
        }

        if (Engine::get_singleton()->is_editor_hint()) return;

        Vector2 mouseMotion = p_event->get_relative();
        camera->rotate_y(Math::deg_to_rad(-mouseMotion.x * look_sensitivity));
        mouseRotation.x += Math::deg_to_rad(-mouseMotion.y * look_sensitivity);

        mouseRotation.x = Math::clamp(mouseRotation.x, Math::deg_to_rad(-89.0f), Math::deg_to_rad(89.0f));

        mouseRotation.z += Math::deg_to_rad(-mouseMotion.y * look_sensitivity * inputDir.length());
        mouseRotation.z = Math::clamp(mouseRotation.z, Math::deg_to_rad(-85.0f), Math::deg_to_rad(85.0f));

        mouseRotation.z = Math::lerp(mouseRotation.z, 0.0f, static_cast<float>(get_physics_process_delta_time()) * 7.0f);

        Transform3D t = camera->get_transform();
        t.basis = get_basis();
        camera->set_transform(t);

        camera->rotate_object_local(Vector3(1, 0, 0), mouseRotation.x);
    }

    float Player::get_move_speed()
    {
        if(is_crouched)
        {
            return walk_speed * 0.8;
        }
        if(Input::get_singleton()->is_action_pressed("Sprint"))
        {
            return sprint_speed;
        }
        return walk_speed;
    }

    float Player::ConvertImperialToMetric(Vector2 height)
    {
        float feet = height.x;
        float inches = height.y;
        const float feet_to_meters = 0.3048f;
        const float inches_to_meters = 0.0254f;

        float meters_from_feet = feet * feet_to_meters;
        float meters_from_inches = inches * inches_to_meters;
        float total_meters = meters_from_feet + meters_from_inches;
        return total_meters;
    }

    void Player::SwitchWeapon(int index)
    {

    }

    float Player::get_headbob_move_amount()
    {
        return HEADBOB_MOVE_AMOUNT;
    }

    float Player::get_headbob_frequency()
    {
        return HEADBOB_FREQUENCY;
    }

    float Player::get_headbob_time()
    {
        return headbob_time;
    }

    float Player::get_walk_speed()
    {
        return walk_speed;
    }

    float Player::get_sprint_speed()
    {
        return sprint_speed;
    }

    float Player::get_ground_accel()
    {
        return ground_accel;
    }

    float Player::get_ground_decel()
    {
        return ground_decel;
    }

    float Player::get_ground_friction()
    {
        return ground_friction;
    }

    float Player::get_air_cap()
    {
        return air_cap;
    }

    float Player::get_air_accel()
    {
        return air_accel;
    }

    float Player::get_air_move_speed()
    {
        return air_move_speed;
    }

    float Player::get_gravity()
    {
        return gravity;
    }

    float Player::get_swim_up_speed()
    {
        return swim_up_speed;
    }

    float Player::get_climb_speed()
    {
        return climb_speed;
    }

    float Player::get_crouch_translate()
    {
        return CROUCH_TRANSLATE;
    }

    float Player::get_crouch_jump_add()
    {
        return CROUCH_JUMP_ADD / CROUCH_TRANSLATE;
    }

    float Player::get_noclip_speed_mult()
    {
        return noclip_speed_mult;
    }

    float Player::get_max_step_height()
    {
        return MAX_STEP_HEIGHT;
    }

    bool Player::get_auto_bhop()
    {
        return auto_bhop;
    }

    bool Player::get_noclip()
    {
        return noclip;
    }

    float Player::get_mouse_look_sensitivity()
    {
        return look_sensitivity;
    }

    float Player::get_controller_look_sensitivity()
    {
        return controller_look_sensitivity;
    }

    float Player::get_jump_velocity()
    {
        return jump_velocity;
    }

    Vector2 Player::get_player_height()
    {
        return PlayerHeight;
    }

    float Player::get_speed_jump_mult()
    {
        return SPEED_JUMP_MULT;
    }


    float Player::get_capsule_height()
    {
        return capsule_height;
    }

    float Player::get_capsule_radius()
    {
        return capsule_radius;
    }

    void Player::set_headbob_move_amount(float amount)
    {
        HEADBOB_MOVE_AMOUNT = amount;
    }

    void Player::set_headbob_frequency(float frequency)
    {
        HEADBOB_FREQUENCY = frequency;
    }

    void Player::set_headbob_time(float time)
    {
        headbob_time = time;
    }

    void Player::set_walk_speed(float speed)
    {
        walk_speed = speed;
    }

    void Player::set_sprint_speed(float speed)
    {
        sprint_speed = speed;
    }

    void Player::set_ground_accel(float accel)
    {
        ground_accel = accel;
    }

    void Player::set_ground_decel(float decel)
    {
        ground_decel = decel;
    }

    void Player::set_ground_friction(float friction)
    {
        ground_friction = friction;
    }

    void Player::set_air_cap(float cap)
    {
        air_cap = cap;
    }

    void Player::set_air_accel(float accel)
    {
        air_accel = accel;
    }

    void Player::set_air_move_speed(float speed)
    {
        air_move_speed = speed;
    }

    void Player::set_gravity(float _gravity)
    {
        gravity = _gravity;
    }

    void Player::set_swim_up_speed(float speed)
    {
        swim_up_speed = speed;
    }

    void Player::set_climb_speed(float speed)
    {
        climb_speed = speed;
    }

    void Player::set_crouch_translate(float translate)
    {
        CROUCH_TRANSLATE = translate;
    }

    void Player::set_crouch_jump_add(float add)
    {
        CROUCH_JUMP_ADD = get_crouch_translate() * add;
    }

    void Player::set_noclip_speed_mult(float mult)
    {
        noclip_speed_mult = mult;
    }

    void Player::set_max_step_height(float height)
    {
        MAX_STEP_HEIGHT = height;
    }

    void Player::set_auto_bhop(bool bhop)
    {
        auto_bhop = bhop;
    }

    void Player::set_noclip(bool _noclip)
    {
        noclip = _noclip;
    }

    void Player::set_controller_look_sensitivity(float _sens)
    {
        controller_look_sensitivity = _sens;
    }

    void Player::set_mouse_look_sensitivity(float _sens)
    {
        look_sensitivity = _sens;
    }

    void Player::set_jump_velocity(float force)
    {
        jump_velocity = force;
    }

    void Player::set_player_height(Vector2 pos)
    {
        PlayerHeight = pos;
        UpdatePlayerSizeAttributes();
    }

    void Player::set_speed_jump_mult(float mult)
    {
        SPEED_JUMP_MULT = mult;
    }

    void Player::set_capsule_height(float height)
    {
        capsule_height = height;
        UpdatePlayerSizeAttributes();
    }

    void Player::set_capsule_radius(float radius)
    {
        capsule_radius = radius;
        UpdatePlayerSizeAttributes();
    }


    void Player::_add_velocity_x(float value)
{
    Vector3 v = this->get_velocity();
    v.x += value;
    this->set_velocity(v);
}

    void Player::_add_velocity_y(float value)
{
    Vector3 v = this->get_velocity();
    v.y += value;
    this->set_velocity(v);
}

    void Player::_add_velocity_z(float value)
{
    Vector3 v = this->get_velocity();
    v.z += value;
    this->set_velocity(v);
}
    void Player::_subtract_velocity_x(float value)
{
    Vector3 v = this->get_velocity();
    v.x -= value;
    this->set_velocity(v);
}

    void Player::_subtract_velocity_y(float value)
{
    Vector3 v = this->get_velocity();
    v.y -= value;
    this->set_velocity(v);
}

    void Player::_subtract_velocity_z(float value)
{
    Vector3 v = this->get_velocity();
    v.z -= value;
    this->set_velocity(v);
}

    void Player::UpdatePlayerSizeAttributes()
    {
        if(!playerInitialized) return;
        Vector3 _headPos = HeadOriginalPosition->get_position();
        _headPos.y = ConvertImperialToMetric(PlayerHeight) - (6 * 0.0254f);
        HeadOriginalPosition->set_position(_headPos);
        savedCameraPosition = get_global_position();
        Ref<CapsuleShape3D> shape = col->get_shape();
        shape->set_height(ConvertImperialToMetric(PlayerHeight));
        shape->set_radius(capsule_radius);
    }


Ref<ActorSettings> Player::get_Settings() const {
        return settings;
    }
void Player::set_Settings(const Ref<ActorSettings> &_settings) {
        settings = _settings;
    }