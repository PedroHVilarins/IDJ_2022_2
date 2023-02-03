#include "state.h"
#include "inputmanager.h"
#include "camera.h"
#include "camerafollower.h"
#include "alien.h"
#include "penguinbody.h"
#include "collider.h"
#include <cmath>

State::State()
{

	started = false;
	quitRequested = false;
}

State::~State()
{

	objectArray.clear();
}

void State::LoadAssets()
{

	GameObject *objeto = new GameObject();

	Sprite *bg = new Sprite(*objeto, "./assets/img/ocean.jpg");
	objeto->box.x = 0;
	objeto->box.y = 0;

	CameraFollower *seguidor = new CameraFollower(*objeto);

	objeto->AddComponent(bg);
	objeto->AddComponent(seguidor);
	objectArray.emplace_back(objeto);

	GameObject *outro = new GameObject();

	TileSet *tile = new TileSet(64, 64, "./assets/img/tileset.png");
	TileMap *mapa = new TileMap(*outro, "./assets/map/tileMap.txt", tile);

	outro->AddComponent(mapa);
	objectArray.emplace_back(outro);

	GameObject *player = new GameObject();

	player->box.x = 750;
	player->box.y = 750;
	PenguinBody *jogador = new PenguinBody(*player);

	player->AddComponent(jogador);

	Camera::Follow(player);
	objectArray.emplace_back(player);

	GameObject *inimigo = new GameObject();

	Alien *alienigena = new Alien(*inimigo, 2);
	inimigo->box.x = 20;
	inimigo->box.y = 20;

	inimigo->AddComponent(alienigena);
	objectArray.emplace_back(inimigo);

	music = *new Music("./assets/audio/stageState.ogg");
}

void State::Update(float dt)
{
	int valor = objectArray.size();
	Camera::Update(dt);

	if ((InputManager::GetInstance().KeyPress(SDLK_ESCAPE) == true) or (InputManager::GetInstance().QuitRequested() == true))
	{

		quitRequested = true;
	};

	if (InputManager::GetInstance().KeyPress(SDLK_SPACE) == true)
	{
		Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI * (rand() % 1001) / 500.0) + Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
		AddObject((int)objPos.x, (int)objPos.y);
	};

	int i, j;
	for (i = 0; i < valor; i++)
	{

		objectArray[i]->Update(dt);
	};

	for (i = 0; i < valor; i++)
	{
		Collider *colisor = (Collider *)objectArray[i]->GetComponent("collider");

		if (colisor != nullptr)
		{

			for (j = i + 1; j < valor; j++)
			{
				Collider *colidente = (Collider *)objectArray[j]->GetComponent("collider");

				if (colidente != nullptr)
				{

					if (colisor->IsColliding(*colidente) == true)
					{

						objectArray[i]->NotifyCollision(*objectArray[j]);
						objectArray[j]->NotifyCollision(*objectArray[i]);
					}
				}
			}
		}
	}

	for (i = 0; i < objectArray.size(); i++)
	{

		if (objectArray[i]->IsDead() == true)
		{

			objectArray.erase(objectArray.begin() + i);
			i--;
		};
	};
}

void State::Render()
{
	int valor = objectArray.size();

	int i;
	for (i = 0; i < valor; i++)
	{
		if (objectArray[i]->GetComponent("camerafollower"))
		{
			printf("camera : %f %f\n", Camera::pos.x, Camera::pos.y);
		}

		objectArray[i]->Render();
	};
}

bool State::QuitRequested()
{

	return quitRequested;
}

void State::AddObject(int mouseX, int mouseY)
{

	GameObject *objeto = new GameObject();

	Sprite *penguin = new Sprite(*objeto, "./assets/img/penguinface.png");
	objeto->box.x = (mouseX - (penguin->GetWidth()) / 2) + Camera::pos.x;
	objeto->box.y = (mouseY - (penguin->GetHeight()) / 2) + Camera::pos.y;

	objeto->AddComponent(penguin);

	Sound *som = new Sound(*objeto, "./assets/audio/boom.wav");

	objeto->AddComponent(som);

	objectArray.emplace_back(objeto);
}

void State::Start()
{

	LoadAssets();
	music.Play();

	int valor = objectArray.size();
	for (int i = 0; i < valor; i++)
	{

		objectArray[i]->Start();
	};

	started = true;
}

weak_ptr<GameObject> State::AddObject(GameObject *go)
{

	shared_ptr<GameObject> novo(go);

	objectArray.push_back(novo);

	if (started)
	{

		go->Start();
	};

	weak_ptr<GameObject> retorno(novo);

	return retorno;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{

	int valor = objectArray.size();

	int i;
	for (i = 0; i < valor; i++)
	{

		if (objectArray[i]->GetComponent("Alien") != nullptr)
			cout << "alien existe" << endl;
		if (objectArray[i].get() == go)
		{
			cout << "ALIEN ENCONTRADO" << endl;

			weak_ptr<GameObject> retorno(objectArray[i]);
			return retorno;
		};
	};

	weak_ptr<GameObject> retorno;

	return retorno;
}