#ifndef STATE_H
#define STATE_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "music.h"
#include "sprite.h"
#include "gameobject.h"
#include "sound.h"
#include "vec2.h"
#include "tilemap.h"
#include <string>
#include <array>
#include <memory>
#include <vector>

using namespace std;

class State
{

public:
    State();
    virtual ~State();

    virtual void LoadAssets() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

    void virtual Start() = 0;
    void virtual Pause() = 0;
    void virtual Resume() = 0;

    virtual weak_ptr<GameObject> AddObject(GameObject *go);
    virtual weak_ptr<GameObject> GetObjectPtr(GameObject *go);

    bool QuitRequested();
    bool PopRequested();

protected:
    void StartArray();
    void virtual UpdateArray(float dt);
    void virtual RenderArray();

    bool quitRequested;
    vector<shared_ptr<GameObject>> objectArray;
    bool started;
    bool popRequested;
};

#endif