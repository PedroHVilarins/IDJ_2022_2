#ifndef ALIEN_H
#define ALIEN_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "component.h"
#include "vec2.h"
#include "timer.h"
#include <memory>
#include <vector>
#include <queue>

using namespace std;

class GameObject;

class Alien : public Component
{

public:
    Alien(GameObject &associated, int nMinions);
    ~Alien();
    void Start();

    void Update(float dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject &other);

    int alienCount;

private:
    enum AlienState
    {
        MOVING,
        RESTING
    };
    AlienState state;
    Timer *restTimer;
    Vec2 destination;

    Vec2 speed;
    int hp;

    vector<weak_ptr<GameObject>> minionArray;
};

#endif