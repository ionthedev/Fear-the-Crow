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
#include <chrono>

class engine_core {

    //Constructor and Desconstructor
public:
    engine_core() = default;
    engine_core(bool initialized);

    void Loop();
    void Start() const;
    void Update(double _deltaTime) const;
    void Render() const;
    void HandleInput() const;
    bool IsRunning() const;

protected:

    double deltaTime;
    double tLastUpdate;
    double tAccumulator;
    double tSlice = 0.016; // 60 FPS (1/60 seconds)

private:
    bool running;
    std::chrono::steady_clock::time_point currentFrameTime;
    static constexpr double tickStep = 0.016; // 60 FPS (1/60 seconds)




};



#endif //ENGINE_LOOP_H
