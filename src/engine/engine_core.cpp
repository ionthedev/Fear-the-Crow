//
// Created by Brandon Friend on 7/21/24.
//

#include "engine_core.h"


engine_core::engine_core(bool initialized)
{
    running = initialized;
}

void engine_core::Loop()
{
    auto now = std::chrono::steady_clock::now(); // Get the current time
    double tNow = std::chrono::duration<double>(now.time_since_epoch()).count();
    deltaTime = tNow - tLastUpdate;
    tLastUpdate += deltaTime;
    tAccumulator += deltaTime;
    while(tAccumulator > tSlice)
    {
        Update(tickStep);
        tAccumulator -= tSlice;
    }
}

void engine_core::Start() const
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Phantom Engine - Window");


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
}

void engine_core::Update(double _deltaTime) const
{

}

void engine_core::Render() const
{
    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, SKYBLUE);
}
