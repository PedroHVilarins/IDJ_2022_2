#define GAME_TITLE "Pedro Henrique Da Costa Vilarins 18/0114441"
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600
#define WINDOW_DELAY 33
#define WINDOW_FLAG 0
// #define WINDOW_FLAG SDL_WINDOW_MAXIMIZED

#include "game.h"

Game *Game::instance;

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

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == 0)
    {
        window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAG);
    }

    if (window)
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    state = new State();
}

Game::~Game()
{
    delete state;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

State &Game::GetState()
{
    return *state;
}

SDL_Renderer *Game::GetRenderer()
{
    return renderer;
}

void Game::Run()
{
    while (state->QuitRequested() == false)
    {
        state->Update(3);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(WINDOW_DELAY);
    };
    Game::~Game();
}
