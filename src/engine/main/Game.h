//
// Created by Brandon Friend on 7/24/24.
//

#ifndef GAME_H
#define GAME_H


#include "PE_Core.h"

class PE_Core;


class Game {

public:
    Game();

    ~Game()
    {
    }

    virtual void Start() const;
    virtual void Update(double _deltaTime) const;
    virtual void FixedUpdate(double _deltaTime) const;
    virtual void Render() const;
    virtual void HandleInput() const;

    const int screenWidth = 800;
    const int screenHeight = 450;




};


#endif //GAME_H
