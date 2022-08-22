#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 position, Texture2D idleTex, Texture2D runTex, float speed, int health, int damage, float timeBetweenAttacks);

    void SetTarget(Character* character) {target = character;}

    virtual void Tick(float deltaTime) override;
private:
    void HandleVelocity();

    Character* target;
    float radius = 25.0f;
};