//
// Created by Brandon Friend on 8/27/24.
//

#include "Player.h"
#include "Player.h"

#include <godot_cpp/variant/utility_functions.hpp>

namespace FearTheCrow {

void Player::_bind_methods()
    {

        ClassDB::bind_method(D_METHOD("CreateCamera"), &Player::CreateCamera);
        ClassDB::bind_method(D_METHOD("_handle_ground_physics"), &Player::_handle_ground_physics);
        ClassDB::bind_method(D_METHOD("_handle_air_physics"), &Player::_handle_air_physics);
    }

Player::Player() {}

void Player::_ready()
{
    CharacterBody3D::_ready();
    CreateCamera();
}
    void Player::CreateCamera()
{
    camera = memnew(Camera3D);
    if (camera == nullptr) {
        UtilityFunctions::print("Camera creation failed!");
    } else {
        UtilityFunctions::print("Camera created successfully.");
    }

    add_child(camera);
    camera->set_position(Vector3(0, 1.5f, 0));

    if (camera->is_inside_tree()) {
        UtilityFunctions::print("Camera added to tree successfully.");
    } else {
        UtilityFunctions::print("Camera not added to tree.");
    }
}

    void Player::_process(double p_delta)
    {
        CharacterBody3D::_process(p_delta);
    }


    void Player::_exit_tree()
{
    CharacterBody3D::_exit_tree();
}

void Player::_physics_process(double p_delta)
{
    CharacterBody3D::_physics_process(p_delta);
    if (Engine::get_singleton()->is_editor_hint()) return;

    inputDir = Input::get_singleton()->get_vector("Left", "Right", "Forward", "Backward").normalized();
    wishDir = get_transform().basis.xform(Vector3(-inputDir.x, 0, -inputDir.y));

    if(is_on_floor())
    {
        _handle_ground_physics(p_delta);
    }
    else
    {
        _handle_air_physics(p_delta);
    }


    move_and_slide();
}

void Player::_enter_tree()
{
    CharacterBody3D::_enter_tree();
}

void Player::_unhandled_input(const Ref<InputEvent>& p_event)
{
    if (p_event->is_class("InputEventMouseMotion")) {
        auto *mouseMotionEvent = dynamic_cast<InputEventMouseMotion *>(*p_event);
        _mouse_look(mouseMotionEvent);
    }
}

void Player::_handle_ground_physics(double p_delta)
{
    _set_velocity_x(wishDir.x * GROUND_ACCELERATION);
    _set_velocity_z(wishDir.z * GROUND_ACCELERATION);
}

void Player::_handle_air_physics(double p_delta)
{
    _subtract_velocity_y(ProjectSettings::get_singleton()->get_setting("physics/3d/default_gravity").FLOAT * static_cast<float>(p_delta));
}


    void Player::_mouse_look(const Ref<InputEventMouseMotion>& p_event)
{
    if (camera == nullptr) {
        UtilityFunctions::print("Camera is null during mouse look!");
        return;
    }

    if (Engine::get_singleton()->is_editor_hint()) return;

    Vector2 mouseMotion = p_event->get_relative();
    camera->rotate_y(Math::deg_to_rad(-mouseMotion.x * SENSITIVITY));
    mouseRotation.x += Math::deg_to_rad(-mouseMotion.y * SENSITIVITY);
    mouseRotation.x = Math::clamp(mouseRotation.x, Math::deg_to_rad(-89.0f), Math::deg_to_rad(89.0f));

    mouseRotation.z += Math::deg_to_rad(-mouseMotion.y * SENSITIVITY * inputDir.length());
    mouseRotation.z = Math::clamp(mouseRotation.z, Math::deg_to_rad(-85.0f), Math::deg_to_rad(85.0f));

    mouseRotation.z = Math::lerp(mouseRotation.z, 0.0f, static_cast<float>(get_physics_process_delta_time()) * 7.0f);

    Transform3D t = camera->get_transform();
    t.basis = get_basis();
    camera->set_transform(t);

    camera->rotate_object_local(Vector3(1, 0, 0), mouseRotation.x);
}


void Player::_set_velocity_x(float value)
{
    Vector3 v = get_velocity();
    v.x = value;
    set_velocity(v);
}

void Player::_set_velocity_y(float value)
{
    Vector3 v = get_velocity();
    v.y = value;
    set_velocity(v);
}

void Player::_set_velocity_z(float value)
{
    Vector3 v = get_velocity();
    v.z += value;
    set_velocity(v);
}

    void Player::_add_velocity_x(float value)
{
    Vector3 v = get_velocity();
    v.x += value;
    set_velocity(v);
}

    void Player::_add_velocity_y(float value)
{
    Vector3 v = get_velocity();
    v.y += value;
    set_velocity(v);
}

    void Player::_add_velocity_z(float value)
{
    Vector3 v = get_velocity();
    v.z += value;
    set_velocity(v);
}
    void Player::_subtract_velocity_x(float value)
{
    Vector3 v = get_velocity();
    v.x -= value;
    set_velocity(v);
}

    void Player::_subtract_velocity_y(float value)
{
    Vector3 v = get_velocity();
    v.y -= value;
    set_velocity(v);
}

    void Player::_subtract_velocity_z(float value)
{
    Vector3 v = get_velocity();
    v.z -= value;
    set_velocity(v);
}

} // FearTheCrow