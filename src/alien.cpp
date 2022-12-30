#include "alien.h"
#include "sprite.h"
#include "inputmanager.h"
#include "camera.h"
#include "minion.h"
#include "state.h"
#include "game.h"

Alien::Alien(GameObject &associated, int nMinions) : Component(associated)
{

    Sprite *alien = new Sprite(associated, "./assets/img/alien.png");

    this->associated.AddComponent(alien);
    hp = 10;
    speed = {0, 0};
}

Alien::Action::Action(ActionType type, float x, float y)
{

    this->type = type;
    pos = {x, y};
}

void Alien::Start()
{
    int aliens = 4;

    int i;

    for (i = 0; i < aliens; i++)
    {

        State &temp = Game::GetInstance().GetState();
        GameObject *objeto = new GameObject();
        weak_ptr<GameObject> centro = temp.GetObjectPtr(&associated);
        Minion *bola = new Minion(*objeto, centro, (M_PI * (1 + 2 * i * 360 / aliens)) / 360);
        objeto->AddComponent(bola);
        minionArray.push_back(temp.AddObject(objeto));
    }
}

Alien::~Alien()
{

    minionArray.clear();
}

void Alien::Update(float dt)
{

    associated.angleDeg = associated.angleDeg - M_PI / 180 * dt * 1024;

    if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT))
    {

        taskQueue.push(Action(Action::Shoot, InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y));
    }
    if (InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT))
    {

        taskQueue.push(Action(Action::Move, InputManager::GetInstance().GetMouseX() + Camera::pos.x, InputManager::GetInstance().GetMouseY() + Camera::pos.y));
    }

    speed = Vec2(0, 0);
    Vec2 posic_atual = Vec2(associated.box.x, associated.box.y);

    if (taskQueue.size() != 0)
    {

        if (taskQueue.front().type == Action::Move)
        {

            Vec2 destino;

            destino.x = taskQueue.front().pos.x - (associated.box.w / 2);
            destino.y = taskQueue.front().pos.y - (associated.box.h / 2);
            Vec2 aux = (posic_atual - destino).normalizar();
            speed.x = speed.x + aux.x;
            speed.y = speed.y + aux.y;

            posic_atual.x = posic_atual.x + (speed.x * dt * 200);
            posic_atual.y = posic_atual.y + (speed.y * dt * 200);

            Vec2 distancia = posic_atual - destino;

            printf("distancia %f %f\n", distancia.x, distancia.y);
            printf("destino %f %f\n", destino.x, destino.y);

            printf("%f %f\n", associated.box.x, associated.box.y);
            float temp = abs(distancia.magnitude());

            if (temp <= 10)
            {
                posic_atual = destino;
                taskQueue.pop();
            }

            associated.box.x = posic_atual.x;
            associated.box.y = posic_atual.y;
        }

        if (taskQueue.front().type == Action::Shoot)
        {

            int i;
            float temp;
            float minimo = 1000000;
            int escolhido = 0;

            for (i = 0; i < minionArray.size(); i++)
            {
                if (shared_ptr<GameObject> go = minionArray[i].lock())
                {
                    Vec2 aux = Vec2((taskQueue.front().pos.x - go->box.x), (taskQueue.front().pos.y - go->box.y));
                    temp = aux.magnitude();

                    if (temp < minimo)
                    {

                        minimo = temp;
                        escolhido = i;
                    }
                }
            }

            if (shared_ptr<GameObject> go = minionArray[escolhido].lock())
            {

                Minion *minion = (Minion *)go->GetComponent("Minion");
                minion->Shoot(taskQueue.front().pos);
                taskQueue.pop();
            }
        }
    }

    if (hp <= 0)
    {

        associated.RequestDelete();
    }
}

void Alien::Render() {}

bool Alien::Is(string type)
{

    if (type == "Alien")
    {
        return true;
    };
    return false;
}
