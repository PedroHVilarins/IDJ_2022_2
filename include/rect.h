#ifndef RECT_H
#define RECT_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
using namespace std;

#include "vec2.h"

class Rect
{
public:
    Rect();
    Rect(float d, float f, float j, float l);
    float x;
    float y;
    float w;
    float h;
    bool Contains(Vec2 vetor);
};

#endif