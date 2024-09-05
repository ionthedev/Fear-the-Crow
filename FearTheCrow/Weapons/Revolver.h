//
// Created by Brandon Friend on 9/4/24.
//

#ifndef REVOLVER_H
#define REVOLVER_H
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node3d.hpp>

#include "WeaponBase.h"

namespace FearTheCrow {
using namespace godot;
class Revolver : WeaponBase {
    GDCLASS(Revolver, WeaponBase);

protected:
    static void _bind_methods();





};

} // FearTheCrow

#endif //REVOLVER_H
