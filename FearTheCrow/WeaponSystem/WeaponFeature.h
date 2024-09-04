//
// Created by Brandon Friend on 9/1/24.
//

#ifndef WEAPONFEATURE_H
#define WEAPONFEATURE_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/classes/input_event_action.hpp>
#include <godot_cpp/classes/ray_cast3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/packed_scene.hpp>


namespace FearTheCrow {
using namespace godot;
    class WeaponSystem;
class WeaponFeature : public Resource {
    GDCLASS(WeaponFeature, Resource)

public:
    virtual void PreExecution(String event);
    virtual void OnExecution();
    virtual void PostExecution();
    virtual bool CanExecute(String event);

    void SetExecutionAction(String event);
    String GetExecutionAction();


    void SetSystem(WeaponSystem* system);

    bool operator==(const WeaponFeature& other) const {
        return exectutionEvent == other.exectutionEvent;
    }
    WeaponSystem* weapon_system = nullptr;

protected:
    static void _bind_methods();

private:
    String exectutionEvent = "";


};

} // FearTheCrow

#endif //WEAPONFEATURE_H
