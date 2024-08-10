//
// Created by Brandon Friend on 8/7/24.
//

#include <iostream>

#include "PhantomPch.h"
#include "Core/EntryPoint.h"

class FearTheCrow : public Phantom::Application
{
public:
    FearTheCrow()
    {

    }

    ~FearTheCrow()
    {

    }
};

Phantom::Application* Phantom::CreateApplication()
{
    return new FearTheCrow();
}

