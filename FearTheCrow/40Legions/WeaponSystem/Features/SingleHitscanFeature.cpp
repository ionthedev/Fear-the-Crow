//
// Created by Brandon Friend on 9/1/24.
//

#include "SingleHitscanFeature.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "../WeaponSystem.h"

namespace FearTheCrow {
    void SingleHitscanFeature::PreExecution(String event)
    {
        WeaponFeature::PreExecution(event);
         weapon_system->GetHitscan()->set_target_position(Vector3(UtilityFunctions::randf_range(-GetSpray(), GetSpray()), UtilityFunctions::randf_range(-GetSpray(), GetSpray()), -GetRange()));

    }



    void SingleHitscanFeature::OnExecution()
    {
        WeaponFeature::OnExecution();

         weapon_system->GetHitscan()->force_raycast_update();
    }

    void SingleHitscanFeature::PostExecution()
    {
        WeaponFeature::PostExecution();
        if(weapon_system->GetHitscan()->get_collider())
        {
            UtilityFunctions::print(cast_to<Node>(weapon_system->GetHitscan()->get_collider())->get_name());
                Node *instantiated_node = bulletHole->instantiate();
                Node3D *decal = cast_to<Node3D>(instantiated_node);
                SceneTree* tree = weapon_system->get_tree();
                tree->get_current_scene()->add_child(decal);
                Vector3 normal = weapon_system->GetHitscan()->get_collision_normal();
                decal->set_global_position(weapon_system->GetHitscan()->get_collision_point());



            if(normal != Vector3(0,1,0) && normal != Vector3(0,-1,0))
            {
                decal->rotate_object_local(Vector3(1,0,0), 90);
            }



        }

    }

    bool SingleHitscanFeature::CanExecute(String event)
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

    void SingleHitscanFeature::SetBullethole(Ref<PackedScene> _bullethole)
    {
        bulletHole = _bullethole;
    }

    Ref<PackedScene> SingleHitscanFeature::GetBullethole() const
    {
        return bulletHole;
    }

    void SingleHitscanFeature::_bind_methods()
    {

        ClassDB::bind_method(D_METHOD("GetSpray"), &SingleHitscanFeature::GetSpray);
        ClassDB::bind_method(D_METHOD("SetSpray"), &SingleHitscanFeature::SetSpray);
        ClassDB::add_property("SingleHitscanFeature", PropertyInfo(Variant::FLOAT, "Spray"), "SetSpray", "GetSpray");

        ClassDB::bind_method(D_METHOD("GetRange"), &SingleHitscanFeature::GetRange);
        ClassDB::bind_method(D_METHOD("SetRange"), &SingleHitscanFeature::SetRange);
        ClassDB::add_property("SingleHitscanFeature", PropertyInfo(Variant::FLOAT, "Range"), "SetRange", "GetRange");

        ClassDB::bind_method(D_METHOD("GetBullethole"), &SingleHitscanFeature::GetBullethole);
        ClassDB::bind_method(D_METHOD("SetBullethole", "_bulletHole"), &SingleHitscanFeature::SetBullethole);
        ClassDB::add_property("SingleHitscanFeature", PropertyInfo(Variant::OBJECT, "bulletHole", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "SetBullethole", "GetBullethole");
    }
} // FearTheCrow