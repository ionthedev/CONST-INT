//
// Created by Brandon Friend on 8/27/24.
//


#ifndef PLAYER_H
#define PLAYER_H
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/ray_cast3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/rigid_body3d.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/shape3d.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/capsule_shape3d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/mesh_library.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>

#include "Config/ActorSettings.h"


using namespace godot;
    class Player : public CharacterBody3D {
        GDCLASS(Player, CharacterBody3D)

    public:
        static void _bind_methods();
        Player();
        ~Player() {}

        void CreateHead();
        //Overrides
            void _ready() override;
            void _process(double p_delta) override;
            void _physics_process(double p_delta) override;
        bool HandleLadderPhysics();
        void CalculateDirection();
        void _enter_tree() override;
        //void InteractionCast();
        void _exit_tree() override;
            void _unhandled_input(const Ref<InputEvent>& p_event) override;
        void _headbob_effect(float delta);
        void _handle_controller_look_input(double delta);

        //Custom
        void _handle_ground_physics(double delta);
        void _handle_air_physics(double delta);
        bool IsSurfaceTooSteep(Vector3 _normal);
        void CreateCollider();
        void CreateBody();
        void CreateStepRays();
        void SnapDownToStairsCheck();
        bool StepUpStairsCheck(double delta);
        void SaveCamPosForSmoothing();
        void SmoothCamera(double delta);
        void _push_away_rigid_bodies();
        bool _handle_water_physics(double delta);
        void _handle_crouch(double delta);
        bool _handle_noclip(double delta);
        void clip_velocity(Vector3 normal, float overbounce, float _delta);
        void CreateCamera();
        void CreateHitscan();
        void SetMouseMode(Input::MouseMode _mode) const;
        void _mouse_look(const Ref<InputEventMouseMotion> &p_event);
        float get_move_speed();
        float ConvertImperialToMetric(Vector2 height);
        void SwitchWeapon(int index);


        //Getters
        float get_headbob_move_amount();
        float get_headbob_frequency();
        float get_headbob_time();

        float get_walk_speed();
        float get_sprint_speed();
        float get_ground_accel();
        float get_ground_decel();
        float get_ground_friction();

        float get_air_cap();
        float get_air_accel();
        float get_air_move_speed();
        float get_gravity();

        float get_swim_up_speed();
        float get_climb_speed();
        float get_crouch_translate();
        float get_crouch_jump_add();
        float get_noclip_speed_mult();
        float get_max_step_height();
        bool get_auto_bhop();
        bool get_noclip();
        float get_mouse_look_sensitivity();
        float get_controller_look_sensitivity();
        float get_jump_velocity();
        Vector2 get_player_height();
        float get_speed_jump_mult();




        float get_capsule_height();
        float get_capsule_radius();

        //Setters
        void set_headbob_move_amount(float amount);
        void set_headbob_frequency(float frequency);
        void set_headbob_time(float time);

        void set_walk_speed(float speed);
        void set_sprint_speed(float speed);
        void set_ground_accel(float accel);
        void set_ground_decel(float decel);
        void set_ground_friction(float friction);

        void set_air_cap(float cap);
        void set_air_accel(float accel);
        void set_air_move_speed(float speed);
        void set_gravity(float _gravity);

        void set_swim_up_speed(float speed);
        void set_climb_speed(float speed);
        void set_crouch_translate(float translate);
        void set_crouch_jump_add(float add);
        void set_noclip_speed_mult(float mult);
        void set_max_step_height(float height);
        void set_auto_bhop(bool bhop);
        void set_noclip(bool _noclip);
        void set_controller_look_sensitivity(float _sens);
        void set_mouse_look_sensitivity(float _sens);
        void set_jump_velocity(float force);

        void set_player_height(Vector2 pos);
        void set_speed_jump_mult(float mult);

        void set_capsule_height(float height);
        void set_capsule_radius(float radius);



            void _set_velocity_x(float value);
            void _set_velocity_y(float value);
            void _set_velocity_z(float value);
            void _add_velocity_x(float value);
            void _add_velocity_y(float value);
            void _add_velocity_z(float value);
            void _subtract_velocity_x(float value);
            void _subtract_velocity_y(float value);
            void _subtract_velocity_z(float value);

        void UpdatePlayerSizeAttributes();
        Ref<ActorSettings> get_Settings() const;
        void set_Settings(const Ref<ActorSettings>& _settings);

    private:
        Vector2 inputDir;
        Vector3 wishDir;
        Vector3 mouseRotation;
        Vector3 savedCameraPosition;
        Vector2 _cur_controller_look;
        Ref<ActorSettings> settings;

        Area3D* currentLadder = nullptr;
        Variant interact_cast_result = nullptr;

        float SPEED_JUMP_MULT = 3.25;


        Vector2 PlayerHeight = Vector2(5,10);
        float EyeHeight;

        Node3D* HeadOriginalPosition;
        Node3D* Head;
        Node3D* CameraSmooth;

        float look_sensitivity= 0.006f;
        float controller_look_sensitivity = 0.05f;
        float jump_velocity = .27f;
        bool auto_bhop = true;
        bool playerInitialized = false;

        float HEADBOB_MOVE_AMOUNT = 0.06f;
        float HEADBOB_FREQUENCY = 2.4f;
        float headbob_time = 0.0f;
        float capsule_height = 2.0f;
        float capsule_radius = 0.5f;

        // Ground movement settings
         float walk_speed = 7.0f;
         float sprint_speed = 8.5f;
         float ground_accel = 7.0f;
         float ground_decel = 5.0f;
         float ground_friction = 6.0f;

        // Air movement settings. Need to tweak these to get the feeling dialed in.
         float air_cap = 2.85f; // Can surf steeper ramps if this is higher, makes it easier to stick and bhop
         float air_accel = 1.f;
         float air_move_speed = 17.0f;
         float gravity = 15.24f;

         float swim_up_speed = 10.0f;
         float climb_speed = 7.0f;

        Vector3 cam_aligned_wish_dir = Vector3(0,0,0);

        float CROUCH_TRANSLATE = 0.7;
        float CROUCH_JUMP_ADD = CROUCH_TRANSLATE * 0.9; // * 0.9 for sourcelike camera jitter in air on crouch, makes for a nice notifier
        bool is_crouched = false;

        float noclip_speed_mult = 3.0;
        bool noclip = false;

        float MAX_STEP_HEIGHT = 0.5f;
        bool _snapped_to_stairs_last_frame = false;
        uint64_t _last_frame_was_on_floor;

        Camera3D* camera;
        RayCast3D* hitscan;
        MeshInstance3D* body;
        RayCast3D* stepDownRay;
        RayCast3D* stepAheadRay;
        CollisionShape3D* col = nullptr;
    };


#endif //PLAYER_H
