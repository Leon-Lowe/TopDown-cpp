#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(Vector2 windowDimensions, int damage, float timeBetweenAttacks);

    Rectangle GetWeaponCollisionRect() {return weaponCollisionRect;}
    bool GetAttacking() {return attacking;}

    virtual void Tick(float deltaTime) override;

private:
    Vector2 GetInput();
    void HandleWeapon();

    Texture2D weaponTexture{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRect{};

    bool attacking = false;
};

#endif