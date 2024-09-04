//
// Created by Brandon Friend on 9/3/24.
//

#include "WeaponSystem.h"

#include <godot_cpp/classes/input_event_mouse_button.hpp>

namespace FearTheCrow {
    void WeaponSystem::_ready()
    {
        Node3D::_ready();
        weaponRenderer = memnew(MeshInstance3D);
        weaponRenderer->set_position(Vector3(0.145f, -0.15f, -0.1f));
    }

    void WeaponSystem::_unhandled_input(const Ref<InputEvent>& p_event)
    {
        Node3D::_unhandled_input(p_event);

        if(p_event->is_class("InputEventMouseButton") && p_event->is_pressed())
        {
            auto *mouseButtonEvent = dynamic_cast<InputEventMouseButton *>(*p_event);
            if(mouseButtonEvent->is_action_pressed("Fire1"))
                emit_signal("onFireOne", GetActiveWeapon());

            if(mouseButtonEvent->is_action_pressed("Fire2"))
                emit_signal("onFireTwo", GetActiveWeapon());

            if(mouseButtonEvent->is_action_pressed("Fire3"))
                emit_signal("onFireThree", GetActiveWeapon());

            if(mouseButtonEvent->is_action_pressed("Scroll"))
                emit_signal("onScroll", this);

            if(mouseButtonEvent->is_action_pressed("Reload"))
                emit_signal("onReload", GetActiveWeapon());
        }
    }

    void WeaponSystem::_process(double p_delta)
    {
        Node3D::_process(p_delta);
    }

    bool WeaponSystem::HasWeaponActive()
    {
        return activeWeaponIndex != -1 || weaponInventory.size > nullptr;
    }

    void WeaponSystem::SetActiveWeapon(int index)
    {
        activeWeaponIndex = index;
    }

    Weapon WeaponSystem::GetActiveWeapon()
    {
       return *weaponInventory[activeWeaponIndex];
    }

    int WeaponSystem::GetActiveWeaponIndex()
    {
        return activeWeaponIndex;
    }

    void WeaponSystem::AddWeapon(Weapon newWeapon)
    {
        weaponInventory.append(&newWeapon);
    }

    void WeaponSystem::RemoveWeapon(int index)
    {
        //TODO: Deactive the weapon just in case it is currently active.
        weaponInventory.remove_at(index);
    }

    void WeaponSystem::_bind_methods()
    {
    }
} // FearTheCrow