//
// Created by Brandon Friend on 9/3/24.
//

#ifndef WEAPON_H
#define WEAPON_H
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/resource.hpp>

#include "WeaponFeature.h"


namespace FearTheCrow {
using namespace godot;
class Weapon : public Resource {
    GDCLASS(Weapon, Resource)

public:
    void PreActivate();
    void OnActivate();
    void PostActivate();

    void PreDeactivate();
    void OnDeactivate();
    void PostDeactivate();

    void ExecuteFeature(String p_event);
    void SetFeatures(TypedArray<WeaponFeature> _features);
    TypedArray<WeaponFeature> GetFeatures();

    bool HasFeature(WeaponFeature feature);

    void SetMesh(Mesh* _weaponMesh);
    Mesh* GetMesh();
    void SetSystem(WeaponSystem* system);
    const Weapon* GetWeapon() const{return this;}

private:
    TypedArray<WeaponFeature> features;
    Mesh* weaponMesh = nullptr;
    Vector3 weaponAnchor = Vector3(0.145f, -0.15f, -0.1f);
    WeaponSystem* weapon_system;

protected:
    static void _bind_methods();
};


} // FearTheCrow

#endif //WEAPON_H
