#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 position, Texture2D idleTex, Texture2D runTex, float speed, int health, int damage, float timeBetweenAttacks)
{
    texture = idleTex;
    idleTexture = idleTex;
    runTexture = runTex;

    worldPosition = position;

    width = texture.width/maxFrames;
    height = texture.height;

    walkSpeed = speed;

    SetAttackDamage(damage);
    SetHealth(health);

    SetTimeBetweenAttacks(timeBetweenAttacks);
}

void Enemy::Tick(float deltaTime)
{
    if(!GetAlive()) {return;}

    attackTimer += deltaTime;

    SetWorldPositionLastFrame();

    HandleVelocity();
    Move();

    screenPosition = Vector2Subtract(worldPosition, target->GetWorldPositon());

    if(CheckCollisionRecs(target->GetCollisionRectangle(), GetCollisionRectangle()))
    {
        if(attackTimer >= GetTimeBetweenAttacks())
        {
            target->Damage(GetAttackDamage());
            attackTimer = 0.0f;
        }
    }

    BaseCharacter::Tick(deltaTime);
}

void Enemy::HandleVelocity()
{
    Vector2 toTarget = Vector2Subtract(target->GetScreenPosition(), screenPosition);

    if(Vector2Length(toTarget) < radius) {toTarget = {};}

    toTarget = Vector2Normalize(toTarget);
    velocity = Vector2Scale(toTarget, walkSpeed);
}