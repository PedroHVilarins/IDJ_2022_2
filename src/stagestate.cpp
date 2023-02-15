#include "stagestate.h"
#include "inputmanager.h"
#include "camera.h"
#include "camerafollower.h"
#include "alien.h"
#include "penguinbody.h"
#include "collider.h"
#include "endstate.h"
#include "gamedata.h"
#include "game.h"
#include <cmath>

StageState::StageState()
{

	backgroundMusic = nullptr;
	tileSet = nullptr;

	started = false;
	quitRequested = false;

	GameData::playerVictory = false;
}

StageState::~StageState()
{

	objectArray.clear();
}

void StageState::LoadAssets()
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

	int i;

	for (i = 0; i < 4; i++)
	{

		GameObject *inimigo = new GameObject();

		int x = 750, y = 750;

		while ((x <= 1050) and (x >= 550))
		{

			x = rand() % 2000;
		}
		while ((y <= 1050) and (y >= 550))
		{

			y = rand() % 2000;
		}

		inimigo->box.x = x;
		inimigo->box.y = y;

		Alien *alienigena = new Alien(*inimigo, rand() % (5 - 3 + 1) + 3, rand() % 5 + 1);

		inimigo->AddComponent(alienigena);
		objectArray.emplace_back(inimigo);
	}

	backgroundMusic = new Music("./assets/audio/stageState.ogg");
}

void StageState::Update(float dt)
{
	int valor = objectArray.size();

	if (PenguinBody::player == nullptr)
	{
		GameData::playerVictory = false;
		popRequested = true;
		EndState *fim = new EndState();
		Game::GetInstance().Push(fim);
	}
	else if (Alien::alienCount == 0)
	{
		GameData::playerVictory = true;
		popRequested = true;
		EndState *fim = new EndState();
		Game::GetInstance().Push(fim);
	}

	else
	{
		if ((InputManager::GetInstance().KeyPress(SDLK_ESCAPE) == true) or (InputManager::GetInstance().QuitRequested() == true))
		{

			popRequested = true;
			backgroundMusic->Stop();
			Camera::Unfollow();
			Camera::pos = Vec2(0, 0);
		};
		Camera::Update(dt);
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

		for (i = 0, j = objectArray.size(); i < j; i++)
		{

			if (objectArray[i]->IsDead() == true)
			{

				objectArray.erase(objectArray.begin() + i);
				i--;
				j--;
			};
		};
	}
}

void StageState::Render()
{
	int valor = objectArray.size();

	int i;
	for (i = 0; i < valor; i++)
	{
		if (objectArray[i]->GetComponent("penguinbody"))
		{
			printf("camera : %f %f\n", objectArray[i]->box.x, objectArray[i]->box.y);
		}

		objectArray[i]->Render();
	};
}

void StageState::Start()
{

	LoadAssets();
	backgroundMusic->Play();

	int valor = objectArray.size();
	for (int i = 0; i < valor; i++)
	{

		objectArray[i]->Start();
	};

	started = true;
}

void StageState::Pause() {}

void StageState::Resume() {}