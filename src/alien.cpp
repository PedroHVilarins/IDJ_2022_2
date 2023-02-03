#include "alien.h"
#include "sprite.h"
#include "inputmanager.h"
#include "camera.h"
#include "minion.h"
#include "state.h"
#include "game.h"
#include "collider.h"
#include "bullet.h"
#include "sound.h"
#include "penguinbody.h"

Alien::Alien(GameObject &associated, int nMinions) : Component(associated)
{

    Sprite *alien = new Sprite(associated, "./assets/img/alien.png");

    this->associated.AddComponent(alien);

    Collider *colisor = new Collider(associated);
    this->associated.AddComponent(colisor);

    hp = 50;
    speed = {0, 0};

    alienCount = alienCount + 1;

    state = RESTING;

    restTimer = new Timer();
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

    alienCount = alienCount - 1;
}

void Alien::Update(float dt)
{

    if (hp <= 0)
    {

        int i;
        int valor = minionArray.size();

        for (i = 0; i < valor; i++)
        {
            if (shared_ptr<GameObject> minion = minionArray[i].lock())
                minion->RequestDelete();
        }

        GameObject *morte = new GameObject();

        morte->box = associated.box;

        associated.RequestDelete();

        Sprite *explosao = new Sprite(*morte, "./assets/img/aliendeath.png", 4, 0.2, 0.8);

        morte->AddComponent(explosao);

        State &temp = Game::GetInstance().GetState();

        Sound *som = new Sound(*morte, "./assets/audio/boom.wav");

        som->Play();

        morte->AddComponent(som);

        temp.AddObject(morte);
    }
    else
    {

        restTimer->Update(dt);
        Vec2 posic_atual = Vec2(associated.box.x, associated.box.y);

        if (state == MOVING)
        {

            int flag = 0;
            posic_atual.x = posic_atual.x + (speed.x * dt * 200);
            posic_atual.y = posic_atual.y + (speed.y * dt * 200);

            Vec2 distancia = posic_atual - destination;

            float temp = abs(distancia.magnitude());

            if (temp <= 300)
            {
                flag = 1;
                speed = {0, 0};
            }

            associated.box.x = posic_atual.x;
            associated.box.y = posic_atual.y;

            if (flag == 1)
            {

                Vec2 destino;
                PenguinBody *jogador = PenguinBody::player;

                if (jogador != nullptr)
                {

                    destino.x = jogador->GetPos().GetCenter().x;
                    destino.y = jogador->GetPos().GetCenter().y;

                    destination = Vec2(destino.x, destino.y);

                    int i;
                    float temp;
                    float minimo = 1000000;
                    int escolhido = 0;

                    for (i = 0; i < minionArray.size(); i++)
                    {
                        if (shared_ptr<GameObject> go = minionArray[i].lock())
                        {
                            Vec2 aux = Vec2((destination.x - go->box.x), (destination.y - go->box.y));
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
                        minion->Shoot(destination);
                    }

                    state = RESTING;
                    restTimer->Restart();
                }
            }
        }

        associated.angleDeg = associated.angleDeg - M_PI / 180 * dt * 1024;

        if (state == RESTING)
        {

            if (restTimer->Get() > 0.2)
            {

                Vec2 destino;
                PenguinBody *jogador = PenguinBody::player;

                if (jogador != nullptr)
                {

                    destino.x = jogador->GetPos().GetCenter().x - (associated.box.w / 2);
                    destino.y = jogador->GetPos().GetCenter().y - (associated.box.h / 2);
                    destination = Vec2(destino.x, destino.y);

                    Vec2 aux = (posic_atual - destino).normalizar();
                    speed.x = speed.x + aux.x;
                    speed.y = speed.y + aux.y;

                    state = MOVING;
                }
            }
        }
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

void Alien::NotifyCollision(GameObject &other)
{

    Bullet *tiro = (Bullet *)other.GetComponent("Bullet");

    if (tiro != nullptr)
    {

        if (tiro->targetsPlayer == false)
        {

            int dano = tiro->GetDamage();

            other.RequestDelete();

            hp = hp - dano;
        }
    }
}
