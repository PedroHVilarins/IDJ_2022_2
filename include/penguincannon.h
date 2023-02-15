#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#include <iostream>
#include <vector>
#include <memory>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "component.h"
#include "timer.h"
#include "vec2.h"

using namespace std;

class GameObject;

class PenguinCannon : public Component
{

public:
    PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody);
    ~PenguinCannon();

    void Update(float dt);
    void Render();
    bool Is(string type);

    void Shoot();

private:
    weak_ptr<GameObject> pbody;
    float angle;
    float cooldown;
    Timer *timer;
};

#endif