#include "raylib.h"
#include "raymath.h"
#include "Character.h"

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
    Character player;
    player.SetScreenPosition(WINDOW_DIMENSIONS.x, WINDOW_DIMENSIONS.y);

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

        mapPosition = Vector2Scale(player.GetWorldPositon(), -1.0f);

        //Draw map
        DrawTextureEx(mapTexture, mapPosition, mapRotation, mapScale, WHITE);

        player.Tick(DELTA_TIME);

        EndDrawing();
    }
    CloseWindow();

    //Unload textures
    UnloadTexture(mapTexture);
    UnloadTexture(player.GetTexture());
    UnloadTexture(player.GetRunTexture());
    UnloadTexture(player.GetIdleTexture());

    return 0;
}