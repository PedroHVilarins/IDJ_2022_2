#include "sprite.h"
#include "game.h"
#include "resources.h"
#include "camera.h"

Sprite::Sprite(GameObject &associated) : Component(associated)
{

    texture = nullptr;
    scale.x = 1;
    scale.y = 1;
}

Sprite::Sprite(GameObject &associated, string file) : Component(associated)
{

    texture = nullptr;
    scale.x = 1;
    scale.y = 1;
    Open(file);
}

Sprite::~Sprite()
{

    Resources::ClearImage();
}

void Sprite::Open(string file)
{

    const char *c = file.c_str();
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
    associated.box.h = height;
    associated.box.w = width;
}

void Sprite::SetClip(int x, int y, int w, int h)
{

    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render()
{

    Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

void Sprite::Render(int x, int y)
{

    SDL_Rect temp;
    temp.x = x + (clipRect.w / 2 - (clipRect.w / 2 * scale.x));
    temp.y = y + (clipRect.h / 2 - (clipRect.h / 2 * scale.y));
    temp.h = clipRect.h * scale.y;
    temp.w = clipRect.w * scale.x;

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &temp, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

int Sprite::GetWidth()
{

    return width * scale.x;
}

int Sprite::GetHeight()
{

    return height * scale.y;
}

bool Sprite::IsOpen()
{

    if (texture != NULL)
    {
        return true;
    };

    return false;
}

bool Sprite::Is(string type)
{

    if (type == "sprite")
    {
        return true;
    };
    return false;
}

void Sprite::Update(float dt) {}

void Sprite::SetScaleX(float scaleX, float scaleY)
{

    if (scaleX != 0)
    {
        scale.x = scaleX;
    }

    if (scaleY != 0)
    {
        scale.y = scaleY;
    }
}

Vec2 Sprite::GetScale()
{

    return scale;
}