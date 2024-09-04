//
// Created by Brandon Friend on 9/3/24.
//

#ifndef WEAPONSYSTEM_H
#define WEAPONSYSTEM_H
#include <godot_cpp/classes/node3d.hpp>

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
    Weapon GetActiveWeapon();
    int GetActiveWeaponIndex();
    void AddWeapon(Weapon newWeapon);
    void RemoveWeapon(int index);

private:
    MeshInstance3D* weaponRenderer = nullptr;
    Vector<Weapon*> weaponInventory;
    int activeWeaponIndex = -1;


protected:
    static void _bind_methods();

};

} // FearTheCrow

#endif //WEAPONSYSTEM_H
