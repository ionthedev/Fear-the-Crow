//
// Created by Brandon Friend on 9/1/24.
//

#include "SingleHitscanFeature.h"

#include <godot_cpp/variant/utility_functions.hpp>

namespace FearTheCrow {
    void SingleHitscanFeature::PreExecution(InputEvent* event)
    {
        WeaponFeature::PreExecution(event);
        hitscan = new RayCast3D;
        hitscan->set_target_position(Vector3(UtilityFunctions::randf_range(-GetSpray(), GetSpray()), UtilityFunctions::randf_range(-GetSpray(), GetSpray()), GetRange()));
    }

    void SingleHitscanFeature::OnExecution()
    {
        WeaponFeature::OnExecution();
        if(hitscan == nullptr) return;

        hitscan->force_raycast_update();
    }

    void SingleHitscanFeature::PostExecution()
    {
        WeaponFeature::PostExecution();
        if(hitscan->get_collider())
        {
            UtilityFunctions::print(hitscan->get_collider_rid());
        }
    }

    bool SingleHitscanFeature::CanExecute(InputEvent* event)
    {
        return WeaponFeature::CanExecute(event);
    }


    void SingleHitscanFeature::SetRange(float _range)
    {
        range = _range;
    }

    float SingleHitscanFeature::GetRange() const
    {
        return range;
    }

    void SingleHitscanFeature::SetSpray(float _spray)
    {
        spray = _spray;
    }

    float SingleHitscanFeature::GetSpray() const
    {
        return spray;
    }

    void SingleHitscanFeature::_bind_methods()
    {
    }
} // FearTheCrow