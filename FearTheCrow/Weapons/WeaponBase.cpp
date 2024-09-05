//
// Created by Brandon Friend on 9/4/24.
//

#include "WeaponBase.h"

namespace FearTheCrow {
    void WeaponBase::_ready()
    {
        Node3D::_ready();
    }

    void WeaponBase::_unhandled_input(const Ref<InputEvent>& p_event)
    {
        Node3D::_unhandled_input(p_event);
    }

    void WeaponBase::Fire()
    {
    }

    void WeaponBase::Reload()
    {

    }

    void WeaponBase::SetAnimationTree(AnimationTree* a_AnimationTree)
    {
        m_AnimationTree = a_AnimationTree;
    }

    AnimationTree* WeaponBase::GetAnimationTree() const
    {
        return m_AnimationTree;
    }

    void WeaponBase::SetFireRateTimer(Timer* a_Timer)
    {
        m_FireRateTimer = a_Timer;
    }

    Timer* WeaponBase::GetFireRateTimer() const
    {
        return m_FireRateTimer;
    }

    void WeaponBase::SetReloadTimer(Timer* a_Timer)
    {
        m_ReloadTimer = a_Timer;
    }

    Timer* WeaponBase::GetReloadTimer() const
    {
        return m_ReloadTimer;
    }

    void WeaponBase::SetMeshInstance(MeshInstance3D* a_MeshInstance)
    {
        m_MeshInstance = a_MeshInstance;
    }

    MeshInstance3D* WeaponBase::GetMeshInstance() const
    {
        return m_MeshInstance;
    }

    void WeaponBase::SetMuzzleFlash(PackedScene* a_PackedScene)
    {
        m_MuzzleFlash = a_PackedScene;
    }

    PackedScene* WeaponBase::GetMuzzleFlash() const
    {
        return m_MuzzleFlash;
    }

    void WeaponBase::SetTracer(PackedScene* a_PackedScene)
    {
        m_Tracer = a_PackedScene;
    }

    PackedScene* WeaponBase::GetTracer() const
    {
        return m_Tracer;
    }

    void WeaponBase::SetProjectile(PackedScene* a_PackedScene)
    {

    }

    PackedScene* WeaponBase::GetProjectile() const
    {
        return m_Projectile;
    }

    void WeaponBase::SetFireRate(float a_Rate)
    {
        m_FireRate = a_Rate;
    }

    float WeaponBase::GetFireRate() const
    {
        return m_FireRate;
    }

    void WeaponBase::SetRange(float a_Range)
    {
        m_Range = a_Range;
    }

    float WeaponBase::GetRange() const
    {
        return m_Range;
    }

    void WeaponBase::SetSpray(float a_Spray)
    {
        m_Spray = a_Spray;
    }

    float WeaponBase::GetSpray() const
    {
        return m_Spray;
    }

    void WeaponBase::SetKickback(float a_Kickback)
    {
        m_Kickback = a_Kickback;
    }

    float WeaponBase::GetKickback() const
    {
        return m_Kickback;
    }

    void WeaponBase::SetRoundsPerShot(int a_RoundsPerShot)
    {
    }

    int WeaponBase::GetRoundsPerShot() const
    {
        return m_RoundsPerShot;
    }

    void WeaponBase::SetMaxAmmo(int a_MaxAmmo)
    {
        m_MaxAmmoPerMag = a_MaxAmmo;
    }

    int WeaponBase::GetMaxAmmo() const
    {
        return m_MaxAmmoPerMag;
    }

    void WeaponBase::SetCurrentAmmo(int a_CurrentAmmo)
    {
        m_CurrentAmmo = a_CurrentAmmo;
    }

    int WeaponBase::GetCurrentAmmo() const
    {
        return m_CurrentAmmo;
    }

    void WeaponBase::SetCurrentMagazines(int a_CurrentMag)
    {
        m_CurrentMagazines = a_CurrentMag;
    }

    int WeaponBase::GetCurrentMagazines() const
    {
        return m_CurrentMagazines;
    }

    void WeaponBase::SetRangeModifier(float a_RangeModifier)
    {
        m_RangeModifier = a_RangeModifier;
    }

    float WeaponBase::GetRangeModifier() const
    {
        return m_RangeModifier;
    }

    void WeaponBase::SetSprayModifier(float a_SprayModifier)
    {
        m_SprayModifier = a_SprayModifier;
    }

    float WeaponBase::GetSprayModifier() const
    {
        return m_SprayModifier;
    }

    void WeaponBase::SetKickbackModifier(float a_KickbackModifier)
    {
        m_KickbackModifier = a_KickbackModifier;
    }

    float WeaponBase::GetKickbackModifier() const
    {
        return m_KickbackModifier;
    }

    void WeaponBase::_bind_methods()
    {
    }
} // FearTheCrow