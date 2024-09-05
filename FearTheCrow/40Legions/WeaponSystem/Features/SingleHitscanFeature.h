//
// Created by Brandon Friend on 9/1/24.
//

#ifndef SINGLEHITSCANFEATURE_H
#define SINGLEHITSCANFEATURE_H
#include "../WeaponFeature.h"
#include <godot_cpp/classes/ray_cast3d.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>



namespace FearTheCrow {

class SingleHitscanFeature : public WeaponFeature  {
    GDCLASS(SingleHitscanFeature, WeaponFeature)
public:
    void PreExecution(String event) override;
    void OnExecution() override;
    void PostExecution() override;
    bool CanExecute(String event) override;
    void SetRange(float _range);
    float GetRange() const;
    void SetSpray(float _spray);
    float GetSpray() const;

    void SetBullethole(Ref<PackedScene> _bullethole);
    Ref<PackedScene> GetBullethole() const;
    Ref<PackedScene> bulletHole;
protected:
    static void _bind_methods();

private:
    float range = 10.f;
    float spray = 0.125f;
    RayCast3D* hitscan = memnew(RayCast3D);

};

} // FearTheCrow

#endif //SINGLEHITSCANFEATURE_H
