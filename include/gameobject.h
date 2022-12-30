#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

#include "rect.h"

class Component;

class GameObject
{
public:
    GameObject();
    ~GameObject();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component *cpt);
    void RemoveComponent(Component *cpt);
    Component *GetComponent(string type);
    Rect box;

private:
    vector<unique_ptr<Component>> components;
    bool isDead;
};

#endif