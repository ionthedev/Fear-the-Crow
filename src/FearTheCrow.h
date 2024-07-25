//
// Created by Brandon Friend on 7/21/24.
//

#ifndef FEARTHECROW_H
#define FEARTHECROW_H

#include "engine/main/PE_Core.h"
#include "engine/main/Game.h"


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
protected:
    PE_Core engine;

    private:
    bool initialized;

};



#endif //FEARTHECROW_H
