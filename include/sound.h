#ifndef SOUND_H
#define SOUND_H

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
using namespace std;

#include "component.h"

class Sound : public Component
{
public:
    Sound(GameObject &associated);
    Sound(GameObject &associated, string file);
    ~Sound();
    void Play(int times = 1);
    void Stop();
    void Open(string file);
    bool IsOpen();

    void Update(float dt);
    void Render();
    bool Is(string type);

private:
    Mix_Chunk *chunk;
    int channel;
};

#endif