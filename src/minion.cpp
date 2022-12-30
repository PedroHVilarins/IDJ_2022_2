#include "minion.h"
#include "bullet.h"
#include "sprite.h"
#include "gameobject.h"
#include "game.h"
#include <cmath>

Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated)
{

    double tamanho = 1 + double(rand()) / (double(RAND_MAX / (1.5 - 1.0)));

    this->alienCenter = alienCenter;
    arc = arcOffsetDeg;

    Sprite *minio = new Sprite(associated, "./assets/img/minion.png");

    minio->SetScaleX(tamanho, tamanho);

    this->associated.AddComponent(minio);
}

using namespace std;

void Minion::Update(float dt)
{

    float constante = M_PI / (720 * dt);

    Vec2 distancia = Vec2(100, 0);

    Vec2 centro;
    if (shared_ptr<GameObject> go = alienCenter.lock())
    {

        centro.x = go->box.x + (go->box.w / 2);
        centro.y = go->box.y + (go->box.h / 2);
    }

    distancia = distancia.GetRotated(arc) + centro;

    arc = arc + constante;

    associated.box.y = distancia.y - (associated.box.h / 2);
    associated.box.x = distancia.x - (associated.box.w / 2);
}

void Minion::Render() {}

bool Minion::Is(string type)
{

    if (type == "Minion")
    {
        return true;
    };
    return false;
}

void Minion::Shoot(Vec2 target)
{
    GameObject *objeto = new GameObject();

    objeto->box.x = associated.box.x + associated.box.w / 2;
    objeto->box.y = associated.box.y + associated.box.h / 2;

    Vec2 inicio = Vec2((associated.box.x + associated.box.w / 2), (associated.box.y + associated.box.h / 2));

    Vec2 distancia = inicio - target;

    float angulo = atan2(distancia.y, distancia.x);

    Bullet *bala = new Bullet(*objeto, angulo, 500, 5, 500, "./assets/img/minionbullet1.png");

    objeto->AddComponent(bala);

    objeto->box.x -= objeto->box.w / 2;
    objeto->box.y -= objeto->box.h / 2;

    State &estado = Game::GetInstance().GetState();
    estado.AddObject(objeto);
}