#ifndef ALIEN_H
#define ALIEN_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "component.h"
#include "vec2.h"
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

private:
    class Action
    {

    public:
        enum ActionType
        {
            Move,
            Shoot
        };
        Action(ActionType type, float x, float y);

        ActionType type;
        Vec2 pos;
    };

    Vec2 speed;
    int hp;

    queue<Action> taskQueue;
    vector<weak_ptr<GameObject>> minionArray;
};

#endif