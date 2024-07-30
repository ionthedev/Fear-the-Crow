//
// Created by Brandon Friend on 7/25/24.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "../main/PE_Core.h"
#include "../main/Game.h"


class GameObject {

public:
    GameObject();
    virtual ~GameObject();

    virtual void Init();
    virtual void Start();
    virtual void Update(double _deltaTime);
    virtual void FixedUpdate(double _deltaTime);
    virtual void Render();
    virtual void HandleInput();
    virtual bool GetIsActive();
    virtual void SetIsActive(bool _isActive);

private:
    bool m_isActive{};


};



#endif //GAMEOBJECT_H
