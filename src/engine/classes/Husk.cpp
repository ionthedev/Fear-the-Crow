//
// Created by Brandon Friend on 7/21/24.
//

#include "Husk.h"


void Husk::Init()
{
    GameObject::Init();
}

void Husk::Start()
{
    GameObject::Start();
}

void Husk::Update(double _deltaTime)
{
    GameObject::Update(_deltaTime);
}

void Husk::FixedUpdate(double _deltaTime)
{
    GameObject::FixedUpdate(_deltaTime);
}

void Husk::Render()
{
    GameObject::Render();
}

void Husk::HandleInput()
{
    GameObject::HandleInput();
}

void Husk::SetIsActive(bool _isActive)
{
    GameObject::SetIsActive(_isActive);
}

bool Husk::GetIsActive()
{
    return GameObject::GetIsActive();
}

void Husk::HandleMovement()
{
}