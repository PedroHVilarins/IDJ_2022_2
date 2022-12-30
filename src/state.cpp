#include "state.h"
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

	TileSet *tile = new TileSet(64, 64, "./assets/img/tileset.png");

	TileMap *mapa = new TileMap(*objeto, "./assets/map/tileMap.txt", tile);
	objeto->AddComponent(bg);
	objeto->AddComponent(mapa);
	objectArray.emplace_back(objeto);

	objectArray.emplace_back(objeto);

	music = *new Music("./assets/audio/stageState.ogg");
}

void State::Update(float dt)
{

	Input();

	int valor = objectArray.size();

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

		objectArray[i]->Render();
	};
}

bool State::QuitRequested()
{

	return quitRequested;
}

void State::Input()
{
	SDL_Event event;
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);

	while (SDL_PollEvent(&event))
	{

		if (event.type == SDL_QUIT)
		{
			quitRequested = true;
		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{

			for (int i = objectArray.size() - 1; i >= 0; --i)
			{
				GameObject *go = (GameObject *)objectArray[i].get();

				if (go->box.Contains({(float)mouseX, (float)mouseY}))
				{
					Face *face = (Face *)go->GetComponent("Face");
					if (nullptr != face)
					{

						face->Damage(rand() % 10 + 10);

						break;
					}
				}
			}
		}
		if (event.type == SDL_KEYDOWN)
		{

			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				quitRequested = true;
			}
			else
			{
				Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY)
{

	GameObject *objeto = new GameObject();

	Sprite *penguin = new Sprite(*objeto, "./assets/img/penguinface.png");
	objeto->box.x = mouseX - (penguin->GetWidth()) / 2;
	objeto->box.y = mouseY - (penguin->GetHeight()) / 2;

	objeto->AddComponent(penguin);

	Sound *som = new Sound(*objeto, "./assets/audio/boom.wav");

	objeto->AddComponent(som);

	Face *inimigo = new Face(*objeto);

	objeto->AddComponent(inimigo);

	objectArray.emplace_back(objeto);
}