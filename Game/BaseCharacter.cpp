#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::Tick(float deltaTime)
{
    Animate(deltaTime);
    Draw();

    attackTimer += deltaTime;
}

void BaseCharacter::Move()
{
    if(Vector2Length(velocity) != 0.0)
    {
        worldPosition = Vector2Add(worldPosition, Vector2Scale(Vector2Normalize(velocity), sprinting ? sprintSpeed : walkSpeed));
        velocity.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
        texture = runTexture;
    }
    else
    {
        texture = idleTexture;
    }
}

void BaseCharacter::Animate(float deltaTime)
{
    runningTime += deltaTime;
    if(runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if(frame > maxFrames) {frame = 0;}
    }
}

void BaseCharacter::Draw()
{
    Rectangle playerSource{width * frame, 0.0f, rightLeft * width, height};
    Rectangle playerDest{screenPosition.x, screenPosition.y, scale * width, scale * height};
    Vector2 origin{width/2.0f, height/2.0f};
    DrawTexturePro(texture, playerSource, playerDest, origin, 0.0f, WHITE);
}

void BaseCharacter::UndoMovement()
{
    worldPosition = worldPositionLastFrame;
}

Rectangle BaseCharacter::GetCollisionRectangle()
{
    return Rectangle{
        screenPosition.x,
        screenPosition.y,
        width * scale,
        height * scale
    };
}