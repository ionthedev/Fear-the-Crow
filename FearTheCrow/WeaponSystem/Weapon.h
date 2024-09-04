//
// Created by Brandon Friend on 9/3/24.
//

#ifndef WEAPON_H
#define WEAPON_H
#include <godot_cpp/godot.hpp>
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

    void ExecuteFeature();

    bool HasFeature();

    void SetMesh(Mesh* _weaponMesh);
    Mesh* GetMesh();

private:
    Vector<WeaponFeature> features;
    Mesh* weaponMesh = nullptr;
    Vector3 weaponAnchor = Vector3(0.145f, -0.15f, -0.1f);

protected:
    static void _bind_methods();
};

} // FearTheCrow

#endif //WEAPON_H
