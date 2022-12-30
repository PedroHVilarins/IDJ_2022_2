#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <vector>
#include <memory>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "rect.h"

using namespace std;

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
    void Start();
    bool started;

    double angleDeg;

private:
    vector<unique_ptr<Component>> components;
    bool isDead;
};

#endif