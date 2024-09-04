//
// Created by Brandon Friend on 9/1/24.
//

#include "WeaponFeature.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/ray_cast3d.hpp>

#include "WeaponSystem.h"

namespace FearTheCrow {
    void WeaponFeature::PreExecution(String event)
    {
        if(CanExecute(event))
            OnExecution();
    }

    void WeaponFeature::OnExecution()
    {
        PostExecution();
    }

    void WeaponFeature::PostExecution()
    {
    }

    bool WeaponFeature::CanExecute(String event)
    {
        if(exectutionEvent == event)
            return true;
        else
            return false;
    }

    void WeaponFeature::SetExecutionAction(String event)
    {
        exectutionEvent = event;
    }

    String WeaponFeature::GetExecutionAction()
    {
        return exectutionEvent;
    }



    void WeaponFeature::SetSystem(WeaponSystem* system)
    {
        weapon_system = system;
    }

    void WeaponFeature::_bind_methods()
    {
        ClassDB::bind_method(D_METHOD("GetExecutionAction"), &WeaponFeature::GetExecutionAction);
        ClassDB::bind_method(D_METHOD("SetExecutionAction", "InputEventAction"), &WeaponFeature::SetExecutionAction);
        ClassDB::add_property("WeaponFeature", PropertyInfo(Variant::STRING , "InputEventAction"), "SetExecutionAction", "GetExecutionAction");
    }

} // FearTheCrow