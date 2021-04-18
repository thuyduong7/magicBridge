#include "Materials.h"
#include "Yolk.h"
#include "Enemy.h"
#include "Coin.h"

SDL_Texture* background;
SDL_Texture* backgroundLayer;

SDL_Texture* dot;

SDL_Texture* yolk;
SDL_Rect yolkIdle;
SDL_Rect yolkRun[TOTAL_YOLK_RUN_SPRITE];
SDL_Rect yolkDie;

SDL_Texture* radish;
SDL_Rect radishSprite[TOTAL_RADISH_SPRITE];

SDL_Texture* spike;
SDL_Rect spikeSprite[TOTAL_SPIKE_SPRITE];

SDL_Texture* bird;
SDL_Rect birdSprite[TOTAL_BIRD_SPRITE];

SDL_Texture* spikeBall;

SDL_Texture* coin;
SDL_Rect coinSprite[TOTAL_COIN_SPRITE];

bool Materials::load(SDL_Renderer* renderer)
{
    //Load dot texture
    dot = loadFromFile("Assets/Dot1.png", renderer);
    if (dot == NULL){
        cout << "Fail to load dot\n";
        return false;
    }
    //Load yolk texture
    yolk = loadFromFile("Assets/catSprite.png", renderer);
    if (yolk == NULL){
        cout << "Fail to load Yolk\n";
        return false;
    }
    //Set yolk sprite
    yolkIdle.x = 0;
    yolkIdle.y = 0;
    yolkIdle.w = YOLK_WIDTH;
    yolkIdle.h = YOLK_HEIGHT;

    yolkDie.x = 0;
    yolkDie.y = YOLK_HEIGHT;
    yolkDie.w = YOLK_WIDTH;
    yolkDie.h = YOLK_HEIGHT;

    for (int i = 0; i < TOTAL_YOLK_RUN_SPRITE; i++){
        yolkRun[i].x = YOLK_WIDTH * i;
        yolkRun[i].y = YOLK_HEIGHT*2;
        yolkRun[i].w = YOLK_WIDTH;
        yolkRun[i].h = YOLK_HEIGHT;
    }
    //Load background texture
    background = loadFromFile("Assets/design.png", renderer);
    if (background == NULL){
        cout << "Fail to load background\n";
        return false;
    }

    backgroundLayer = loadFromFile("Assets/BackgroundLayer1.png", renderer);
    if (backgroundLayer == NULL){
        cout << "Fail to load background layer\n";
        return false;
    }

    //Load radish texture
    radish = loadFromFile("Assets/Radish.png", renderer);
    if (radish == NULL){
        cout << "Fail to load Radish\n";
        return false;
    }
    //Set radish sprite
    for (int i = 0; i < TOTAL_RADISH_SPRITE; i++){
        radishSprite[i].x = RADISH_WIDTH * i;
        radishSprite[i].y = 0;
        radishSprite[i].w = RADISH_WIDTH;
        radishSprite[i].h = RADISH_HEIGHT;
    }
    //Load spike texture
    spike = loadFromFile("Assets/Spike.png", renderer);
    if (spike == NULL){
        cout << "Fail to load Spike\n";
        return false;
    }
    //Set spike sprite
    for (int i = 0; i < TOTAL_SPIKE_SPRITE; i++){
        spikeSprite[i].x = SPIKE_WIDTH * i;
        spikeSprite[i].y = 0;
        spikeSprite[i].w = SPIKE_WIDTH;
        spikeSprite[i].h = SPIKE_HEIGHT;
    }

    bird = loadFromFile("Assets/birdSprite.png", renderer);
    if (bird == NULL){
        cout << "Fail to load Spike\n";
        return false;
    }
    //Set bird sprite
    for (int i = 0; i < TOTAL_BIRD_SPRITE; i++){
        birdSprite[i].x = BIRD_WIDTH * i;
        birdSprite[i].y = 0;
        birdSprite[i].w = BIRD_WIDTH;
        birdSprite[i].h = BIRD_HEIGHT;
    }

    //Load spike ball texture
    spikeBall = loadFromFile("Assets/spikeBall.png", renderer);
    if (spikeBall == NULL){
        cout << "Fail to load Spike Ball\n";
        return false;
    }

    //Load coin texture
    coin = loadFromFile("Assets/Coin.png", renderer);
    if (coin == NULL){
        cout << "Fail to load Coin\n";
        return false;
    }
    for (int i = 0; i < TOTAL_COIN_SPRITE; i++){
        coinSprite[i].x = COIN_WIDTH * i;
        coinSprite[i].y = 0;
        coinSprite[i].w = COIN_WIDTH;
        coinSprite[i].h = COIN_HEIGHT;
    }
    return true;
}

SDL_Texture* Materials::loadFromFile(string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface != NULL){
        //SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 0xff, 0xff, 0xff));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
        SDL_FreeSurface(loadSurface);
    }
    return newTexture;
}


SDL_Texture* Materials::getTexture(MAT_TYPE type)
{
    switch (type){
        case BRIDGE:
            return dot;
        case YOLK:
            return yolk;
        case BACKGROUND:
            return background;
        case BACKGROUNDLAYER:
            return backgroundLayer;
        case RADISH:
            return radish;
        case SPIKE:
            return spike;
        case BIRD:
            return bird;
        case SPIKEBALL:
            return spikeBall;
        case COIN:
            return coin;
    }
}

SDL_Rect Materials::getSprite(MAT_TYPE type, SPRITE_TYPE _type, int i)
{
    switch (type)
    {
        case YOLK:
            switch (_type)
            {
                case IDLE:
                    return yolkIdle;
                case RUN:
                    return yolkRun[i];
                case DIE:
                    return yolkDie;
            }
        case RADISH:
            return radishSprite[i];
        case SPIKE:
            return spikeSprite[i];
        case BIRD:
            return birdSprite[i];
        case COIN:
            return coinSprite[i];
    }
}

void Materials::render(SDL_Renderer* renderer, SDL_Texture* _texture, SDL_Rect scrRect, SDL_Rect dstRect,
                       SDL_RendererFlip flip, double angle, SDL_Point* center)
{
    SDL_RenderCopyEx(renderer, _texture, &scrRect, &dstRect, angle, center, flip);
}

void Materials::free()
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(backgroundLayer);
    SDL_DestroyTexture(dot);
    SDL_DestroyTexture(yolk);
    SDL_DestroyTexture(radish);
    SDL_DestroyTexture(spike);
    SDL_DestroyTexture(bird);
    SDL_DestroyTexture(spikeBall);
    SDL_DestroyTexture(coin);
}
