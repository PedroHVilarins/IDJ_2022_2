#ifndef MINION_H
#define MINION_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "component.h"
#include "vec2.h"
#include <memory>
#include <vector>

using namespace std;

class GameObject;

class Minion : public Component
{

public:
    Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);

    void Update(float dt);
    void Render();
    bool Is(string type);
    void Shoot(Vec2 target);

private:
    weak_ptr<GameObject> alienCenter;
    float arc;
    Vec2 referencial;
};

#endif