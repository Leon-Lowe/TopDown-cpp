#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);

    Texture2D GetTexture() {return texture;}

    void Draw(Vector2 playerPosition);
private:
    Texture2D texture{};
    Vector2 worldPosition{};
    float scale = 4.0f;
};