//
// Created by Brandon Friend on 7/26/24.
//

#include "Player.h"





void Player::Init()
{
    Husk::Init();
}

void Player::Start()
{
    Husk::Start();

}

void Player::Update(double _deltaTime)
{
    Husk::Update(_deltaTime);
}

void Player::FixedUpdate(double _deltaTime)
{

    HandleInput();
    Husk::FixedUpdate(_deltaTime);
}

void Player::Render()
{
    Husk::Render();
}

void Player::HandleInput()
{
    Husk::HandleInput();
    float forward;
    float right;
    if(IsKeyDown(KEY_W))
    {
        forward = walkSpeed;
    }
    else if(IsKeyDown(KEY_S))
    {
        forward = -walkSpeed;
    }
    else
    {
        forward = 0;
    }

    if(IsKeyDown(KEY_D))
    {
        right = walkSpeed;
    }
    else if(IsKeyDown(KEY_A))
    {
        right = -walkSpeed;
    }
    else
    {
        right = 0;
    }

    std::cout << forward << std::endl;
    std::cout << right << std::endl;
    HandleMovement(forward, right, 0.0f);


}

void Player::SetIsActive(bool _isActive)
{
    Husk::SetIsActive(_isActive);
}

bool Player::GetIsActive()
{
    return Husk::GetIsActive();
}

Camera& Player::GetPlayerCamera()
{
    return camera;
}

void Player::HandleMovement(float forward, float right, float up)
{
    Husk::HandleMovement(forward, right, up);


    Vector3* movementVector = new Vector3();
    movementVector->x = forward;
    movementVector->y = 0;
    movementVector->z = right;

    Vector3* cameraRotation = new Vector3();
    cameraRotation->x = GetMouseDelta().x * 0.05f;
    cameraRotation->y = GetMouseDelta().y * 0.05f;
    cameraRotation->z = 0;

    UpdateCameraPro(&GetPlayerCamera(), *movementVector, *cameraRotation, 1.0f);
}

Camera Player::camera = Camera
{
    Vector3{ 0.f, 1.8f, 0.f },  // position
    Vector3{ 0.0f, 0.0f, 20.0f }, // target
    Vector3{ 0.0f, 1.0f, 0.0f }, // up
    90.0f,
    CAMERA_FIRST_PERSON
};

