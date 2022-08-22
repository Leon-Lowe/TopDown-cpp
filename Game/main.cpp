#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <string>

int main()
{
    //Initialise window
    const Vector2 WINDOW_DIMENSIONS{1280, 720};
    const char* WINDOW_NAME = "Top Down";
    
    InitWindow(WINDOW_DIMENSIONS.x, WINDOW_DIMENSIONS.y, WINDOW_NAME);

    //Initialise map texture
    Texture2D mapTexture = LoadTexture("nature_tileset/OpenWorldMap.png");
    Vector2 mapPosition{0.0f, 0.0f};
    float mapRotation = 0.0f;
    float mapScale = 4.0f;

    //Initialise player
    Character player{WINDOW_DIMENSIONS, 35, 0.2f};

    //Initialse enemies
    Enemy goblin{
        Vector2{1000.0f, 1000.0f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png"),
        3.5f,
        50,
        10,
        1.0f
    };

    Enemy slime{
        Vector2{1500.0f, 500.0f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
        5.0f,
        75,
        5,
        0.7f
    };

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for(Enemy* enemy : enemies)
    {
        enemy->SetTarget(&player);
    }

    //Initialise props
    Prop props[2]{
        Prop{Vector2{1200.0f, 600.0f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{800.0f, 1000.0f}, LoadTexture("nature_tileset/Log.png")}
    };

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

        //Draw props
        for(Prop prop : props)
        {
            prop.Draw(player.GetWorldPositon());
        }

        if(player.GetAlive())
        {
            std::string healthText = "Health: ";
            healthText.append(std::to_string(player.GetHealth()));
            DrawText(healthText.c_str(), 5, 5, 40, GREEN);
        }
        else
        {
            DrawText("Game Over!", 200.0f, 300.0f, 160, RED);
            EndDrawing();
            continue;
        }

        player.Tick(DELTA_TIME);
        
        for(Enemy* enemy : enemies)
        {
            enemy->Tick(DELTA_TIME);
        }

        //Check map bounds
        if(player.GetWorldPositon().x < 0.0f ||
            player.GetWorldPositon().y < 0.0f ||
            player.GetWorldPositon().x + WINDOW_DIMENSIONS.x > mapTexture.width * mapScale ||
            player.GetWorldPositon().y + WINDOW_DIMENSIONS.y > mapTexture.height * mapScale)
        {
            player.UndoMovement();
        }

        //Check prop collisions
        for(Prop prop : props)
        {
            if(CheckCollisionRecs(prop.GetCollisionRectangle(player.GetWorldPositon()), player.GetCollisionRectangle()))
            {
                player.UndoMovement();
            }
        }

        //Check player attacking
        if(player.GetAttacking())
        {
            for(Enemy* enemy : enemies)
            {
                if(CheckCollisionRecs(enemy->GetCollisionRectangle(), player.GetWeaponCollisionRect()))
                {
                    enemy->Damage(player.GetAttackDamage());
                }
            }
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}