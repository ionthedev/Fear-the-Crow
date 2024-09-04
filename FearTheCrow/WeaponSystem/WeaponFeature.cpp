//
// Created by Brandon Friend on 9/1/24.
//

#include "WeaponFeature.h"

#include <godot_cpp/classes/input.hpp>

namespace FearTheCrow {
    void WeaponFeature::PreExecution(InputEvent* event)
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

    bool WeaponFeature::CanExecute(InputEvent* event)
    {
        if(exectutionEvent == event)
            return true;
        else
            return false;
    }

    void WeaponFeature::SetExecutionAction(InputEvent* event)
    {
        exectutionEvent = event;
    }

    InputEvent* WeaponFeature::GetExecutionAction()
    {
        return exectutionEvent;
    }

    void WeaponFeature::_bind_methods()
    {
    }
} // FearTheCrow