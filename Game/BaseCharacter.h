#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();

    Vector2 GetWorldPositon() {return worldPosition;}
    Vector2 GetScreenPosition() {return screenPosition;}

    Texture2D GetTexture() {return texture;}
    Texture2D GetIdleTexture() {return idleTexture;}
    Texture2D GetRunTexture() {return runTexture;}

    int GetRightLeft() {return rightLeft;}
    int GetFrame() {return frame;}
    int GetMaxFrames() {return maxFrames;}
    float GetRunningTime() {return runningTime;}
    float GetUpdateTime() {return updateTime;}

    bool GetAlive() {return alive;}
    void SetAlive(bool isAlive) {alive = isAlive;}

    int GetHealth() {return health;}
    void SetHealth(int newHealth) {health = newHealth;}
    void Damage(int damageAmount) {health -= damageAmount; CheckForDead();}
    void Heal(int healAmount) {health += healAmount;}

    void CheckForDead() {if(health <= 0) {alive = false;}}

    int GetAttackDamage() {return attackDamage;}
    void SetAttackDamage(int damage) {attackDamage = damage;}

    float GetTimeBetweenAttacks() {return timeBetweenAttacks;}
    void SetTimeBetweenAttacks(float time) {timeBetweenAttacks = time;}

    Rectangle GetCollisionRectangle();
    
    virtual void Tick(float deltaTime);
    void UndoMovement();
protected:
    void Move();
    void Animate(float deltaTime);
    void Draw();
    void SetWorldPositionLastFrame() {worldPositionLastFrame = worldPosition;}

    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idleTexture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D runTexture{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPosition{};
    Vector2 worldPosition{};
    Vector2 worldPositionLastFrame{};
    float scale = 4.0f;
    float width = 0.0f;
    float height = 0.0f;

    float walkSpeed = 4.0f;
    float sprintSpeed = 7.0f;
    bool sprinting = false;
    Vector2 velocity{};

    float rightLeft = 1.0f;
    float runningTime = 0.0f;
    int frame = 0;
    int maxFrames = 6;
    float updateTime = 1.0f / 12.0f;

    float attackTimer = 0.0f;
private:
    int health = 100;
    bool alive = true;
    int attackDamage = 10;
    float timeBetweenAttacks = 1.0f;
};

#endif