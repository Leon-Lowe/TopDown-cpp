#include "Character.h"
#include "raymath.h"

Character::Character(Vector2 windowDimensions)
{
    screenPosition = {
        (windowDimensions.x/2.0f) - scale * (0.5f * width),
        (windowDimensions.y/2.0f) - scale * (0.5f * height)
    };

    width = texture.width/maxFrames;
    height = texture.height;
}

void Character::Tick(float deltaTime)
{
    SetWorldPositionLastFrame();

    velocity = GetInput();
    Move();
    
    BaseCharacter::Tick(deltaTime);
}

Vector2 Character::GetInput()
{
    Vector2 dir{};
    if(IsKeyDown(KEY_A)) {dir.x -= 1.0;}
    if(IsKeyDown(KEY_D)) {dir.x += 1.0;}
    if(IsKeyDown(KEY_W)) {dir.y -= 1.0;}
    if(IsKeyDown(KEY_S)) {dir.y += 1.0;}

    if(IsKeyDown(KEY_LEFT_SHIFT)) {sprinting = true;}
    if(!IsKeyDown(KEY_LEFT_SHIFT)) {sprinting = false;}

    return dir;
}