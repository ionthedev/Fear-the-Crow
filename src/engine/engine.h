//
// Created by Brandon Friend on 7/21/24.
//

#ifndef ENGINE_LOOP_H
#define ENGINE_LOOP_H

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "../libraries/raygui.h"
#include "../game.h"

class engine {

    //Constructor and Desconstructor
public:
    engine(const engine&) = default;
    engine& operator=(const engine&) = default;
    void Start() const;
    void Update() const;
    void FixedUpdate(double ) const;
    void PhysicsUpdate() const;
    void Render() const;
    void HandleInput() const;
    bool IsRunning() const;
    double GetDeltaTime() const;
    double GetPhysicsDeltaTime() const;
    float FGetDeltaTime() const;
    float FGetPhysicsDeltaTime() const;

private:
    bool running;
    double deltaTime();
    double physicsDeltaTime();



};



#endif //ENGINE_LOOP_H
