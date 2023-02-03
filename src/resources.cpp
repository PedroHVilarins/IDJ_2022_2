#include "resources.h"
#include <string>
#include "game.h"

unordered_map<string, Mix_Chunk *> Resources::soundTable;
unordered_map<string, Mix_Music *> Resources::musicTable;
unordered_map<string, SDL_Texture *> Resources::imageTable;

SDL_Texture *Resources::GetImage(string file)
{

    if (imageTable.find(file) != imageTable.end())
    {

        return imageTable[file];
    }

    const char *c = file.c_str();
    imageTable[file] = IMG_LoadTexture(Game::GetInstance().GetRenderer(), c);

    return imageTable[file];
}

void Resources::ClearImage()
{

    imageTable.erase(imageTable.begin(), imageTable.end());
}

Mix_Music *Resources::GetMusic(string file)
{

    if (musicTable.find(file) != musicTable.end())
    {

        return musicTable[file];
    }

    const char *c = file.c_str();
    musicTable[file] = Mix_LoadMUS(c);

    return musicTable[file];
}

void Resources::ClearMusic()
{

    musicTable.erase(musicTable.begin(), musicTable.end());
}

Mix_Chunk *Resources::GetSound(string file)
{

    if (soundTable.find(file) != soundTable.end())
    {

        return soundTable[file];
    }

    const char *c = file.c_str();
    soundTable[file] = Mix_LoadWAV(c);

    return soundTable[file];
}

void Resources::ClearSounds()
{

    soundTable.erase(soundTable.begin(), soundTable.end());
}