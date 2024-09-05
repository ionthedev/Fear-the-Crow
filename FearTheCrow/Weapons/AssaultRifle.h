//
// Created by Brandon Friend on 9/4/24.
//

#ifndef ASSAULTRIFLE_H
#define ASSAULTRIFLE_H

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node3d.hpp>

namespace FearTheCrow {

    using namespace godot;
    class AssaultRifle : Node3D {
        GDCLASS(AssaultRifle, Node3D);

    public:
        void _ready() override;
        void _unhandled_input(const Ref<InputEvent>& p_event) override;

    protected:
        static void _bind_methods();

    private:
        float fireRate;
        float range;
        float spray;
        float kickback;

    };

} // FearTheCrowFearTheCrow

#endif //ASSAULTRIFLE_H
