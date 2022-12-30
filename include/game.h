#ifndef GAME_H
#define GAME_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>
#include "state.h"

using namespace std;

class Game
{

public:
    void Run();
    SDL_Renderer *GetRenderer();
    State &GetState();
    static Game &GetInstance();
    ~Game();

private:
    Game(string title, int width, int height);
    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *state;
};

#endif
