#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);

    Texture2D GetTexture() {return texture;}
    Rectangle GetCollisionRectangle(Vector2 playerPosition);

    void Draw(Vector2 playerPosition);
private:
    Texture2D texture{};
    Vector2 worldPosition{};
    float scale = 4.0f;
};