//
// Created by Brandon Friend on 8/14/24.
//

#include "DemoScene.h"

#include "Core/Object.h"

namespace FTC {
    DemoScene::DemoScene()
    {


    }

    DemoScene::~DemoScene()
    {
    }

    void DemoScene::Start() {
        // Initialize Camera
        camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
        camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
        camera.fovy = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;

        shader = LoadShader(TextFormat("resources/Shaders/shader.vs", 330),
                               TextFormat("resources/Shaders/shader.fs", 330));

        mapMesh = LoadPMD("resources/Mesh/Demo.pmd");
        if (mapMesh.meshCount == 0) {
            TraceLog(LOG_ERROR, "Failed to load model!");
            return;
        }
        mapMesh.materials[0].shader = shader;
        mapMesh.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = BLUE;
        // Additional debug information
        TraceLog(LOG_INFO, "mapMesh: vertex count = %i", mapMesh.meshes[0].vertexCount);
        TraceLog(LOG_INFO, "mapMesh: material count = %i", mapMesh.materialCount);
    }



    void DemoScene::Update(double _deltaTime)
    {
         // Update
        //----------------------------------------------------------------------------------
        if (IsCursorHidden()) UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Toggle camera controls
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            if (IsCursorHidden()) EnableCursor();
            else DisableCursor();
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!collision.hit)
            {
                ray = GetScreenToWorldRay(GetMousePosition(), camera);

                // Check collision between ray and box
                collision = GetRayCollisionBox(ray,
                            (BoundingBox){(Vector3){ cubePosition.x - cubeSize.x/2, cubePosition.y - cubeSize.y/2, cubePosition.z - cubeSize.z/2 },
                                          (Vector3){ cubePosition.x + cubeSize.x/2, cubePosition.y + cubeSize.y/2, cubePosition.z + cubeSize.z/2 }});
            }
            else collision.hit = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                if (collision.hit)
                {
                    DrawModel(mapMesh, {0,0,0}, 1.0f, WHITE);
                    //DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, RED);
                    DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, MAROON);

                    DrawCubeWires(cubePosition, cubeSize.x + 0.2f, cubeSize.y + 0.2f, cubeSize.z + 0.2f, GREEN);
                }
                else
                {
                    DrawModel(mapMesh, cubePosition, 1.0f, WHITE);
                    //DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, GRAY);
                    DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, DARKGRAY);
                }

                DrawRay(ray, MAROON);
                DrawGrid(10, 1.0f);

            EndMode3D();




            DrawText("Try clicking on the box with your mouse!", 240, 10, 20, DARKGRAY);

            if (collision.hit) DrawText("BOX SELECTED", (800 - MeasureText("BOX SELECTED", 30)) / 2, (int)(500 * 0.1f), 30, GREEN);

            DrawText("Right click mouse to toggle camera controls", 10, 430, 10, GRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
} // FTC