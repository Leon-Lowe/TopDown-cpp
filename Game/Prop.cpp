#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) :
    texture(tex),
    worldPosition(pos)
{

}

Rectangle Prop::GetCollisionRectangle(Vector2 playerPosition)
{
    Vector2 screenPosition = Vector2Subtract(worldPosition, playerPosition);
    return Rectangle{
        screenPosition.x,
        screenPosition.y,
        texture.width * scale,
        texture.height * scale
    };
}

void Prop::Draw(Vector2 playerPosition)
{
    Vector2 screenPosition = Vector2Subtract(worldPosition, playerPosition);
    DrawTextureEx(texture, screenPosition, 0.0f, scale, WHITE);
}