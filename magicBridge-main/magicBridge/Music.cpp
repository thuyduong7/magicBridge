#include "Music.h"

#include <iostream>

using namespace std;

bool Music::loadMusic()
{
    bool success = true;
    themeSongStart = Mix_LoadMUS("Music/initial.wav");
    if(themeSongStart == NULL)
    {
        cout << "Failed to load start theme song! SDL_mixer Error: " << Mix_GetError();
        success = false;
    }
    themeSong = Mix_LoadMUS("Music/themeSong.wav");
    if(themeSong == NULL)
    {
        cout << "Failed to load theme song! SDL_mixer Error: " << Mix_GetError();
        success = false;
    }

    //Load sound effects
    moveBridge = Mix_LoadWAV( "Music/moveBridge.wav" );
    if( moveBridge == NULL )
    {
        cout << "Failed to load move bridge sound effect! SDL_mixer Error: " << Mix_GetError();
        success = false;
    }

    pressStart = Mix_LoadWAV( "Music/pressStart.wav" );
    if( moveBridge == NULL )
    {
        cout << "Failed to load press start effect! SDL_mixer Error: " << Mix_GetError();
        success = false;
    }

    click = Mix_LoadWAV( "Music/click.wav" );
    if( click == NULL )
    {
        cout << "Failed to load click effect! SDL_mixer Error: " << Mix_GetError();
        success = false;
    }

    hit = Mix_LoadWAV( "Music/hit.wav" );
    if( hit == NULL )
    {
        cout << "Failed to load hit effect! SDL_mixer Error: " << Mix_GetError();
        success = false;
    }

    eatCoin = Mix_LoadWAV( "Music/eatCoin.wav" );
    if( eatCoin == NULL )
    {
        cout << "Failed to load eat coin effect! SDL_mixer Error: " << Mix_GetError();
        success = false;
    }

    die = Mix_LoadWAV( "Music/die.wav" );
    if( click == NULL )
    {
        cout << "Failed to load die effect! SDL_mixer Error: " << Mix_GetError();
        success = false;
    }

    showScore = Mix_LoadWAV( "Music/showScore.wav" );
    if( showScore == NULL )
    {
        cout << "Failed to load show score effect! SDL_mixer Error: " << Mix_GetError();
        success = false;
    }

    return success;
}

void Music::free()
{
    //Free the sound effects
	Mix_FreeChunk(moveBridge);
	Mix_FreeChunk(pressStart);
	Mix_FreeChunk(click);
	Mix_FreeChunk(hit);
	Mix_FreeChunk(eatCoin);
	Mix_FreeChunk(die);
	Mix_FreeChunk(showScore);
    moveBridge = NULL;
    pressStart = NULL;
    click = NULL;
    hit = NULL;
    eatCoin = NULL;
    die = NULL;

	//Free the music
	Mix_FreeMusic(themeSongStart);
	Mix_FreeMusic(themeSong);
	themeSong = NULL;
}
