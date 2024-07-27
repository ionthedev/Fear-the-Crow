//
// Created by Brandon Friend on 7/25/24.
//

#ifndef ARTIFACT_H
#define ARTIFACT_H
#include "../main/PE_Core.h"
#include "../main/Game.h"


class Artifact {

public:
    Artifact();
    virtual ~Artifact();

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



#endif //ARTIFACT_H
