#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"

using namespace std;

class Vec2
{

public:
    Vec2();
    Vec2(int d, int j);
    float x;
    float y;
    Vec2 GetRotated(float ang);
    Vec2 operator+(Vec2 primeiro);
};

#endif