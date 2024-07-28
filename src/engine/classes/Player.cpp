//
// Created by Brandon Friend on 7/26/24.
//

#include "Player.h"



void Player::Init()
{
    Husk::Init();
}

void Player::MouseLook(double _deltaTime) {

    Vector2 mDelta = GetMouseDelta();
    player_data.rotationalVelocity.y += -mDelta.x * settings_sensitivity * player_data.PLAYER_LOOK_SENSITIVITY;
    player_data.rotationalVelocity.x += -mDelta.y * settings_sensitivity * player_data.PLAYER_LOOK_SENSITIVITY;

    player_data.lookRotationEuler = Vector3Add(player_data.lookRotationEuler, Vector3Scale(player_data.rotationalVelocity, _deltaTime * 4.0f));
    player_data.lookRotationEuler.x = Clamp(player_data.lookRotationEuler.x, -PI * 0.45f, PI * 0.45f);

    player_data.rotationalVelocity = Vector3Scale(player_data.rotationalVelocity, 0.92f);

    player_data.lookRotationMat3 = MatrixRotateXYZ(player_data.lookRotationEuler);
    player_data.lookDir = Vector3Transform((Vector3){0,0,1}, player_data.lookRotationMat3);
}

void Player::CalculateInputs() {
    Vector3 acceleration = { 0 };
    acceleration = IsKeyDown(KEY_W) ? Vector3Add(acceleration, player_data.lookDir) :
              (IsKeyDown(KEY_S) ? Vector3Subtract(acceleration, player_data.lookDir) : acceleration);

    acceleration = IsKeyDown(KEY_A) ? Vector3CrossProduct(player_data.lookDir, (Vector3){0, 1, 0}) :
              (IsKeyDown(KEY_D) ? Vector3CrossProduct(player_data.lookDir, (Vector3){0, 1, 0}) : acceleration);

}


