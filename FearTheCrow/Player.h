//
// Created by Brandon Friend on 8/27/24.
//

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/shape3d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

#ifndef PLAYER_H
#define PLAYER_H


namespace FearTheCrow {
using namespace godot;
    class Player : public CharacterBody3D {
        GDCLASS(Player, CharacterBody3D)

    public:
        static void _bind_methods();
        Player();
        ~Player() {}

        //Overrides
            void _ready() override;
        void CreateCamera();
        void _process(double p_delta) override;
            void _physics_process(double p_delta) override;
            void _enter_tree() override;
            void _exit_tree() override;
            void _unhandled_input(const Ref<InputEvent>& p_event) override;

        //Custom
            void _handle_ground_physics(double p_delta);
            void _handle_air_physics(double p_delta);
            void _mouse_look(const Ref<InputEventMouseMotion> &p_event);




            void _set_velocity_x(float value);
            void _set_velocity_y(float value);
            void _set_velocity_z(float value);
            void _add_velocity_x(float value);
            void _add_velocity_y(float value);
            void _add_velocity_z(float value);
            void _subtract_velocity_x(float value);
            void _subtract_velocity_y(float value);
            void _subtract_velocity_z(float value);

    private:
        Vector2 inputDir;
        Vector3 wishDir;
        Vector3 mouseRotation;
        float GROUND_ACCELERATION = 7.f;
        float SPRINT_ACCELERATION = 8.5f;
        float AIR_ACCELERATION = 8.5f;
        float JUMP_VELOCITY = 6.f;
        float SENSITIVITY = 0.19f;
        bool autoBunnyhop = true;
        Camera3D* camera;
        CollisionShape3D* col = nullptr;
    };

} // FearTheCrow

#endif //PLAYER_H
