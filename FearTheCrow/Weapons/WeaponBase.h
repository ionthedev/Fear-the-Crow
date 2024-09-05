//
// Created by Brandon Friend on 9/4/24.
//

#ifndef WEAPONBASE_H
#define WEAPONBASE_H


#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/animation_tree.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/timer.hpp>

namespace FearTheCrow {
    using namespace godot;
    class WeaponBase : Node3D
    {
        GDCLASS(WeaponBase, Node3D);

    public:
        void _ready() override;
        void _unhandled_input(const Ref<InputEvent>& p_event) override;

        virtual void Fire();
        virtual void Reload();

        virtual void SetAnimationTree(AnimationTree* a_AnimationTree);
        virtual AnimationTree* GetAnimationTree() const;

        virtual void SetFireRateTimer(Timer* a_Timer);
        virtual Timer* GetFireRateTimer() const;

        virtual void SetReloadTimer(Timer* a_Timer);
        virtual Timer* GetReloadTimer() const;

        virtual void SetMeshInstance(MeshInstance3D* a_MeshInstance);
        virtual MeshInstance3D* GetMeshInstance() const;

        virtual void SetMuzzleFlash(PackedScene* a_PackedScene);
        virtual PackedScene* GetMuzzleFlash() const;

        virtual void SetTracer(PackedScene* a_PackedScene);
        virtual PackedScene* GetTracer() const;

        virtual void SetProjectile(PackedScene* a_PackedScene);
        virtual PackedScene* GetProjectile() const;

        virtual void SetFireRate(float a_Rate);
        virtual float GetFireRate() const;

        virtual void SetRange(float a_Range);
        virtual float GetRange() const;

        virtual void SetSpray(float a_Spray);
        virtual float GetSpray() const;

        virtual void SetKickback(float a_Kickback);
        virtual float GetKickback() const;

        virtual void SetRoundsPerShot(int a_RoundsPerShot);
        virtual int GetRoundsPerShot() const;

        virtual void SetMaxAmmo(int a_MaxAmmo);
        virtual int GetMaxAmmo() const;

        virtual void SetCurrentAmmo(int a_CurrentAmmo);
        virtual int GetCurrentAmmo() const;

        virtual void SetCurrentMagazines(int a_CurrentMag);
        virtual int GetCurrentMagazines() const;

        virtual void SetRangeModifier(float a_RangeModifier);
        virtual float GetRangeModifier() const;

        virtual void SetSprayModifier(float a_SprayModifier);
        virtual float GetSprayModifier() const;

        virtual void SetKickbackModifier(float a_KickbackModifier);
        virtual float GetKickbackModifier() const;


    protected:
        static void _bind_methods();

    private:
        float m_FireRate;
        float m_Range;
        float m_Spray;
        float m_Kickback;

        int m_RoundsPerShot;
        int m_MaxAmmoPerMag;
        int m_CurrentAmmo;
        int m_CurrentMagazines;

        float m_RangeModifier;
        float m_SprayModifier;
        float m_KickbackModifier;

        AnimationTree* m_AnimationTree;
        Timer* m_FireRateTimer;
        Timer* m_ReloadTimer;
        MeshInstance3D* m_MeshInstance;
        PackedScene* m_MuzzleFlash;
        PackedScene* m_Tracer;
        PackedScene* m_Projectile;



    };


} // FearTheCrow

#endif //WEAPONBASE_H
