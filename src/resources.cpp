#include "resources.h"
#include <string>
#include "game.h"

unordered_map<string, shared_ptr<Mix_Chunk>> Resources::soundTable;
unordered_map<string, shared_ptr<Mix_Music>> Resources::musicTable;
unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string, shared_ptr<TTF_Font>> Resources::fontTable;

shared_ptr<SDL_Texture> Resources::GetImage(string file)
{

    if (imageTable.find(file) != imageTable.end())
    {

        return imageTable[file];
    }

    const char *c = file.c_str();
    SDL_Texture *temp = IMG_LoadTexture(Game::GetInstance().GetRenderer(), c);
    if (temp != nullptr)
    {
        imageTable[file] = shared_ptr<SDL_Texture>(temp, [](SDL_Texture *ptr)
                                                   { SDL_DestroyTexture(ptr); });

        return imageTable[file];
    }

    return nullptr;
}

void Resources::ClearImage()
{

    for (auto i = imageTable.begin(); i != imageTable.end(); i++)
    {

        if (i->second.unique() == true)
        {
            imageTable.erase(i);
        }
    }
}

shared_ptr<Mix_Music> Resources::GetMusic(string file)
{

    if (musicTable.find(file) != musicTable.end())
    {

        return musicTable[file];
    }

    const char *c = file.c_str();
    Mix_Music *temp = Mix_LoadMUS(c);

    if (temp != nullptr)
    {

        musicTable[file] = shared_ptr<Mix_Music>(temp, [](Mix_Music *ptr)
                                                 { Mix_FreeMusic(ptr); });
        return musicTable[file];
    }

    return nullptr;
}

void Resources::ClearMusic()
{

    for (auto i = musicTable.begin(); i != musicTable.end(); i++)
    {

        if (i->second.unique() == true)
        {
            musicTable.erase(i);
        }
    }
}

shared_ptr<Mix_Chunk> Resources::GetSound(string file)
{

    if (soundTable.find(file) != soundTable.end())
    {

        return soundTable[file];
    }

    const char *c = file.c_str();
    Mix_Chunk *temp = Mix_LoadWAV(c);

    if (temp != nullptr)
    {

        soundTable[file] = shared_ptr<Mix_Chunk>(temp, [](Mix_Chunk *ptr)
                                                 { Mix_FreeChunk(ptr); });
        ;
        return soundTable[file];
    }

    return nullptr;
}

void Resources::ClearSounds()
{

    for (auto i = soundTable.begin(); i != soundTable.end(); i++)
    {

        if (i->second.unique() == true)
        {
            soundTable.erase(i);
        }
    }
}

shared_ptr<TTF_Font> Resources::GetFont(string file, int size)
{

    if (fontTable.find(file + to_string(size)) != fontTable.end())
    {

        return fontTable[file + to_string(size)];
    }

    const char *c = file.c_str();
    TTF_Font *temp = TTF_OpenFont(c, size);

    if (temp != nullptr)
    {
        fontTable[file + to_string(size)] = shared_ptr<TTF_Font>(temp, [](TTF_Font *ptr)
                                                                 { TTF_CloseFont(ptr); });

        return fontTable[file + to_string(size)];
    }

    return nullptr;
}

void Resources::ClearFont()
{

    for (auto i = fontTable.begin(); i != fontTable.end(); i++)
    {

        if (i->second.unique() == true)
        {
            fontTable.erase(i);
        }
    }
}