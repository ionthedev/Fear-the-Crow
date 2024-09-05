//
// Created by Brandon Friend on 9/3/24.
//

#include "WeaponSystem.h"

#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "../Player.h"

namespace FearTheCrow {
    void WeaponSystem::_ready()
    {
        Node3D::_ready();
        weaponRenderer = memnew(MeshInstance3D);
        weaponRenderer->set_position(Vector3(0.145f, -0.15f, -0.1f));
        SetActiveWeapon(0);

    }

    void WeaponSystem::_unhandled_input(const Ref<InputEvent>& p_event)
    {
        Node3D::_unhandled_input(p_event);

        if(Engine::get_singleton()->is_editor_hint()) return;
        if(p_event->is_class("InputEventMouseButton") && p_event->is_pressed())
        {
            auto *mouseButtonEvent = dynamic_cast<InputEventMouseButton *>(*p_event);
            if(mouseButtonEvent->is_action_pressed("Fire1"))
                cast_to<Weapon>(weaponInventory[activeWeaponIndex])->ExecuteFeature("Fire1");

            if(mouseButtonEvent->is_action_pressed("Fire2"))
                cast_to<Weapon>(weaponInventory[activeWeaponIndex])->ExecuteFeature("Fire2");

            if(mouseButtonEvent->is_action_pressed("Fire3"))
                cast_to<Weapon>(weaponInventory[activeWeaponIndex])->ExecuteFeature("Fire3");

            /*if(mouseButtonEvent->is_action_pressed("Scroll"))
                emit_signal("onScroll", p_event);*/

            if(mouseButtonEvent->is_action_pressed("Reload"))
                cast_to<Weapon>(weaponInventory[activeWeaponIndex])->ExecuteFeature("Reload");
        }



            auto *inputEventAction = dynamic_cast<InputEventAction *>(*p_event);

            if(p_event->is_action_pressed("Weapon_1"))
            {
                SetActiveWeapon(0);
            }
            if(p_event->is_action_pressed("Weapon_2"))
            {
                SetActiveWeapon(1);
            }
            if(p_event->is_action_pressed("Weapon_3"))
            {
                SetActiveWeapon(2);
            }
            if(p_event->is_action_pressed("Weapon_4"))
            {
                SetActiveWeapon(3);
            }
            if(p_event->is_action_pressed("Weapon_5"))
            {
                SetActiveWeapon(4);
            }


    }

    void WeaponSystem::_process(double p_delta)
    {
        Node3D::_process(p_delta);
    }

    bool WeaponSystem::HasWeaponActive()
    {
        return activeWeaponIndex != -1 || weaponInventory.size() > -1;
    }

    void WeaponSystem::SetActiveWeapon(int index)
    {

        if(index > weaponInventory.size()) return;

        activeWeaponIndex = index;
        cast_to<Weapon>(weaponInventory[activeWeaponIndex])->SetSystem(this);
    }

    Node3D* WeaponSystem::GetCameraNode()
    {
        Node3D* _camera = cast_to<Node3D>(get_tree()->get_nodes_in_group("PlayerCamera")[0]);
        return _camera;
    }

    RayCast3D* WeaponSystem::GetHitscan()
    {
        RayCast3D* _hitscan = cast_to<RayCast3D>(get_tree()->get_nodes_in_group("Hitscan")[0]);
        return _hitscan;
    }



    void WeaponSystem::ConnectSignals()
    {
        cast_to<Weapon>(weaponInventory[activeWeaponIndex])->connect("onFireOne", Callable(weaponInventory[activeWeaponIndex], "ExecuteFeature"));
        cast_to<Weapon>(weaponInventory[activeWeaponIndex])->connect("onFireTwo", Callable(weaponInventory[activeWeaponIndex], "ExecuteFeature"));
        cast_to<Weapon>(weaponInventory[activeWeaponIndex])->connect("onFireThree", Callable(weaponInventory[activeWeaponIndex], "ExecuteFeature"));
        cast_to<Weapon>(weaponInventory[activeWeaponIndex])->connect("onScroll", Callable(weaponInventory[activeWeaponIndex], "ExecuteFeature"));
        cast_to<Weapon>(weaponInventory[activeWeaponIndex])->connect("onReload", Callable(weaponInventory[activeWeaponIndex], "ExecuteFeature"));
    }

    Weapon WeaponSystem::GetActiveWeapon()
    {
       return *cast_to<Weapon>(weaponInventory[activeWeaponIndex]);
    }

    int WeaponSystem::GetActiveWeaponIndex()
    {
        return activeWeaponIndex;
    }

    void WeaponSystem::AddWeapon(Weapon newWeapon)
    {
        weaponInventory.append(&newWeapon);
        if(activeWeaponIndex == -1)
            SetActiveWeapon(0);
    }

    void WeaponSystem::RemoveWeapon(Weapon newWeapon)
    {
        weaponInventory.erase(&newWeapon);
    }

    void WeaponSystem::SetWeapons(TypedArray<Weapon> weapons)
    {

        weaponInventory = weapons;
    }

    TypedArray<Weapon> WeaponSystem::GetWeapons()
    {
        return weaponInventory;
    }

    void WeaponSystem::_bind_methods()
    {
        ADD_SIGNAL(MethodInfo("onFireOne", PropertyInfo(Variant::STRING, "InputActionName")));
        ADD_SIGNAL(MethodInfo("onFireTwo", PropertyInfo(Variant::STRING, "InputActionName")));
        ADD_SIGNAL(MethodInfo("onFireThree", PropertyInfo(Variant::STRING, "InputActionName")));
        ADD_SIGNAL(MethodInfo("onScroll", PropertyInfo(Variant::STRING, "InputActionName")));
        ADD_SIGNAL(MethodInfo("onReload", PropertyInfo(Variant::STRING, "InputActionName")));

        ClassDB::bind_method(D_METHOD("SetWeapons", "weapons"), &WeaponSystem::SetWeapons);
        ClassDB::bind_method(D_METHOD("GetWeapons"), &WeaponSystem::GetWeapons);
        ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "weapons", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "Weapon")), "SetWeapons", "GetWeapons");

    }
} // FearTheCrow