//
// Created by Brandon Friend on 8/14/24.
//

#ifndef DEMOSCENE_H
#define DEMOSCENE_H
#include "Core/Scene.h"

namespace FTC {

class DemoScene : public Phantom::Scene {
public:
    DemoScene();
    ~DemoScene();
    void Start() override;
    void Update(double deltaTime) override;

    Camera camera = { 0 };
    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };
    Ray ray = { 0 };
    RayCollision collision = { 0 };

    Model mapMesh;

    mutable Shader shader;

};

} // FTC

#endif //DEMOSCENE_H
