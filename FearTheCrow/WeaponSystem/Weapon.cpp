//
// Created by Brandon Friend on 9/3/24.
//

#include "Weapon.h"

#include <godot_cpp/variant/utility_functions.hpp>

namespace FearTheCrow {
    void Weapon::PreActivate()
    {

    }

    void Weapon::OnActivate()
    {
    }

    void Weapon::PostActivate()
    {
    }

    void Weapon::PreDeactivate()
    {
    }

    void Weapon::OnDeactivate()
    {
    }

    void Weapon::PostDeactivate()
    {
    }

    void Weapon::ExecuteFeature(String p_event)
    {
        for (int i = 0; i < features.size(); ++i)
        {
            WeaponFeature* feature = cast_to<WeaponFeature>(features[i]);
            feature->PreExecution(p_event);
        }
    }

    void Weapon::SetFeatures(TypedArray<WeaponFeature> _features)
    {
        features = _features;
    }

    TypedArray<WeaponFeature> Weapon::GetFeatures()
    {
        return features;
    }

    bool Weapon::HasFeature(WeaponFeature feature)
    {
        return features.has(&feature);
    }

    void Weapon::SetMesh(Mesh* _weaponMesh)
    {
        weaponMesh = _weaponMesh;
    }

    Mesh* Weapon::GetMesh()
    {
        return weaponMesh;
    }

    void Weapon::SetSystem(WeaponSystem* system)
    {
        weapon_system = system;
        for (int i = 0; i < features.size(); ++i)
        {
            WeaponFeature* feature = cast_to<WeaponFeature>(features[i]);
            feature->SetSystem(system);
        }
    }

    void Weapon::_bind_methods()
    {


        ADD_SIGNAL(MethodInfo("onFireOne", PropertyInfo(Variant::STRING, "InputActionName")));
        ADD_SIGNAL(MethodInfo("onFireTwo", PropertyInfo(Variant::STRING, "InputActionName")));
        ADD_SIGNAL(MethodInfo("onFireThree", PropertyInfo(Variant::STRING, "InputActionName")));
        ADD_SIGNAL(MethodInfo("onScroll", PropertyInfo(Variant::STRING, "InputActionName")));
        ADD_SIGNAL(MethodInfo("onReload", PropertyInfo(Variant::STRING, "InputActionName")));

        ClassDB::bind_method(D_METHOD("SetFeatures", "weapons"), &Weapon::SetFeatures);
        ClassDB::bind_method(D_METHOD("GetFeatures"), &Weapon::GetFeatures);
        ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "features", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "WeaponFeature")), "SetFeatures", "GetFeatures");

    }
} // FearTheCrow