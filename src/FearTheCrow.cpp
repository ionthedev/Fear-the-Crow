//
// Created by Brandon Friend on 7/21/24.
//

#include "FearTheCrow.h"


FearTheCrow::FearTheCrow(bool _initialized)
{
    initialized = _initialized;
    //Initializes the engine and triggers the loop
    engine = PE_Core(true);

    engine.SetGame(this);

    player = Player();
    engine.Loop();
}

FearTheCrow::~FearTheCrow() = default;

void FearTheCrow::DrawWindow() const
{
    InitWindow(screenWidth, screenHeight, "Phantom Engine - Window");
    SetTargetFPS(engine.targetFrameRate);
}

void FearTheCrow::Start() const
{
    DrawWindow();


    // Generates some random columns

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 12);
        positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), heights[i]/2.0f, (float)GetRandomValue(-15, 15) };
        colors[i] = (Color){ 50, 32, 30, 255 };
    }

    DisableCursor();                    // Limit cursor to relative movement inside the window



}

void FearTheCrow::Update(double _deltaTime) const
{

    player.Update(_deltaTime);
}

void FearTheCrow::FixedUpdate(double _deltaTime) const
{
    player.FixedUpdate(_deltaTime);
}

void FearTheCrow::Render() const
{
    ClearBackground(RAYWHITE);
      BeginMode3D(player.camera);

                DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
                DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
                DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
                DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall

                // Draw some cubes around
                for (int i = 0; i < MAX_COLUMNS; i++)
                {
                    DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
                    DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
                }

                // Draw player cube
                if (cameraMode == CAMERA_THIRD_PERSON)
                {
                    DrawCube(player.camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
                    DrawCubeWires(player.camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
                }

            EndMode3D();

            // Draw info boxes

}

void FearTheCrow::HandleInput() const
{
    Game::HandleInput();
    player.HandleInput();
}
