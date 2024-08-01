//
// Created by Brandon Friend on 7/26/24.
//

#include "Player.h"



void Player::Init()
{
    Husk::Init();    camera = *new Camera();
    player_data.lookRotationEuler.x = 0.0f;
    player_data.lookRotationEuler.z = 0.0f;
    player_data.lookRotationEuler.y = PI * 2 - (atan2(-1.0f, -1.0f) * 1.0f); // Placeholder for start direction
    player_data.rotationalVelocity = (Vector3){0, 0, 0};
    player_data.velocity = (Vector3){0, 0.1f, 0.5f};
    player_data.lookDir = (Vector3){0, 0, 1};

}

void Player::Start()
{
    Husk::Start();
}

void Player::Update(double _deltaTime)
{
    Husk::Update(_deltaTime);

    DeltaTime = _deltaTime;
}

bool Player::WishJump() const
{
        return IsKeyDown(KEY_SPACE);
}

void Player::FixedUpdate(double _deltaTime)
{


    Husk::FixedUpdate(_deltaTime);



    Accelerate(PLAYER_SPEED, PLAYER_GROUND_ACCELERATION);
    ProcessJump();
    ApplyGravity();

    UpdateCamera();
    MouseLook(_deltaTime);
    //CalculateInputs(_deltaTime);
    //player_data.velocity = player_data.velocity;
    player_data.lookRotationMat3 = PhantomEngine::MatrixFromYawPitchRoll( player_data.lookRotationEuler.y + player_data.rotationalVelocity.y, Clamp( player_data.lookRotationEuler.x + player_data.rotationalVelocity.x, -PI * 0.5 * 0.95, PI * 0.5 * 0.95), player_data.lookRotationEuler.z + player_data.rotationalVelocity.z);

    player_data.lastPosition = player_data.position;
    player_data.velocity = CalculateFriction(player_data.velocity, PLAYER_GROUND_FRICTION, true, _deltaTime);

    player_data.lastVelocity = player_data.velocity;
    player_data.position = Vector3Add(player_data.position, Vector3Scale(player_data.lastVelocity, (float)DeltaTime));
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

Vector3 Player::GetWishDir()
{
    return WishDir();
}

Vector2 Player::GetMoveDir()
{
    return MoveDir();
}

void Player::MouseLook(const double _deltaTime) {
    const auto fDeltaTime = static_cast<float>(_deltaTime);
    // Update rotational velocity with mouse input
    player_data.rotationalVelocity.y += -GetMouseDelta().x * settings_sensitivity * PLAYER_LOOK_SENSITIVITY;
    player_data.rotationalVelocity.x += GetMouseDelta().y * settings_sensitivity * PLAYER_LOOK_SENSITIVITY;

    // Clamp the pitch (x-axis rotation)
    player_data.lookRotationEuler.x = Clamp(player_data.lookRotationEuler.x + player_data.rotationalVelocity.x * static_cast<float>(_deltaTime), -PI * 0.5 * 0.95, PI * 0.5 * 0.95);

    // Update the look rotation euler angles
    player_data.lookRotationEuler.y += player_data.rotationalVelocity.y * fDeltaTime;

    // Reset the roll (z-axis rotation)
    player_data.lookRotationEuler.z = Lerp(player_data.lookRotationEuler.z, 0.0, Clamp(fDeltaTime * 7.5f, 0.0, 1.0));
    player_data.lookRotationEuler.z -= MoveDir().x * fDeltaTime * 0.75f;
    player_data.lookRotationEuler.z = Clamp(player_data.lookRotationEuler.z, -PI * 0.3f, PI * 0.5f);

    // Create rotation matrix from euler angles
    player_data.lookRotationMat3 = PhantomEngine::MatrixFromYawPitchRoll(player_data.lookRotationEuler.y, player_data.lookRotationEuler.x, player_data.lookRotationEuler.z);

    // Calculate camera direction
    Vector3 camForward = PhantomEngine::MatrixMultiplyVector3(player_data.lookRotationMat3, {0, 0, 1});
    player_data.lookDir = camForward;

    // Update camera position and target
    camera.position = Vector3Add(player_data.position, Vector3Scale(camera.up, PLAYER_HEAD_CENTER_OFFSET));
    camera.target = Vector3Add(camera.position, camForward);

    // Calculate camera up vector
    camera.up = Vector3Normalize(PhantomEngine::QuaternionMultiplyVector3(PhantomEngine::QuaternionAngleAxis(player_data.lookRotationEuler.z * 1.3f, camForward), Vector3{0, 1.0, 0}));

    // Reset rotational velocity
    player_data.rotationalVelocity = {0, 0, 0};

    //std::cout << "Camera Up: Vector3(" << camera.up.x << ", " << camera.up.y << ", " << camera.up.z << ")" << std::endl;
}



void Player::CalculateInputs(double _deltaTime) {
    const auto fDeltaTime = static_cast<float>(_deltaTime);
    Vector3 acceleration = { 0 };
    if (IsKeyDown(KEY_W)) acceleration = Vector3Add(acceleration, player_data.lookDir);
    if (IsKeyDown(KEY_S)) acceleration = Vector3Subtract(acceleration, player_data.lookDir);
    if (IsKeyDown(KEY_A)) acceleration = Vector3Subtract(acceleration, Vector3CrossProduct(player_data.lookDir, (Vector3){0, 1, 0}));
    if (IsKeyDown(KEY_D)) acceleration = Vector3Add(acceleration, Vector3CrossProduct(player_data.lookDir, (Vector3){0, 1, 0}));
    if (IsKeyPressed(PLAYER_KEY_JUMP)) player_data.velocity.y = PLAYER_JUMP_SPEED;


    if (Vector3Length(acceleration) > 0) {
        acceleration = Vector3Normalize(acceleration);
        // if (IsGrounded()) {
        //     player_data.velocity = Vector3Add(player_data.velocity, Vector3Scale(acceleration, PLAYER_SPEED * PLAYER_GROUND_ACCELERATION * fDeltaTime));
        //     player_data.velocity = Vector3Scale(player_data.velocity, pow(PLAYER_GROUND_FRICTION, fDeltaTime));
        // } else {
        //     player_data.velocity = Vector3Add(player_data.velocity, Vector3Scale(acceleration, PLAYER_SPEED * fDeltaTime));
        //     player_data.velocity = Vector3Scale(player_data.velocity, pow(PLAYER_AIR_FRICTION, fDeltaTime));
        // }
    }

    player_data.position = Vector3Add(player_data.position, Vector3Scale(player_data.velocity, fDeltaTime));




}

void Player::UpdateCamera()
{
    camera.position = Vector3Add(player_data.position, (Vector3){0,PLAYER_HEAD_CENTER_OFFSET, 0});
    camera.target = Vector3Add(camera.position, player_data.lookDir);
    camera.up = {0, 1, 0};
    camera.fovy = PLAYER_FOV;
    camera.projection = CAMERA_PERSPECTIVE;
}

Vector2 Player::MoveDir()
{
    Vector2 _moveDir { 0 };
    _moveDir.y += IsKeyDown(KEY_W) ? 1.0f : 0.0f;
    _moveDir.x += IsKeyDown(KEY_A) ? 1.0f : 0.0f;
    _moveDir.y -= IsKeyDown(KEY_S) ? 1.0f : 0.0f;
    _moveDir.x -= IsKeyDown(KEY_D) ? 1.0f : 0.0f;

    return _moveDir;
}

Vector3 Player::WishDir() const
{

    Vector3 forward = Vector3Normalize(PhantomEngine::MatrixMultiplyVector3(player_data.lookRotationMat3, Vector3Multiply({0, 0, 1}, {1, 0, 1})));
    Vector3 right = Vector3Normalize(PhantomEngine::MatrixMultiplyVector3(player_data.lookRotationMat3, Vector3Multiply({1, 0, 0}, {1, 0, 1})));

    Vector3 _wishDir = Vector3Add(Vector3Scale(forward, MoveDir().y), Vector3Scale(right, MoveDir().x));



    return _wishDir;
}

void Player::ProcessJump()
{
    if(WishJump()) player_data.velocity.y = PLAYER_JUMP_SPEED;

}

void Player::ApplyGravity()
{
        player_data.velocity.y -= PLAYER_GRAVITY;
}

void Player::Accelerate(float _wishSpeed, float _acceleration)
{

    const auto fDeltaTime = static_cast<float>(DeltaTime);
    float accelerationSpeed;
    float currentSpeed;
    float addSpeed;

    currentSpeed = Vector3DotProduct(player_data.velocity, WishDir());
    addSpeed = _wishSpeed - currentSpeed;
    if(addSpeed < 0) return;

    accelerationSpeed = _acceleration * _wishSpeed * fDeltaTime;

    if(accelerationSpeed > addSpeed) accelerationSpeed = addSpeed;

    player_data.velocity = Vector3Add(player_data.velocity, Vector3Scale(WishDir(), accelerationSpeed));


}

Vector3 Player::CalculateFriction(const Vector3 &_velocity, float _friction, bool _bDAllowNegatives, double _deltaTime)
{

    const auto fDeltaTime = static_cast<float>(_deltaTime);
    const float velLength = Vector3Length(_velocity);
    const float drop = velLength * _friction * fDeltaTime;

    if (!_bDAllowNegatives)
    {
        return velLength == 0.0f ? Vector3{0, 0, 0}
                                 : Vector3Scale(Vector3Normalize(_velocity), std::max(0.0f, velLength - drop));
    }
    return velLength == 0.0f ? Vector3{0, 0, 0} : Vector3Scale(Vector3Normalize(_velocity), velLength - drop);
}

