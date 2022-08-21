#include "Character.h"
#include "raymath.h"

Character::Character(float windowWidth, float windowHeight)
{
    screenPosition = {
        (windowWidth/2.0f) - scale * (0.5f * width),
        (windowHeight/2.0f) - scale * (0.5f * height)
    };

    width = texture.width/maxFrames;
    height = texture.height;
}

Rectangle Character::GetCollisionRectangle()
{
    return Rectangle{
        screenPosition.x,
        screenPosition.y,
        width * scale,
        height * scale
    };
}

void Character::Tick(float deltaTime)
{
    Vector2 moveDir = GetInput();
    Move(moveDir);
    Animate(deltaTime);
    Draw();
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

void Character::Move(Vector2 moveDir)
{
    worldPositionLastFrame = worldPosition;

    if(Vector2Length(moveDir) != 0.0)
    {
        worldPosition = Vector2Add(worldPosition, Vector2Scale(Vector2Normalize(moveDir), sprinting ? sprintSpeed : walkSpeed));
        moveDir.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
}

void Character::Animate(float deltaTime)
{
    runningTime += deltaTime;
    if(runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if(frame > maxFrames) {frame = 0;}
    }
}

void Character::Draw()
{
    Rectangle playerSource{width * frame, 0.0f, rightLeft * width, height};
    Rectangle playerDest{screenPosition.x, screenPosition.y, scale * width, scale * height};
    Vector2 origin{0.0f, 0.0f};
    DrawTexturePro(texture, playerSource, playerDest, origin, 0.0f, WHITE);
}

void Character::UndoMovement()
{
    worldPosition = worldPositionLastFrame;
}