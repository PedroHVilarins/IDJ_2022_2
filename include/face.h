#ifndef FACE_H
#define FACE_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "component.h"

using namespace std;

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