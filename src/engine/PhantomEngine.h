//
// Created by Brandon Friend on 7/25/24.
//

#ifndef PHANTOMENGINE_H
#define PHANTOMENGINE_H

#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"
#include "rlImGui.h"
#include "imgui.h"
#include "main/PE_Core.h"
#include "main/Game.h"
#include "classes/Artifact.h"
#include "classes/Husk.h"

class PhanthomEngine
{
    public:
    static float m_Clip(float n, float lower, float upper)
    {
        return std::max(lower, std::min(n, upper));
    }
};

#endif //PHANTOMENGINE_H
