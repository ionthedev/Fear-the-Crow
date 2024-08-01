//
// Created by Brandon Friend on 7/26/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "../PhantomEngine.h"
#include "../bullet3/src/BulletCollision/CollisionShapes/btCollisionShape.h"


#define PLAYER_MAX_HEALTH 10
#define PLAYER_HEAD_CENTER_OFFSET 3
#define PLAYER_LOOK_SENSITIVITY 0.001f
#define PLAYER_FOV 110
#define PLAYER_VIEWMODEL_FOV 90
#define PLAYER_BOX_SIZE (Vector3){1.2f, 2.2f, 1.2f}
#define PLAYER_BOX_RAD 0.05f
#define PLAYER_SIZE (Vector3){PLAYER_BOX_SIZE.x + PLAYER_BOX_RAD, PLAYER_BOX_SIZE.y + PLAYER_BOX_RAD, PLAYER_BOX_SIZE.z + PLAYER_BOX_RAD}
#define PLAYER_HEAD_SIN_TIME (PI * 5.0f)
#define PLAYER_GRAVITY 1 // 800
#define PLAYER_SPEED 7 // 320
#define PLAYER_GROUND_ACCELERATION 3 // 10
#define PLAYER_GROUND_FRICTION 6 // 6
#define PLAYER_AIR_ACCELERATION 0.6f // 0.7
#define PLAYER_AIR_FRICTION 0.0f // 0
#define PLAYER_JUMP_SPEED 10 // 270
#define PLAYER_MIN_NORMAL_Y 0.25f
#define PLAYER_FALL_DEATH_Y (-TILE_HEIGHT * 1.8f)
#define PLAYER_FALL_DEATH_START_DARKEN (PLAYER_FALL_DEATH_Y * 0.3f)
#define PLAYER_KEY_JUMP KEY_SPACE

class Player : public virtual Husk {

public:


    struct PlayerData
    {
        Vector3 position = Vector3{0.0f,10.0f,0.0f};
        Vector3 lookRotationEuler;
        Matrix lookRotationMat3;
        Vector3 lookDir;
        Vector3 rotationalVelocity; //used for calculating rotations from mouse input.
        bool bIsGrounded = true;
        Vector3 velocity;
        Vector3 lastPosition;
        Vector3 lastVelocity;
        Vector3 inputDir;
    } player_data;


    void Init() override;
    void Start() override;
    void Update(double _deltaTime) override;
    bool WishJump() const;
    void FixedUpdate(double _deltaTime) override;
    void Render() override;
    auto HandleInput() -> void override;
    void SetIsActive(bool _isActive) override;
    bool GetIsActive() override;
    void PrepareCollision();
    Vector3 GetWishDir();
    static Vector2 GetMoveDir();
    float settings_sensitivity = 100.0f;
   // btCollisionObject collider;

    Camera camera;

protected:
    void MouseLook(double _deltaTime);
    void CalculateInputs(double _deltaTime);
    void UpdateCamera();
    static Vector2 MoveDir();
    Vector3 WishDir() const;
    void ProcessJump();
    void ApplyGravity();
    void Accelerate(float _wishSpeed, float _acceleration);
    static Vector3 CalculateFriction(const Vector3& _velocity, float _friction, bool _bDisAllowNegatives, double _deltaTime);
    void ApplyFrictionToVelocity(Vector3 _moveDir, double _deltaTime);
    double DeltaTime;
};



#endif //PLAYER_H