//
// Created by Brandon Friend on 9/4/24.
//

#ifndef SEMIAUTOTRIGGER_H
#define SEMIAUTOTRIGGER_H
#include "../WeaponTrigger.h"

namespace FearTheCrow {

class SemiAutoTrigger : public WeaponTrigger  {
    GDCLASS(SemiAutoTrigger, WeaponTrigger)

protected:
    static void _bind_methods();

public:
    void PreExecution(String event) override;
    void OnExecution() override;
    void PostExecution() override;
    bool CanExecute(String event) override;
    void SetFireRate(float fireRate);
    float GetFireRate() const;

private:
    float fireRate;

};

} // FearTheCrow

#endif //SEMIAUTOTRIGGER_H
