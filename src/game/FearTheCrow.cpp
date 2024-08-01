//
// Created by Brandon Friend on 7/21/24.
//

#include "FearTheCrow.h"
#include "rlgl.h"

#define GLSL_VERSION  330

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

    Mesh cube = GenMeshCube(1.0f, 1.0f, 1.0f);
    skybox = LoadModelFromMesh(cube);
    skybox.materials[0].shader = LoadShader(TextFormat("../resources/Shaders/skybox.vs", GLSL_VERSION),
                                            TextFormat("../resources/Shaders/skybox.fs", GLSL_VERSION));
    SetShaderValue(skybox.materials[0].shader, GetShaderLocation(skybox.materials[0].shader, "environmentMap"), (int[1]){ MATERIAL_MAP_CUBEMAP }, SHADER_UNIFORM_INT);
    SetShaderValue(skybox.materials[0].shader, GetShaderLocation(skybox.materials[0].shader, "doGamma"), (int[1]) { false ? 1 : 0 }, SHADER_UNIFORM_INT);
    SetShaderValue(skybox.materials[0].shader, GetShaderLocation(skybox.materials[0].shader, "vflipped"), (int[1]){ false ? 1 : 0 }, SHADER_UNIFORM_INT);

    Shader shdrCubemap = LoadShader(TextFormat("../resources/Shaders/cubemap.vs", GLSL_VERSION),
                                    TextFormat("../resources/Shaders/cubemap.fs", GLSL_VERSION));

    SetShaderValue(shdrCubemap, GetShaderLocation(shdrCubemap, "equirectangularMap"), (int[1]){ 0 }, SHADER_UNIFORM_INT);
    char skyboxFileName[256] = { 0 };
    Image img = LoadImage("../resources/Textures/skybox.png");
    skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);    // CUBEMAP_LAYOUT_PANORAMA
    UnloadImage(img);

    shader = LoadShader(TextFormat("../resources/Shaders/shader.vs", GLSL_VERSION),
                               TextFormat("../resources/Shaders/shader.fs", GLSL_VERSION));

    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    //ramp.collider[0] = new Collider();
    ramp.model = new Model(LoadModel("../resources/Mesh/sm_ramp.gltf"));
    ramp.model->materials[0].shader = shader;
    ramp.model->materials[0].maps[MATERIAL_MAP_DIFFUSE].color = BLUE;

    ramp.position = new Vector3{4,0,4};


    level.model = new Model(LoadModel("../resources/Mesh/test_level.gltf"));
    level.model->materials[0].shader = shader;
    level.model->materials[0].maps[MATERIAL_MAP_DIFFUSE].color = BLUE;

    level.position = new Vector3{0,0,0};

    //SetupColliderMesh(&player.collider, GenMeshCylinder(0.4f,2,6));

    //SetupColliderMesh(ramp.collider[0],ramp.model->meshes[0]);

    /*for (int i = 0; i < level.model->meshCount; i++)
    {
        level.collider[i] = new Collider();
        SetupColliderMesh(level.collider[i],level.model->meshes[i]);

        UpdateCollider(*level.position,level.collider[i]);
    }*/

    //UpdateCollider(*ramp.position,ramp.collider[0]);
    // Generates some random columns

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 12);
        positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), heights[i]/2.0f, (float)GetRandomValue(-15, 15) };
        colors[i] = (Color){ 50, 32, 30, 255 };
        meshes[i] = GenMeshCube(2.0f, heights[i], 2.0f);
    }

    DisableCursor();                    // Limit cursor to relative movement inside the window



}

void FearTheCrow::Update(double _deltaTime) const
{


    player.Update(_deltaTime);
}

void FearTheCrow::FixedUpdate(double _deltaTime) const
{

    Vector3 originalVelocity = player.player_data.velocity;

    /*if (CheckCollision(player.collider, *ramp.collider[0], &normal)) {
        // Calculate the projection of the velocity on the collision normal
        Vector3 projection = Vector3Scale(normal, Vector3DotProduct(originalVelocity, normal));

        // Adjust the player's velocity by subtracting the projection
        player.player_data.velocity = Vector3Subtract(originalVelocity, projection);

        // Ensure that the player is not penetrating the collider
        // Calculate penetration depth
        Vector3 closestPointOnRamp = GetClosestPointOnCollider(*ramp.collider[0], player.player_data.position, ramp.model->meshes[0]);
        Vector3 toPlayer = Vector3Subtract(player.player_data.position, closestPointOnRamp);
        float penetrationDepth = Vector3DotProduct(toPlayer, normal);

        if (penetrationDepth < 0) {
            Vector3 correction = Vector3Scale(normal, -penetrationDepth);
            player.player_data.position = Vector3Add(player.player_data.position, correction);
        }
    }
    for (int i = 0; i < level.model->meshCount; i++)
    {
    if (CheckCollision(player.collider, *level.collider[i], &normal)) {
        // Calculate the projection of the velocity on the collision normal
        Vector3 projection = Vector3Scale(normal, Vector3DotProduct(originalVelocity, normal));

        // Adjust the player's velocity by subtracting the projection
        player.player_data.velocity = Vector3Subtract(originalVelocity, projection);

        // Ensure that the player is not penetrating the collider
        // Calculate penetration depth

            Vector3 closestPointOnMesh = GetClosestPointOnCollider(*level.collider[i], player.player_data.position, level.model->meshes[i]);
            Vector3 toPlayer = Vector3Subtract(player.player_data.position, closestPointOnMesh);
            float penetrationDepth = Vector3DotProduct(toPlayer, normal);

            if (penetrationDepth < 0) {
                Vector3 correction = Vector3Scale(normal, -penetrationDepth);
                player.player_data.position = Vector3Add(player.player_data.position, correction);
            }
        }

    }*/

    // Update the collider position to reflect the player's new position
   // UpdateCollider(player.player_data.position, &player.collider);

    // Move the player based on the adjusted velocity
    player.player_data.position = Vector3Add(player.player_data.position, Vector3Scale(player.player_data.velocity, _deltaTime));

    // Call the player's FixedUpdate function to handle additional updates
    player.FixedUpdate(_deltaTime);
}

void FearTheCrow::Render() const
{

    ClearBackground(RAYWHITE);
      BeginMode3D(player.camera);
                rlDisableBackfaceCulling();
                rlDisableDepthMask();
                DrawModel(skybox, (Vector3){0, 0, 0}, 0.0f, WHITE);
                rlEnableBackfaceCulling();
                rlEnableDepthMask();
                DrawModel(*ramp.model, *ramp.position, 1.0f, WHITE);
                DrawModel(*level.model, {0,0,0}, 1.0f, WHITE);


                // Draw player cube
                if (cameraMode == CAMERA_THIRD_PERSON)
                {
                    DrawCube(player.camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
                    DrawCubeWires(player.camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
                }

            EndMode3D();

            // Draw info boxes

            DrawRectangle(5, 5, 225, 65, Fade(MAROON, 0.5f));
            DrawRectangleLines(5, 5, 225, 65, BLACK);

            std::string p_position = std::string("Position: ") + PhantomEngine::Vector3ToChar(player.player_data.position);
            DrawText(p_position.c_str() , 15, 15, 10, BLACK);

            std::string p_velocity = std::string("Velocity: ") + PhantomEngine::Vector3ToChar(player.player_data.velocity);
            DrawText(p_velocity.c_str() , 15, 25, 10, BLACK);

            std::string p_wishDir = std::string("WishDir: ") + PhantomEngine::Vector3ToChar(player.GetWishDir());
            DrawText(p_wishDir.c_str() , 15, 35, 10, BLACK);

            std::string p_moveDir = std::string("InputDir: ") + PhantomEngine::Vector2ToChar(player.GetMoveDir());
            DrawText(p_moveDir.c_str() , 15, 45, 10, BLACK);

            std::string p_lookDir = std::string("LookDir: ") + PhantomEngine::Vector3ToChar(player.player_data.lookDir);
            DrawText(p_lookDir.c_str() , 15, 55, 10, BLACK);


}

void FearTheCrow::HandleInput() const
{
    Game::HandleInput();
    player.HandleInput();
}
