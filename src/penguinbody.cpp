#include "penguinbody.h"
#include "sprite.h"
#include "state.h"
#include "penguincannon.h"
#include "game.h"
#include "inputmanager.h"
#include "collider.h"
#include "bullet.h"
#include "camera.h"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated)
{

    hp = 50;
    angle = 0;
    linearSpeed = 1;
    speed = Vec2(0, 0);

    player = this;

    Sprite *peng = new Sprite(associated, "./assets/img/penguin.png");

    associated.AddComponent(peng);

    Collider *colisor = new Collider(associated);
    this->associated.AddComponent(colisor);
}

PenguinBody::~PenguinBody()
{

    player = nullptr;
}

void PenguinBody::Start()
{

    State &temp = Game::GetInstance().GetState();

    GameObject *objeto = new GameObject();

    weak_ptr<GameObject> peng = temp.GetObjectPtr(&associated);

    PenguinCannon *canhao = new PenguinCannon(*objeto, peng);

    objeto->AddComponent(canhao);

    pcannon = temp.AddObject(objeto);
}

void PenguinBody::Update(float dt)
{

    int velocidade = 50;

    Vec2 atual = Vec2(associated.box.x, associated.box.y);

    if (InputManager::GetInstance().IsKeyDown(SDLK_a))
    {
        angle = angle - 2 * M_PI / (60 * dt);
        associated.angleDeg = angle;
    }
    if (InputManager::GetInstance().IsKeyDown(SDLK_d))
    {
        angle = angle + 2 * M_PI / (60 * dt);
        associated.angleDeg = angle;
    }

    if (InputManager::GetInstance().IsKeyDown(SDLK_w))
    {

        if (speed.x < velocidade)
        {
            speed.x = speed.x + 1;
        }
        else
        {
            speed.x = velocidade;
        }
    }
    else if (InputManager::GetInstance().IsKeyDown(SDLK_s))
    {

        if (speed.x > -velocidade)
        {
            speed.x = speed.x - 1;
        }
        else
        {
            speed.x = -velocidade;
        }
    }
    else
    {
        if (speed.x > 0)
        {
            speed.x = speed.x - linearSpeed;
        }
        else if (speed.x < 0)
        {
            speed.x = speed.x + linearSpeed;
        }
        else
        {
            speed.x = 0;
        }
    }

    Vec2 temp;

    temp.x = speed.normalizar().GetRotated(angle / 180 * M_PI).x * dt * 10;
    temp.y = speed.normalizar().GetRotated(angle / 180 * M_PI).y * dt * 10;

    atual.x = atual.x + temp.x;
    atual.y = atual.y + temp.y;

    associated.box.x = atual.x;
    associated.box.y = atual.y;

    if (hp <= 0)
    {

        GameObject *morte = new GameObject();

        morte->box = associated.box;

        associated.RequestDelete();
        pcannon.lock()->RequestDelete();

        Camera::Unfollow();

        Sprite *explosao = new Sprite(*morte, "./assets/img/penguindeath.png", 5, 0.2, 1);

        morte->AddComponent(explosao);

        State &temp = Game::GetInstance().GetState();

        Sound *som = new Sound(*morte, "./assets/audio/boom.wav");

        som->Play();

        morte->AddComponent(som);

        temp.AddObject(morte);
    }
}

void PenguinBody::Render() {}

bool PenguinBody::Is(string type)
{

    if (type == "penguinbody")
    {
        return true;
    };
    return false;
}

void PenguinBody::NotifyCollision(GameObject &other)
{

    Bullet *tiro = (Bullet *)other.GetComponent("Bullet");

    if (tiro != nullptr)
    {

        if (tiro->targetsPlayer == true)
        {

            int dano = tiro->GetDamage();

            other.RequestDelete();

            hp = hp - dano;
        }
    }
}

Rect PenguinBody::GetPos()
{

    return associated.box;
}