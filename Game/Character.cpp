#include "Character.h"
#include "raymath.h"

Character::Character(Vector2 windowDimensions, int damage, float timeBetweenAttacks)
{
    screenPosition = {
        (windowDimensions.x/2.0f) - scale * (0.5f * width),
        (windowDimensions.y/2.0f) - scale * (0.5f * height)
    };

    width = texture.width/maxFrames;
    height = texture.height;

    SetAttackDamage(damage);
    SetTimeBetweenAttacks(timeBetweenAttacks);
}

void Character::Tick(float deltaTime)
{
    if(!GetAlive()) {return;}

    SetWorldPositionLastFrame();

    velocity = GetInput();
    Move();

    BaseCharacter::Tick(deltaTime);

    HandleWeapon();
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

void Character::HandleWeapon()
{
    Vector2 origin{};
    Vector2 offset{};
    float rotation = 0.0f;

    if(attackTimer >= GetTimeBetweenAttacks())
    {
        attacking = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        attackTimer = 0.0f;
    }
    else
    {
        attacking = false;
    }

    if(rightLeft > 0.0f)
    {
        origin = {0.0f, weaponTexture.height * scale};
        offset = {35.0f, 55.0f};
        attacking ? rotation = 35.0f : rotation = 0.0f;

        weaponCollisionRect = {
            screenPosition.x + offset.x,
            screenPosition.y + offset.y - weaponTexture.height * scale,
            weaponTexture.width * scale,
            weaponTexture.height * scale
        };
    }
    else
    {
        origin = {weaponTexture.width * scale, weaponTexture.height * scale};
        offset = {25.0f, 55.0f};
        attacking ? rotation = -35.0f : rotation = 0.0f;

        weaponCollisionRect = {
            screenPosition.x + offset.x - weaponTexture.height * scale,
            screenPosition.y + offset.y - weaponTexture.height * scale,
            weaponTexture.width * scale,
            weaponTexture.height * scale
        };
    }

    Rectangle source{0.0f, 0.0f, static_cast<float>(weaponTexture.width) * rightLeft, static_cast<float>(weaponTexture.height)};
    Rectangle dest{screenPosition.x + offset.x, screenPosition.y + offset.y, weaponTexture.width * scale, weaponTexture.height * scale};
    DrawTexturePro(weaponTexture, source, dest, origin, rotation, WHITE);
}