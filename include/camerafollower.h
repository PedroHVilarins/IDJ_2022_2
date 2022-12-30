#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
using namespace std;

#include "component.h"

class GameObject;

class CameraFollower : public Component
{
public:
    CameraFollower(GameObject &associated);

    void Update(float dt);
    void Render();
    bool Is(string type);
};

#endif