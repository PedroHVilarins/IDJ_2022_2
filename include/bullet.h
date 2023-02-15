#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "component.h"
#include "vec2.h"

using namespace std;

class GameObject;

class Bullet : public Component
{

public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool targetsPlayer);

    void Update(float dt);
    void Render();
    bool Is(string type);
    int GetDamage();
    bool targetsPlayer;

private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};

#endif