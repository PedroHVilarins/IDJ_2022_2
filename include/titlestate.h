#ifndef TITLESTATE_H
#define TITLESTATE_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "music.h"
#include "sprite.h"
#include "gameobject.h"
#include "state.h"
#include "sound.h"
#include "vec2.h"
#include <string>
#include <array>
#include <memory>
#include <vector>

using namespace std;

class TitleState : public State
{

public:
    TitleState();
    ~TitleState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();

private:
    Timer *timer;
    float cooldown;
};

#endif