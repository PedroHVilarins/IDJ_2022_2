#ifndef GAME_H
#define GAME_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>
#include <memory>
#include <stack>
#include "state.h"
#include "titlestate.h"

using namespace std;

class Game
{

public:
    Game(string title, int width, int height);
    ~Game();

    static Game &GetInstance();
    SDL_Renderer *GetRenderer();
    State &GetCurrentState();

    void Push(State *state);

    void Run();

    float GetDeltaTime();

private:
    void CalculateDeltaTime();

    float dt;
    int frameStart;

    static Game *instance;

    State *storedState;
    SDL_Window *window;
    SDL_Renderer *renderer;
    static stack<unique_ptr<State>> stateStack;
};

#endif
