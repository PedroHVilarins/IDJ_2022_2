#include "sprite.h"
#include "game.h"

Sprite::Sprite()
{
    texture = nullptr;
}

Sprite::Sprite(string file)
{
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}

void Sprite::Open(string file)
{
    const char *c = file.c_str();
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), c);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
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
