//
// Created by Brandon Friend on 7/21/24.
//

#include "PE_Core.h"


PE_Core::PE_Core(bool initialized)
{
    engine_running = initialized;
    currentDeltaFrameTime = std::chrono::steady_clock::now(); // Get the current time
    currentFixedFrameTime = std::chrono::steady_clock::now(); // Get the current time

}

void PE_Core::SetGame(Game* _game)
{
    game = _game;
}

/*-------------------------------------------------------------------------------------
 *      Core Engine Loop
 *          - This is where everything for the game runs.
 *            DeltaTime and FixedDelta Time are calculated and called from here.
 *------------------------------------------------------------------------------------*/

void PE_Core::Loop()
{

    game->Start();
    while (!WindowShouldClose())
    {
        double deltaTime = GetDeltaTime();

        // Fixed update loop to handle fixed time steps


        game->Update(deltaTime);

        tAccumulator += deltaTime;
        while (tAccumulator >= GetFixedDeltaTime())
        {
            game->FixedUpdate(GetFixedDeltaTime());
            tAccumulator -= GetFixedDeltaTime();
        }
        BeginDrawing();

        game->Render(); // Make sure your game has a Draw() function to handle rendering
        EndDrawing();
    }

    // De-Initialization and Kill Process
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}


double PE_Core::GetDeltaTime() const
{
    auto tLastUpdate = currentDeltaFrameTime;

    currentDeltaFrameTime = std::chrono::steady_clock::now();

    const std::chrono::duration<float> frameTime = currentDeltaFrameTime - tLastUpdate;
    return frameTime.count();
}

double PE_Core::GetFixedDeltaTime() const
{
    return 1 / targetFrameRate;
}
