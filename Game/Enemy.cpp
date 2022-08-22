#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 position, Texture2D idleTex, Texture2D runTex, float speed)
{
    texture = idleTex;
    idleTexture = idleTex;
    runTexture = runTex;

    worldPosition = position;

    width = texture.width/maxFrames;
    height = texture.height;

    walkSpeed = speed;
}

void Enemy::Tick(float deltaTime)
{
    SetWorldPositionLastFrame();

    HandleVelocity();
    Move();

    screenPosition = Vector2Subtract(worldPosition, target->GetWorldPositon());

    BaseCharacter::Tick(deltaTime);
}

void Enemy::HandleVelocity()
{
    Vector2 toTarget = Vector2Subtract(target->GetScreenPosition(), screenPosition);
    toTarget = Vector2Normalize(toTarget);
    velocity = Vector2Scale(toTarget, walkSpeed);
}