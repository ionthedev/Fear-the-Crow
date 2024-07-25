//
// Created by Brandon Friend on 7/21/24.
//

#ifndef ENGINE_LOOP_H
#define ENGINE_LOOP_H

#include "raylib.h"
#include "Game.h"
#include <iostream>
#include <chrono>

class Game;

#pragma region imgui
#include "imgui.h"
#include "rlImGui.h"
#include "imguiThemes.h"
#pragma endregion

class PE_Core {

    //Constructor and Desconstructor
public:
    PE_Core() = default;
    PE_Core(bool initialized);
    void SetGame(Game* _game);
    void Loop();

    double GetDeltaTime() const;
    double GetFixedDeltaTime() const;
    double targetFrameRate = 60;

protected:
    double deltaTime;
    double tAccumulator;
    Game* game;

private:
    bool engine_running;
    mutable std::chrono::steady_clock::time_point currentDeltaFrameTime;
    mutable std::chrono::steady_clock::time_point currentFixedFrameTime;




};



#endif //ENGINE_LOOP_H
