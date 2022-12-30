#ifndef STATE_H
#define STATE_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "music.h"
#include "sprite.h"
#include "gameobject.h"
#include "face.h"
#include "sound.h"
#include "vec2.h"
#include "tilemap.h"
#include <string>
#include <array>
#include <memory>

using namespace std;

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