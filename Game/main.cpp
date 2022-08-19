#include "raylib.h"
#include "raymath.h"

int main()
{
    //Initialise window
    const Vector2 WINDOW_DIMENSIONS{1280,720};
    const char* WINDOW_NAME = "Top Down";
    
    InitWindow(WINDOW_DIMENSIONS.x, WINDOW_DIMENSIONS.y, WINDOW_NAME);

    //Initialise map texture
    Texture2D mapTexture = LoadTexture("nature_tileset/OpenWorldMap.png");
    Vector2 mapPosition{0.0, 0.0};
    float mapRotation = 0.0;
    float mapScale = 2.0;

    const float WALK_SPEED = 4.0;
    const float SPRINT_SPEED = 8.0;

    bool sprinting = false;

    SetTargetFPS(60);
    bool running = true;

    //Main game loop
    while(running)
    {
        const float DELTA_TIME = GetFrameTime();

        if(WindowShouldClose())
        {
            running = false;
        }

        BeginDrawing();

        ClearBackground(WHITE);

        Vector2 moveDir{};
        if(IsKeyDown(KEY_A)) {moveDir.x -= 1.0;}
        if(IsKeyDown(KEY_D)) {moveDir.x += 1.0;}
        if(IsKeyDown(KEY_W)) {moveDir.y -= 1.0;}
        if(IsKeyDown(KEY_S)) {moveDir.y += 1.0;}

        if(IsKeyDown(KEY_LEFT_SHIFT)) {sprinting = true;}
        if(!IsKeyDown(KEY_LEFT_SHIFT)) {sprinting = false;}
        
        if(Vector2Length(moveDir) != 0.0)
        {
            mapPosition = Vector2Subtract(mapPosition, Vector2Scale(Vector2Normalize(moveDir), sprinting ? SPRINT_SPEED : WALK_SPEED));
        }

        DrawTextureEx(mapTexture, mapPosition, mapRotation, mapScale, WHITE);

        EndDrawing();
    }

    UnloadTexture(mapTexture);

    return 0;
}