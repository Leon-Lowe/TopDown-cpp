#include "raylib.h"

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
    float mapScale = 4.0;

    bool running = true;

    //Main game loop
    while(running)
    {
        if(WindowShouldClose())
        {
            running = false;
        }

        BeginDrawing();

        ClearBackground(WHITE);

        DrawTextureEx(mapTexture, mapPosition, mapRotation, mapScale, WHITE);

        EndDrawing();
    }

    UnloadTexture(mapTexture);

    return 0;
}