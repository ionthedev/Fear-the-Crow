//
// Created by Brandon Friend on 7/21/24.
//

#include "PE_Core.h"


PE_Core::PE_Core(bool initialized)
{
    engine_running = initialized;

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
    static auto tLastUpdate = std::chrono::steady_clock::now();;

    currentDeltaFrameTime = std::chrono::steady_clock::now();

    double delta = std::chrono::duration<double>(currentDeltaFrameTime - tLastUpdate).count();
    tLastUpdate = currentDeltaFrameTime;

    return delta;
}

double PE_Core::GetFixedDeltaTime() const
{
    return 1 / targetFrameRate;
}
