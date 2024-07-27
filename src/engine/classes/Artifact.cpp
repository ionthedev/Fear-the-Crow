//
// Created by Brandon Friend on 7/25/24.
//

#include "Artifact.h"

Artifact::Artifact()
{
    Artifact::Init();
}

Artifact::~Artifact()
{
}

void Artifact::Init()
{
    Artifact::SetIsActive(true);
}

void Artifact::Start()
{
}

void Artifact::Update(double _deltaTime)
{
}

void Artifact::FixedUpdate(double _deltaTime)
{
    HandleInput();
}

void Artifact::Render()
{
}

void Artifact::HandleInput()
{
}

bool Artifact::GetIsActive()
{
    return m_isActive;
}

void Artifact::SetIsActive(bool _isActive)
{
    m_isActive = _isActive;
}
