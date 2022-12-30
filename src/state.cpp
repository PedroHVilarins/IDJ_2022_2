#include "state.h"
#include "inputmanager.h"
#include "camera.h"
#include "camerafollower.h"
#include <cmath>

State::State()
{

	quitRequested = false;
	LoadAssets();
	music.Play();
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

	int i;
	for (i = 0; i < valor; i++)
	{

		objectArray[i]->Update(dt);
	};

	for (i = 0; i < objectArray.size(); i++)
	{

		if (objectArray[i]->IsDead() == true)
		{

			objectArray.erase(objectArray.begin() + i);
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
		if (objectArray[i]->GetComponent("Face"))
		{
			printf("face : %f %f\n", objectArray[i]->box.x, objectArray[i]->box.y);
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

	Face *inimigo = new Face(*objeto);

	objeto->AddComponent(inimigo);

	objectArray.emplace_back(objeto);
}