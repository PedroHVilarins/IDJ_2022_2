#include "face.h"
#include "gameobject.h"
#include "sound.h"

Face::Face(GameObject &associated) : Component(associated)
{
    hitpoints = 30;
}

void Face::Damage(int damage)
{
    hitpoints = hitpoints - damage;
    if (hitpoints <= 0)
    {
        associated.RequestDelete();

        if (associated.GetComponent("sound") != nullptr)
        {
            Sound *som = (Sound *)associated.GetComponent("sound");
            som->Play();
        };
    };
}

void Face::Update(float dt)
{
}

void Face::Render()
{
}

bool Face::Is(string type)
{
    if (type == "Face")
    {
        return true;
    };
    return false;
}