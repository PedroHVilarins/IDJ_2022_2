#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <unordered_map>
using namespace std;

class Resources
{

public:
    static SDL_Texture *GetImage(string file);
    static void ClearImage();
    static Mix_Music *GetMusic(string file);
    static void ClearMusic();
    static Mix_Chunk *GetSound(string file);
    static void ClearSounds();

private:
    static unordered_map<string, SDL_Texture *> imageTable;
    static unordered_map<string, Mix_Music *> musicTable;
    static unordered_map<string, Mix_Chunk *> soundTable;
};

#endif