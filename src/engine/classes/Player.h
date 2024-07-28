//
// Created by Brandon Friend on 7/26/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "../PhantomEngine.h"


#define PLAYER_MAX_HEALTH 10
#define PLAYER_HEAD_CENTER_OFFSET 0.9f
#define PLAYER_LOOK_SENSITIVITY 0.001f
#define PLAYER_FOV 110
#define PLAYER_VIEWMODEL_FOV 90
#define PLAYER_BOX_SIZE (Vector3){1.2f, 2.2f, 1.2f}
#define PLAYER_BOX_RAD 0.05f
#define PLAYER_SIZE (Vector3){PLAYER_BOX_SIZE.x + PLAYER_BOX_RAD, PLAYER_BOX_SIZE.y + PLAYER_BOX_RAD, PLAYER_BOX_SIZE.z + PLAYER_BOX_RAD}
#define PLAYER_HEAD_SIN_TIME (PI * 5.0f)
#define PLAYER_GRAVITY 220 // 800
#define PLAYER_SPEED 100 // 320
#define PLAYER_GROUND_ACCELERATION 8 // 10
#define PLAYER_GROUND_FRICTION 1 // 6
#define PLAYER_AIR_ACCELERATION 0.6f // 0.7
#define PLAYER_AIR_FRICTION 0.0f // 0
#define PLAYER_JUMP_SPEED 60 // 270
#define PLAYER_MIN_NORMAL_Y 0.25f
#define PLAYER_FALL_DEATH_Y (-TILE_HEIGHT * 1.8f)
#define PLAYER_FALL_DEATH_START_DARKEN (PLAYER_FALL_DEATH_Y * 0.3f)
#define PLAYER_KEY_JUMP KEY_SPACE

class Player : public virtual Husk {

public:


    struct PlayerData {
        Vector3 position;
        Vector3 lookRotationEuler;
        Matrix lookRotationMat3;
        Vector3 lookDir;
        Vector3 rotationalVelocity; //used for calculating rotations from mouse input.
        bool bIsGrounded;
        Vector3 velocity;
        Vector3 lastPosition;
        Vector3 lastVelocity;
        Vector3 inputDir;
    } player_data;


    void Init() override;
    void Start() override;
    void Update(double _deltaTime) override;
    void FixedUpdate(double _deltaTime) override;
    void Render() override;
    auto HandleInput() -> void override;
    void SetIsActive(bool _isActive) override;
    bool GetIsActive() override;
    float settings_sensitivity = 0.04f;

    static Camera camera;

protected:
    void MouseLook(double _deltaTime);
    void CalculateInputs();

};



#endif //PLAYER_H
