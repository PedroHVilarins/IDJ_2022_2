#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "component.h"

using namespace std;

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