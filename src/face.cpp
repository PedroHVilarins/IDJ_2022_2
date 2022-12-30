#include "face.h"
#include "gameobject.h"
#include "sound.h"
#include "inputmanager.h"
#include "camera.h"

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
    if (associated.box.Contains({InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y}) and (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)))
    {

        Damage(rand() % 10 + 10);
    }
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