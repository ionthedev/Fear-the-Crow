
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
int main(void)
{
    engine_core engine = engine_core(true);
    // Initialization
    //--------------------------------------------------------------------------------------
    engine.Start();
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        engine.Loop();
        BeginDrawing();
        engine.Render();
        EndDrawing();
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}