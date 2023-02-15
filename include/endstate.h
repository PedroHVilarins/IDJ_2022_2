#ifndef ENDSTATE_H
#define ENDSTATE_H

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

class EndState : public State
{

public:
    EndState();
    ~EndState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();

private:
    Music *backgroundMusic;
};

#endif