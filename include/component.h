#ifndef COMPONENT_H
#define COMPONENT_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
using namespace std;

class GameObject;

class Component
{
public:
    Component(GameObject &associated);

    virtual ~Component();
    void virtual Update(float dt) = 0;
    void virtual Render() = 0;
    bool virtual Is(string type) = 0;

protected:
    GameObject &associated;
};

#endif