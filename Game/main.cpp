#include "raylib.h"
#include "raymath.h"

int main()
{
    //Initialise window
    const Vector2 WINDOW_DIMENSIONS{1280.0f, 720.0f};
    const char* WINDOW_NAME = "Top Down";
    
    InitWindow(WINDOW_DIMENSIONS.x, WINDOW_DIMENSIONS.y, WINDOW_NAME);

    //Initialise map texture
    Texture2D mapTexture = LoadTexture("nature_tileset/OpenWorldMap.png");
    Vector2 mapPosition{0.0f, 0.0f};
    float mapRotation = 0.0f;
    float mapScale = 4.0f;

    //Initialise player
    Texture2D playerIdleTexture = LoadTexture("characters/knight_idle_spritesheet.png");
    float playerScale = 4.0f;
    Vector2 playerPosition{
        (WINDOW_DIMENSIONS.x/2.0f) - playerScale * (0.5f * (float)playerIdleTexture.width/6.0),
        (WINDOW_DIMENSIONS.y/2.0f) - playerScale * (0.5f * (float)playerIdleTexture.height)
    };

    //Initialise movement variables
    const float WALK_SPEED = 4.0f;
    const float SPRINT_SPEED = 8.0f;
    float rightLeft = 1.0f; //1 = Facing right, -1 = Facing left
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
            moveDir.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
        }

        //Draw map
        DrawTextureEx(mapTexture, mapPosition, mapRotation, mapScale, WHITE);

        //Draw player
        Rectangle playerSource{0.0f, 0.0f, rightLeft * (float)playerIdleTexture.width/6.0f, (float)playerIdleTexture.height};
        Rectangle playerDest{playerPosition.x, playerPosition.y, playerScale * (float)playerIdleTexture.width/6.0f, playerScale * (float)playerIdleTexture.height};
        Vector2 origin{};
        DrawTexturePro(playerIdleTexture, playerSource, playerDest, origin, 0.0f, WHITE);

        EndDrawing();
    }
    CloseWindow();

    //Unload textures
    UnloadTexture(mapTexture);
    UnloadTexture(playerIdleTexture);

    return 0;
}