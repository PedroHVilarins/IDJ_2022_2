#ifndef STATE_H
#define STATE_H

#include "music.h"
#include "sprite.h"
#include <string>

class State
{

public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

private:
    Sprite bg;
    Music music;
    bool quitRequested;
};

#endif