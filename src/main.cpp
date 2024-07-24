
#include "raylib.h"
#include "rcamera.h"

#include "engine/engine_core.h"

#define MAX_COLUMNS 20

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    engine_core engine = engine_core(true);
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    const double deltaTime = 0;

    InitWindow(screenWidth, screenHeight, "Phantom Engine - Window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        engine.Loop();
        BeginDrawing();
        engine.Render();
        //Middle Process
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}