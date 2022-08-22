#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(Vector2 windowDimensions);

    virtual void Tick(float deltaTime) override;

private:
    Vector2 GetInput();
};

#endif