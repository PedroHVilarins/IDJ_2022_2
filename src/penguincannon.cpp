#include "penguincannon.h"
#include "sprite.h"
#include "state.h"
#include "inputmanager.h"
#include "camera.h"
#include "game.h"
#include "bullet.h"
#include "collider.h"
#include <cmath>

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody) : Component(associated)
{

    angle = 0;
    pbody = penguinBody;

    Sprite *cann = new Sprite(associated, "./assets/img/cubngun.png");

    associated.AddComponent(cann);

    Collider *colisor = new Collider(associated);
    this->associated.AddComponent(colisor);

    cooldown = 0.5;

    timer = new Timer();
}

void PenguinCannon::Update(float dt)
{

    timer->Update(dt);

    if (shared_ptr<GameObject> go = pbody.lock())
    {

        associated.box.x = go->box.x + go->box.w / 2 - associated.box.w / 2;
        associated.box.y = go->box.y + go->box.h / 2 - associated.box.h / 2;

        Vec2 mouse = Vec2(InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y);
        Vec2 centro = Vec2(associated.box.x + associated.box.w / 2, associated.box.y + associated.box.h / 2);

        Vec2 ponto = centro - mouse;

        angle = atan2(ponto.y, ponto.x);

        associated.angleDeg = angle * 180 / M_PI;

        if (InputManager::GetInstance().IsMouseDown(SDL_BUTTON_LEFT))
        {

            if (timer->Get() > cooldown)
            {
                Shoot();
            }
        }
    }
    else
    {

        associated.RequestDelete();
    }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(string type)
{

    if (type == "penguincannon")
    {
        return true;
    };
    return false;
}

void PenguinCannon::Shoot()
{

    Sprite *peng = (Sprite *)associated.GetComponent("sprite");

    Vec2 inicio = Vec2((associated.box.x + associated.box.w / 2), (associated.box.y + associated.box.h / 2));
    Vec2 fim = Vec2(peng->GetWidth() / 2, 0).GetRotated(angle);

    Vec2 ponto = fim + inicio;

    GameObject *objeto = new GameObject();

    objeto->box.x = ponto.x;
    objeto->box.y = ponto.y;
    objeto->angleDeg = angle * 180 / M_PI;

    Bullet *bala = new Bullet(*objeto, angle, 500, 5, 500, "./assets/img/penguinbullet.png", 4, 0.2, false);

    objeto->AddComponent(bala);

    State &estado = Game::GetInstance().GetCurrentState();
    estado.AddObject(objeto);

    timer->Restart();
}

PenguinCannon::~PenguinCannon() {}