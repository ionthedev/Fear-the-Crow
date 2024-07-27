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
    void HandleMovement(float forward, float right, float up) override;

    float walkSpeed = 6.0f;

};



#endif //PLAYER_H
