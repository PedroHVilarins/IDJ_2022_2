#ifndef STAGESTATE_H
#define STAGESTATE_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "music.h"
#include "sprite.h"
#include "gameobject.h"
#include "state.h"
#include "sound.h"
#include "vec2.h"
#include "tilemap.h"
#include <string>
#include <array>
#include <memory>
#include <vector>

using namespace std;

class StageState : public State
{

public:
    StageState();
    ~StageState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();

private:
    TileSet *tileSet;
    Music *backgroundMusic;
};

#endif