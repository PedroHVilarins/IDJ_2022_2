#ifndef VEC2_H
#define VEC2_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
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
    Vec2 normalizar(Vec2 vet);
};

#endif