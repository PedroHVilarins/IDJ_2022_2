#ifndef MUSIC_H
#define MUSIC_H

class Music
{
private:
    Mix_Music* music;
public:
    Music();
    Music(string file);
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(string file);
    bool IsOpen();
};

Music::Music()
{
}




#endif