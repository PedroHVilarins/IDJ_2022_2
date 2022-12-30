#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
using namespace std;

#include "state.h"

class Game
{

public:
    void Run();
    SDL_Renderer *GetRenderer();
    State &GetState();
    static Game &GetInstance();
    ~Game();
    float GetDeltaTime();

private:
    Game(string title, int width, int height);
    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *state;
    void CalculateDeltaTime();
    float dt;
    int frameStart;
};

#endif
