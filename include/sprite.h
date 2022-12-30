#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "component.h"
#include "vec2.h"

using namespace std;

class Sprite : public Component
{

public:
    Sprite(GameObject &associated);
    Sprite(GameObject &associated, string file);
    ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render();
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();

    void Update(float dt);
    bool Is(string type);

    void SetScaleX(float scaleX, float scaleY);
    Vec2 GetScale();

private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;

    Vec2 scale;
};

#endif