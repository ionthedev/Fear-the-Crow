//
// Created by Brandon Friend on 7/21/24.
//

#ifndef FEARTHECROW_H
#define FEARTHECROW_H

#include "engine/classes/Player.h"
#include "engine/main/PE_Core.h"
#include "engine/main/Game.h"


#define MAX_COLUMNS 20
class FearTheCrow : public Game {

public:
    FearTheCrow() = default;
    FearTheCrow(bool _initialized);
    ~FearTheCrow();
    void DrawWindow() const;
    void ConfigureImGui() const;
    void Start() const override;
    void Update(double _deltaTime) const override;
    void FixedUpdate(double _deltaTime) const override;
    void Render() const override;
    void HandleInput() const override;

    mutable Camera camera;



protected:
    PE_Core engine;
    mutable int cameraMode = CAMERA_FIRST_PERSON;
    mutable float heights[MAX_COLUMNS] = { 0 };
    mutable Vector3 positions[MAX_COLUMNS] = { 0 };
    mutable Color colors[MAX_COLUMNS] = { 0 };
    mutable Player player;

    private:
    bool initialized;

};



#endif //FEARTHECROW_H
