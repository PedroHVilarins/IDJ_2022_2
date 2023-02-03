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

    speed = {0, 0};

    if (focus == nullptr)
    {

        if (InputManager::GetInstance().IsKeyDown(SDLK_UP))
        {
            speed = speed + Vec2(0, -1);
        }
        if (InputManager::GetInstance().IsKeyDown(SDLK_DOWN))
        {
            speed = speed + Vec2(0, 1);
        }
        if (InputManager::GetInstance().IsKeyDown(SDLK_RIGHT))
        {
            speed = speed + Vec2(1, 0);
        }
        if (InputManager::GetInstance().IsKeyDown(SDLK_LEFT))
        {
            speed = speed + Vec2(-1, 0);
        };

        pos.x = pos.x + (speed.x * dt * 200);
        pos.y = pos.y + (speed.y * dt * 200);
    }
    else
    {

        pos = {focus->box.GetCenter().x - 500, focus->box.GetCenter().y - 300};
    };
}