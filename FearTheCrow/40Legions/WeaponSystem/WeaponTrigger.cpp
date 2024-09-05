//
// Created by Brandon Friend on 9/4/24.
//
#include "WeaponTrigger.h"

namespace FearTheCrow
{

    void WeaponTrigger::_bind_methods()
    {

    }

    void WeaponTrigger::PreExecution(String event)
    {
        WeaponFeature::PreExecution(event);
    }

    void WeaponTrigger::OnExecution()
    {
        WeaponFeature::OnExecution();
    }

    void WeaponTrigger::PostExecution()
    {
        WeaponFeature::PostExecution();
    }

    bool WeaponTrigger::CanExecute(String event)
    {
        return WeaponFeature::CanExecute(event);
    }

}
