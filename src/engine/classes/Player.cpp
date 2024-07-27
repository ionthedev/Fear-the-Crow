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
    GetPlayerCamera();

}

void Player::Update(double _deltaTime)
{

}

void Player::FixedUpdate(double _deltaTime)
{

    HandleInput();
    Husk::FixedUpdate(_deltaTime);
    HandleMovement();

}

void Player::Render()
{
    Husk::Render();
}

void Player::HandleInput()
{
    Husk::HandleInput();


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

void Player::HandleMovement()
{
    //CameraMoveForward(&GetPlayerCamera(), wishDir(inputDir()).x * MAX_SPEED, true);
    //CameraMoveRight(&GetPlayerCamera(), wishDir(inputDir()).z * MAX_SPEED, true);
    Husk::HandleMovement();
    Vector3 cameraRotation = {GetMouseDelta().x*0.04f, GetMouseDelta().y*0.04f, 0};
    UpdateCameraPro(&GetPlayerCamera(), CalculateGroundVelocity(wishDir(inputDir()), velocity, deltaTime), cameraRotation, 1.0f);
}

Vector3 Player::Friction(Vector3 _velocity, float _deltaTime)
{

    return Vector3Scale(_velocity, GROUND_FRICTION * _deltaTime);
}

Vector3 Player::wishDir(Vector3 _inputDir)
{
    Vector3 forward = Vector3Scale(GetCameraForward(&GetPlayerCamera()), _inputDir.x);
    Vector3 right = Vector3Scale(GetCameraRight(&GetPlayerCamera()), _inputDir.z);

    return Vector3Normalize(Vector3Add(forward, right));

}

Vector3 Player::CalculateGroundVelocity(Vector3 _wishDir, Vector3 _velocity, float _deltaTime)
{
    _velocity = Friction(_velocity, deltaTime);
    float ADD_SPEED = PhanthomEngine::m_Clip(MAX_SPEED - CURR_SPEED, 0, MAX_SPEED * _deltaTime);
    Vector3 out = Vector3Multiply(_velocity, Vector3Scale(_wishDir, ADD_SPEED));
    std::cout << "Vector3(" << out.x << ", " << out.y << ", " << out.z << ")" << std::endl;

    return out;
}

Vector3 Player::inputDir()
{
    float forward = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
    float right = IsKeyDown(KEY_A) - IsKeyDown(KEY_D);

    return { right, 0.0, forward};
}

Camera Player::camera = Camera
{
    { 0.0f, 2.0f, 4.0f },
    { 0.0f, 2.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    60.0f,
    CAMERA_PERSPECTIVE


};

