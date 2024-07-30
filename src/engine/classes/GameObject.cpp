//
// Created by Brandon Friend on 7/25/24.
//

#include "GameObject.h"

GameObject::GameObject()
{
    GameObject::Init();
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
    GameObject::SetIsActive(true);
}

void GameObject::Start()
{
}

void GameObject::Update(double _deltaTime)
{
}

void GameObject::FixedUpdate(double _deltaTime)
{
    HandleInput();
}

void GameObject::Render()
{
}

void GameObject::HandleInput()
{
}

bool GameObject::GetIsActive()
{
    return m_isActive;
}

void GameObject::SetIsActive(bool _isActive)
{
    m_isActive = _isActive;
}
