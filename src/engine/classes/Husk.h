//
// Created by Brandon Friend on 7/21/24.
//

#ifndef HUSK_H
#define HUSK_H
#include "../PhantomEngine.h"

class Husk : public Artifact {

public:

    void Init() override;
    void Start() override;
    void Update(double _deltaTime) override;
    void FixedUpdate(double _deltaTime) override;
    void Render() override;
    auto HandleInput() -> void override;
    void SetIsActive(bool _isActive) override;
    bool GetIsActive() override;

protected:
    virtual void HandleMovement(float forward, float right, float up);


};



#endif //HUSK_H
