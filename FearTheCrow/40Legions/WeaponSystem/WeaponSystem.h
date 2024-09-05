//
// Created by Brandon Friend on 9/3/24.
//

#ifndef WEAPONSYSTEM_H
#define WEAPONSYSTEM_H
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include "Weapon.h"
#include "godot_cpp/godot.hpp"

namespace FearTheCrow {
using namespace godot;
class WeaponSystem : public Node3D {
GDCLASS(WeaponSystem, Node3D)

public:
    void _ready() override;
    void _unhandled_input(const Ref<InputEvent>& p_event) override;
    void _process(double p_delta) override;
    bool HasWeaponActive();
    void SetActiveWeapon(int index);
    Node3D* GetCameraNode();
RayCast3D* GetHitscan();
void ConnectSignals();
    Weapon GetActiveWeapon();
    int GetActiveWeaponIndex();
    void AddWeapon(Weapon newWeapon);
    void RemoveWeapon(Weapon newWeapon);

    TypedArray<Weapon> GetWeapons();
    void SetWeapons(TypedArray<Weapon> weapons);



private:
    MeshInstance3D* weaponRenderer = nullptr;
    TypedArray<Weapon> weaponInventory;
    int activeWeaponIndex = 0;


protected:
    static void _bind_methods();

};

} // FearTheCrow

#endif //WEAPONSYSTEM_H
