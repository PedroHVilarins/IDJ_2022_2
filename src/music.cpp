#include "music.h"

Music::Music()
{

    music = nullptr;
}

Music::Music(string file)
{

    music = nullptr;
    Open(file);
}

void Music::Play(int times)
{

    Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop)
{

    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file)
{

    const char *c = file.c_str();
    music = Mix_LoadMUS(c);
}

bool Music::IsOpen()
{

    if (music != NULL)
    {
        return true;
    };

    return false;
}

Music::~Music()
{

    Stop();
    Mix_FreeMusic(music);
}