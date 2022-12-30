#include "sprite.h"
#include "game.h"
#include "resources.h"
#include "camera.h"

Sprite::Sprite(GameObject &associated) : Component(associated)
{

    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, string file) : Component(associated)
{

    texture = nullptr;

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
    temp.x = x;
    temp.y = y;
    temp.h = clipRect.h;
    temp.w = clipRect.w;

    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &temp);
}

int Sprite::GetWidth()
{

    return width;
}

int Sprite::GetHeight()
{

    return height;
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
