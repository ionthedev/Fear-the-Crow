//
// Created by Brandon Friend on 7/21/24.
//

#include "engine_core.h"


engine_core::engine_core(bool initialized): deltaTime(0), tLastUpdate(0), tAccumulator(0)
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
        Update(tickStep); //TODO: Make this use the Game Class
        tAccumulator -= tSlice;
    }
}

void engine_core::Start() const
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Phantom Engine - Window");


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

#pragma region imgui
    rlImGuiSetup(true);

    //you can use whatever imgui theme you like!
    ImGui::StyleColorsDark();
    //imguiThemes::yellow();
    //imguiThemes::gray();
    //imguiThemes::green();
    //imguiThemes::red();
    imguiThemes::embraceTheDarkness();


    ImGuiIO &io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.FontGlobalScale = 2;

    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        //style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 0.5f;
        //style.Colors[ImGuiCol_DockingEmptyBg].w = 0.f;
    }
}

void engine_core::Update(double _deltaTime) const
{

}

void engine_core::Render() const
{

    ClearBackground(RAYWHITE);


#pragma region imgui
    rlImGuiBegin();

    ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
    ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    ImGui::PopStyleColor(2);
#pragma endregion


    ImGui::Begin("Test");

    ImGui::Text("Hello");
    ImGui::Button("Cummy");
    ImGui::Button("Squirty");

    ImGui::End();


    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);


#pragma region imgui
    rlImGuiEnd();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
#pragma endregion

}
