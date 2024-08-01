//
// Created by Brandon Friend on 7/21/24.
//

#ifndef FEARTHECROW_H
#define FEARTHECROW_H

#include "../engine/classes/Player.h"
#include "../engine/Core/PE_Core.h"
#include "../engine/Core/Game.h"


#define MAX_COLUMNS 20
class FearTheCrow : public Game {

public:

    typedef struct
    {
        Model *model = nullptr;
        Vector3 *position = nullptr;
        //Collider *collider[100];
    } worldObject;

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




protected:
    PE_Core engine;
    mutable int cameraMode = CAMERA_FIRST_PERSON;
    mutable float heights[MAX_COLUMNS] = { 0 };
    mutable Vector3 positions[MAX_COLUMNS] = { 0 };
    mutable Color colors[MAX_COLUMNS] = { 0 };
    mutable Mesh meshes[MAX_COLUMNS] = { 0 };
    mutable Player player;
    mutable worldObject ramp;
    mutable Shader shader;
    mutable Material material;
    mutable Vector3 normal = {0}; //Init the normal value
    mutable worldObject level;
    mutable Model skybox;

    private:
    bool initialized;

};



#endif //FEARTHECROW_H
