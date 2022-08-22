#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 position, Texture2D idleTex, Texture2D runTex, float speed);

    void SetTarget(Character* character) {target = character;}

    virtual void Tick(float deltaTime) override;
private:
    void HandleVelocity();
    
    Character* target;
};