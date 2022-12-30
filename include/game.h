#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
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