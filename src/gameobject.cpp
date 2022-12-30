#include "gameobject.h"
#include "component.h"

GameObject::GameObject()
{
    isDead = false;
}

GameObject::~GameObject()
{
    int valor = components.size();
    int i;

    for (i = valor; i <= 0; i--)
    {
        components.erase(components.begin() + i);
    };

    components.clear();
}

void GameObject::Update(float dt)
{
    int valor = components.size();
    int i;

    for (i = 0; i < valor; i++)
    {
        components[i]->Update(dt);
    };
}

void GameObject::Render()
{
    int valor = components.size();
    int i;

    for (i = 0; i < valor; i++)
    {
        components[i]->Render();
    };
}

bool GameObject::IsDead()
{
    return isDead;
}

void GameObject::RequestDelete()
{
    isDead = true;
}

void GameObject::AddComponent(Component *cpt)
{
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt)
{
    int valor = components.size();
    int i;

    for (i = 0; i < valor; i++)
    {
        if (components[i].get() == cpt)
        {
            components.erase(components.begin() + i);
        };
    };
}

Component *GameObject::GetComponent(string type)
{
    int valor = components.size();
    int i;

    for (i = 0; i < valor; i++)
    {
        if (components[i]->Is(type) == true)
        {
            return components[i].get();
        };
    };

    return nullptr;
}
