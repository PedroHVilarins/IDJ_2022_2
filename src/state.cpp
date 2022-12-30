#include "state.h"

State::State()
{
    quitRequested = false;
    LoadAssets();
    music.Play();
}

void State::LoadAssets()
{
    bg = *new Sprite("./assets/img/ocean.jpg");
    music = *new Music("./assets/audio/stageState.ogg");
}

void State::Update(float dt)
{
    bool valor = SDL_QuitRequested();

    if (valor == true)
    {
        quitRequested = true;
    }
}

void State::Render()
{
    bg.Render(0, 0);
}

bool State::QuitRequested()
{
    return quitRequested;
}
