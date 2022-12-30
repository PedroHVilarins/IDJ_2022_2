#ifndef STATE_H
#define STATE_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>

#include <array>
#include <memory>
using namespace std;

#include "music.h"
#include "sprite.h"
#include "gameobject.h"
#include "face.h"
#include "sound.h"
#include "vec2.h"

class State
{
public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Input();
    void AddObject(int mouseX, int mouseY);

private:
    Sprite *bg;
    Music music;
    bool quitRequested;
    vector<unique_ptr<GameObject>> objectArray;
};

#endif