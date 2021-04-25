#ifndef MUSIC_H
#define MUSIC_H

#include <SDL_mixer.h>
#include "Yolk.h"

struct Music
{
    bool loadMusic();
    bool getMusic(STATE state);
    void free();

    //The music that will be played
    Mix_Music *themeSong = NULL;

    //The sound effects that will be used
    Mix_Chunk* moveBridge = NULL;
    Mix_Chunk* pressStart = NULL;
    Mix_Chunk* click = NULL;
    Mix_Chunk* hit = NULL;
    Mix_Chunk* eatCoin = NULL;
    Mix_Chunk* die = NULL;
};

#endif // MUSIC_H
