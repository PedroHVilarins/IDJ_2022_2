#ifndef FACE_H
#define FACE_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
using namespace std;

#include "component.h"

class GameObject;

class Face : public Component
{
public:
    Face(GameObject &associated);
    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(string type);

private:
    int hitpoints;
};

#endif