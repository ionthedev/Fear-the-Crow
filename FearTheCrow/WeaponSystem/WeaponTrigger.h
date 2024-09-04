//
// Created by Brandon Friend on 9/1/24.
//

#ifndef WEAPONTRIGGER_H
#define WEAPONTRIGGER_H
#include "WeaponFeature.h"

namespace FearTheCrow {

class WeaponTrigger : public WeaponFeature  {
    GDCLASS(WeaponTrigger, WeaponFeature)


protected:
    static void _bind_methods();

public:
    void PreExecution(String event) override;
    void OnExecution() override;
    void PostExecution() override;
    bool CanExecute(String event) override;



private:
    WeaponFeature* triggeredFeature;

};

} // FearTheCrow

#endif //WEAPONTRIGGER_H
