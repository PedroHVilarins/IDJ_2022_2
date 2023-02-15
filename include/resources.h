#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>
#include <unordered_map>
#include <memory>
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL
#include "SDL_include.h"

using namespace std;

class Resources
{

public:
    static shared_ptr<SDL_Texture> GetImage(string file);
    static void ClearImage();
    static shared_ptr<Mix_Music> GetMusic(string file);
    static void ClearMusic();
    static shared_ptr<Mix_Chunk> GetSound(string file);
    static void ClearSounds();
    static shared_ptr<TTF_Font> GetFont(string file, int size);
    static void ClearFont();

private:
    static unordered_map<string, shared_ptr<SDL_Texture>> imageTable;
    static unordered_map<string, shared_ptr<Mix_Music>> musicTable;
    static unordered_map<string, shared_ptr<Mix_Chunk>> soundTable;
    static unordered_map<string, shared_ptr<TTF_Font>> fontTable;
};

#endif