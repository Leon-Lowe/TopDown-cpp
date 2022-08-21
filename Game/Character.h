#include "raylib.h"

class Character
{
public:
    Character(float windowWidth, float windowHeight);

    Vector2 GetWorldPositon() {return worldPosition;}
    Vector2 GetScreenPosition() {return screenPosition;}
    Texture2D GetTexture() {return texture;}
    Texture2D GetIdleTexture() {return idle;}
    Texture2D GetRunTexture() {return run;}
    int GetRightLeft() {return rightLeft;}
    int GetFrame() {return frame;}
    int GetMaxFrames() {return maxFrames;}
    float GetRunningTime() {return runningTime;}
    float GetUpdateTime() {return updateTime;}
    Rectangle GetCollisionRectangle();

    void Tick(float deltaTime);
    void UndoMovement();

private:
    Vector2 GetInput();
    void Move(Vector2 moveDir);
    void Animate(float deltaTime);
    void Draw();

    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPosition{};
    Vector2 worldPosition{};
    Vector2 worldPositionLastFrame{};
    float scale = 4.0f;
    float width = 0.0f;
    float height = 0.0f;

    float walkSpeed = 4.0f;
    float sprintSpeed = 7.0f;
    bool sprinting = false;

    float rightLeft = 1.0f;
    float runningTime = 0.0f;
    int frame = 0;
    int maxFrames = 6;
    float updateTime = 1.0f / 12.0f;
};