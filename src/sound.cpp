#include "sound.h"
#include "resources.h"

Sound::Sound(GameObject &associated) : Component(associated)
{

    chunk = nullptr;
}

Sound::Sound(GameObject &associated, string file) : Component(associated)
{

    Open(file);
}

void Sound::Play(int times)
{

    channel = Mix_PlayChannel(-1, chunk, times - 1);
}

void Sound::Stop()
{

    if (chunk != nullptr)
    {
        Mix_HaltChannel(channel);
    };
}

void Sound::Open(string file)
{

    chunk = Resources::GetSound(file);
}

Sound::~Sound()
{

    if (chunk != nullptr)
    {

        Mix_HaltChannel(channel);
    };

    Mix_FreeChunk(chunk);
}

bool Sound::IsOpen()
{

    if (chunk == nullptr)
    {
        return false;
    };

    return true;
}

void Sound::Update(float dt) {}

void Sound::Render() {}

bool Sound::Is(string type)
{

    if (type == "sound")
    {
        return true;
    };
    return false;
}
