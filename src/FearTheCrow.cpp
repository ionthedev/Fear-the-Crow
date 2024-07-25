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
    engine.Loop();
}

FearTheCrow::~FearTheCrow() = default;

void FearTheCrow::DrawWindow() const
{
    InitWindow(screenWidth, screenHeight, "Phantom Engine - Window");
    SetTargetFPS(engine.targetFrameRate);
}

void FearTheCrow::ConfigureImGui() const
{
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
    #pragma endregion imgui
}

void FearTheCrow::Start() const
{
    DrawWindow();
    ConfigureImGui();
}

void FearTheCrow::Update(double _deltaTime) const
{
}

void FearTheCrow::FixedUpdate(double _deltaTime) const
{
}

void FearTheCrow::Render() const
{
    Game::Render();

    ClearBackground(RAYWHITE); // Clear the background to white (or any other color)
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    #pragma region imgui
        rlImGuiBegin();

        ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ImGui::PopStyleColor(2);

        ImGui::Begin("Update");
        ImGui::Text("Hello");

        ImGui::Text(std::to_string(engine.GetDeltaTime()).c_str());
        ImGui::Button("Button 1");
        ImGui::Button("Button 2");

        ImGui::End();

        ImGui::Begin("Fixed Update");
        ImGui::Text(std::to_string(engine.GetFixedDeltaTime()).c_str());

        ImGui::End();

        rlImGuiEnd();
        ImGuiIO &io = ImGui::GetIO(); (void)io;
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    #pragma endregion
}

void FearTheCrow::HandleInput() const
{
    Game::HandleInput();
}
