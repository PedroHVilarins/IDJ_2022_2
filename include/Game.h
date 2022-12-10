#ifndef GAME_H
#define GAME_H

#include <string>
#include "State.h"
using namespace std;

class Game{
private:    
    Game(
        string title,
        int width,
        int height
    );
public:
    ~Game();
    
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
private:
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
};

Game::Game(string title, int width, int height)
{
}

Game::~Game()
{
}

#endif
