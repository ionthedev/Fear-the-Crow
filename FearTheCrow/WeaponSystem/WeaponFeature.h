//
// Created by Brandon Friend on 9/1/24.
//

#ifndef WEAPONFEATURE_H
#define WEAPONFEATURE_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/classes/input_event_action.hpp>

namespace FearTheCrow {
using namespace godot;
class WeaponFeature : public Resource {
    GDCLASS(WeaponFeature, Resource)

public:
    virtual void PreExecution(InputEvent* event);
    virtual void OnExecution();
    virtual void PostExecution();
    virtual bool CanExecute(InputEvent* event);
    void SetExecutionAction(InputEvent* event);
    InputEvent* GetExecutionAction();

protected:
    static void _bind_methods();

private:
    InputEvent* exectutionEvent;
};

} // FearTheCrow

#endif //WEAPONFEATURE_H
