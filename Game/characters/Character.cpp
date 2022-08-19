#include "Character.h"
#include "raymath.h"

Character::Character()
{
    width = texture.width/maxFrames;
    height = texture.height;
}

void Character::SetScreenPosition(int windowWidth, int windowHeight)
{
    screenPosition = {
        ((float)windowWidth/2.0f) - (float)scale * (0.5f * width),
        ((float)windowHeight/2.0f) - (float)scale * (0.5f * height)
    };
}

void Character::Tick(float deltaTime)
{
    //Get input
    Vector2 moveDir{};
    if(IsKeyDown(KEY_A)) {moveDir.x -= 1.0;}
    if(IsKeyDown(KEY_D)) {moveDir.x += 1.0;}
    if(IsKeyDown(KEY_W)) {moveDir.y -= 1.0;}
    if(IsKeyDown(KEY_S)) {moveDir.y += 1.0;}

    if(IsKeyDown(KEY_LEFT_SHIFT)) {sprinting = true;}
    if(!IsKeyDown(KEY_LEFT_SHIFT)) {sprinting = false;}
    
    //Move
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

    //Animate
    runningTime += deltaTime;
    if(runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if(frame > maxFrames) {frame = 0;}
    }

    //Draw
    Rectangle playerSource{width * frame, 0.0f, rightLeft * width, height};
    Rectangle playerDest{screenPosition.x, screenPosition.y, scale * width, scale * height};
    Vector2 origin{0.0f, 0.0f};
    DrawTexturePro(texture, playerSource, playerDest, origin, 0.0f, WHITE);
}