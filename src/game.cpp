#define GAME_TITLE "Pedro Henrique Da Costa Vilarins 18/0114441"
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600
#define WINDOW_DELAY 33

#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#include "game.h"
#include "inputmanager.h"
#include "resources.h"
#include "text.h"
#include <cstdlib>
#include <ctime>

#include <chrono>

Game *Game::instance = nullptr;
stack<unique_ptr<State>> Game::stateStack;

Game &Game::GetInstance()
{

    if (instance == nullptr)
    {
        new Game(GAME_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
    };

    return *instance;
}

Game::Game(string title, int width, int height)
{

    frameStart = SDL_GetTicks();
    dt = 0;
    srand(time(NULL));
    if (instance == nullptr)
    {
        instance = this;
    };

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        SDL_Log("Ocorreu um erro: %s", SDL_GetError());
    };

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
    {
        SDL_Log("Ocorreu um erro: %s", SDL_GetError());
    };

    if (Mix_Init(MIX_INIT_OGG) == 0)
    {
        SDL_Log("Ocorreu um erro: %s", SDL_GetError());
    };
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, WINDOW_WIDTH);
    Mix_AllocateChannels(32);

    if (TTF_Init() != 0)
    {
        SDL_Log("Ocorreu um erro: %s", SDL_GetError());
    }

    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    int index = -1;

    renderer = SDL_CreateRenderer(window, index, SDL_RENDERER_ACCELERATED);

    storedState = nullptr;
}

Game::~Game()
{

    if (storedState != nullptr)
    {

        delete (storedState);
    }

    while (stateStack.empty() == false)
    {
        stateStack.pop();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

State &Game::GetCurrentState()
{

    return *stateStack.top();
}

SDL_Renderer *Game::GetRenderer()
{

    return renderer;
}

void Game::Push(State *state)
{

    storedState = state;
}

void Game::Run()
{

    if (storedState != nullptr)
    {
        stateStack.emplace(storedState);
        storedState = nullptr;
        stateStack.top()->Start();
    }
    else
    {
        exit(0);
    }

    while ((stateStack.top()->QuitRequested() == false) and (stateStack.empty() == false))
    {

        if (stateStack.top()->PopRequested() == true)
        {
            stateStack.top()->Pause();
            stateStack.pop();
            if (stateStack.empty() == false)
            {
                stateStack.top()->Resume();
            }
        }

        if (storedState != nullptr)
        {
            stateStack.top()->Pause();
            stateStack.emplace(storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }

        chrono::high_resolution_clock clock;
        chrono::high_resolution_clock::time_point start = clock.now();

        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        stateStack.top()->Update(GetDeltaTime());
        stateStack.top()->Render();
        SDL_RenderPresent(renderer);

        chrono::high_resolution_clock::time_point end = clock.now();

        chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(end - start);

        if (ms.count() <= WINDOW_DELAY)
            SDL_Delay(WINDOW_DELAY - ms.count());
    };

    while (stateStack.empty() == false)
    {
        stateStack.pop();
    }
    Resources::ClearImage();
    Resources::ClearSounds();
    Resources::ClearMusic();
}

void Game::CalculateDeltaTime()
{

    int temp = frameStart;
    frameStart = SDL_GetTicks();
    dt = (frameStart - temp) / 1000.0;
}

float Game::GetDeltaTime()
{

    return dt;
}
