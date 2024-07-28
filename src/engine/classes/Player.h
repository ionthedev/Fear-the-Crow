//
// Created by Brandon Friend on 7/26/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "../PhantomEngine.h"




class Player : public virtual Husk {

public:


    void Init() override;
    void Start() override;
    void Update(double _deltaTime) override;
    void FixedUpdate(double _deltaTime) override;
    void Render() override;
    auto HandleInput() -> void override;
    void SetIsActive(bool _isActive) override;
    bool GetIsActive() override;
    static Camera& GetPlayerCamera();

    static Camera camera;

protected:
    void HandleMovement() override;
    void CalculateMovement(double _deltaTime);
    float deltaTime;
    float MAX_SPEED = 3.0f;
    float CURR_SPEED = 5.0f;
    float MAX_ACCEL = 10.0f * MAX_SPEED;
    float GROUND_FRICTION = 6.0f;

    Vector3 Friction(Vector3 _velocity, float _deltaTime);
    Vector3 wishDir();

    Vector3 CalculateGroundVelocity(Vector3 _wishDir, Vector3 _velocity, float _deltaTime);
    void SetCameraRotation();

    Vector3 inputDir();
    Vector3 velocity;

    Vector3 position = { 0, 1, 0};
    Vector3 rotation;

};



#endif //PLAYER_H
