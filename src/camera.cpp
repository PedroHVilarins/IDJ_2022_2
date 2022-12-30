#include "camera.h"
#include "inputmanager.h"

Vec2 Camera::pos = {0, 0};
Vec2 Camera::speed;
GameObject *Camera::focus;

void Camera::Follow(GameObject *newFocus)
{
    focus = newFocus;
}

void Camera::Unfollow()
{
    focus = nullptr;
}

void Camera::Update(float dt)
{
    if (focus == nullptr)
    {

        if (InputManager::GetInstance().IsKeyDown(SDLK_UP))
        {
            speed = {0, -dt};
            pos = pos + speed;
        }
        if (InputManager::GetInstance().IsKeyDown(SDLK_DOWN))
        {
            speed = {0, dt};
            pos = pos + speed;
        }
        if (InputManager::GetInstance().IsKeyDown(SDLK_RIGHT))
        {
            speed = {dt, 0};
            pos = pos + speed;
        }
        if (InputManager::GetInstance().IsKeyDown(SDLK_LEFT))
        {
            speed = {-dt, 0};
            pos = pos + speed;
        };
    }
    else
    {

        pos = {focus->box.x, focus->box.y};
    };
}