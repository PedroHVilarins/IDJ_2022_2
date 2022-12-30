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

#include <array>
#include <memory>
#include <vector>

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
    void AddObject(int mouseX, int mouseY);

    void Start();
    weak_ptr<GameObject> AddObject(GameObject *go);
    weak_ptr<GameObject> GetObjectPtr(GameObject *go);

private:
    Sprite *bg;
    Music music;
    bool quitRequested;
    vector<shared_ptr<GameObject>> objectArray;

    bool started;
};

#endif