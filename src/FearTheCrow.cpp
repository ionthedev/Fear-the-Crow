//
// Created by Brandon Friend on 8/7/24.
//

#include <iostream>

#include "DemoScene.h"
#include "PhantomPch.h"
#include "Components/Transform2D.h"
#include "Core/Engine.h"
#include "Core/EntryPoint.h"
#include "Core/Scene.h"

class FearTheCrow : public Phantom::Application
{
public:
    FearTheCrow()
    {

        PH_INFO("Initialized");
        //Initializes the engine and triggers the loop

        Phantom::Engine* engine = Phantom::Engine::GetSingleton(true);

        engine->SetApp(this);
        engine->Loop();
    }

    ~FearTheCrow()
    {
        Phantom::Engine* engine = Phantom::Engine::GetSingleton(true);
        engine->Shutdown();
    }

    void Start() const override;
    void Update(double _deltaTime) const override;
    void FixedUpdate(double _deltaTime) const override;


    FTC::DemoScene *activeScene = new FTC::DemoScene();

};

void FearTheCrow::Start() const
{
    Application::Start();

    activeScene->Start();
    InitWindow(800, 500, "Fear The Crow");
    SetTargetFPS(60);



}

void FearTheCrow::Update(double _deltaTime) const
{
    if(WindowShouldClose()) delete this;
    activeScene->Update(_deltaTime);
}

void FearTheCrow::FixedUpdate(double _deltaTime) const
{
    Application::FixedUpdate(_deltaTime);
}

Phantom::Application* Phantom::CreateApplication()
{
    return new FearTheCrow();
}

