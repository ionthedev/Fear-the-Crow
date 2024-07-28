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

    CalculateMovement(_deltaTime);
}

void Player::FixedUpdate(double _deltaTime)
{

    HandleInput();
    Husk::FixedUpdate(_deltaTime);

    //CameraYaw(&camera, GetMouseDelta().x * 0.004f, false);

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
    Husk::HandleMovement();

}

void Player::CalculateMovement(double _deltaTime)
{

    // Update the velocity based on the wish direction and player speed
    velocity = Vector3Scale(wishDir(), CURR_SPEED * _deltaTime);

    // Update the position based on the velocity
    position = Vector3Add(position, velocity);

    // Update the camera position based on the player's position
    camera.position = position;

    // Optionally update the camera target to maintain a specific view direction
    camera.target = Vector3Add(camera.position, Vector3Normalize(Vector3Subtract(camera.target, camera.position)));
}

Vector3 Player::Friction(Vector3 _velocity, float _deltaTime)
{

    return Vector3Scale(_velocity, GROUND_FRICTION * _deltaTime);
}

Vector3 Player::wishDir()
{
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));

    // Right direction is perpendicular to forward and up vector (assuming up vector is (0, 1, 0))
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, { 0, 1, 0 }));

    // Wish direction is a combination of forward and right directions
    Vector3 wishDir = {
        forward.x * inputDir().z + right.x * inputDir().x,
        0, // We don't want any vertical movement here
        forward.z * inputDir().z + right.z * inputDir().x};

    wishDir = Vector3Normalize(wishDir);

    std::cout << "Vector3(" << wishDir.x << ", " << wishDir.y << ", " << wishDir.z << ")" << std::endl;

    return wishDir;

}

Vector3 Player::CalculateGroundVelocity(Vector3 _wishDir, Vector3 _velocity, float _deltaTime)
{
    //_velocity = Friction(_velocity, deltaTime);
    //float ADD_SPEED = PhanthomEngine::m_Clip(MAX_SPEED, 0, MAX_SPEED * _deltaTime);
    Vector3 out = Vector3Multiply(_wishDir, Vector3Scale(_velocity, MAX_SPEED * _deltaTime));
    //std::cout << "Vector3(" << _wishDir.x << ", " << _wishDir.y << ", " << _wishDir.z << ")" << std::endl;

    return _wishDir;
}

void Player::SetCameraRotation()
{
    Vector3 forward = GetCameraForward(&GetPlayerCamera());
    Vector3 right = GetCameraRight(&GetPlayerCamera());

    rotation.x = asinf(forward.y) * RAD2DEG;
    rotation.y = atan2f(forward.x, forward.z) * RAD2DEG;
    rotation.z = atan2f(right.y, right.x) * RAD2DEG;

}

Vector3 Player::inputDir()
{
    Vector3 _inputDir = { 0 };
    _inputDir.z = (IsKeyDown(KEY_W) - IsKeyDown(KEY_S));
    _inputDir.x = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));

    if (_inputDir.x != 0 || _inputDir.z != 0) {
        _inputDir = Vector3Normalize(_inputDir);
    }

    return _inputDir;
}

Camera Player::camera = Camera
{
    { 0.0f, 1.0f, 2.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    90.0f,
    CAMERA_PERSPECTIVE


};

