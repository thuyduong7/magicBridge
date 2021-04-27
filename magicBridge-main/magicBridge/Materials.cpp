#include "Materials.h"
#include "Yolk.h"
#include "Enemy.h"
#include "Coin.h"
#include "Button.h"

//Background
SDL_Texture* backgroundTexture;
SDL_Texture* backgroundLayer1Texture;
SDL_Texture* backgroundLayer2Texture;
SDL_Texture* backgroundLayer3Texture;
SDL_Texture* backgroundLayer4Texture;
SDL_Texture* backgroundLayer5Texture;
SDL_Texture* introTexture;
SDL_Rect introSprite[TOTAL_INTRO_SPRITE];

//Button
SDL_Texture* startButtonTexture;
SDL_Rect startButtonSprite[TOTAL_BUTTON_SPRITE];
SDL_Texture* helpButtonTexture;
SDL_Rect helpButtonSprite[TOTAL_BUTTON_SPRITE];
SDL_Texture* pauseButtonTexture;
SDL_Rect pauseButtonSprite[TOTAL_BUTTON_SPRITE];
SDL_Texture* continueButtonTexture;
SDL_Rect continueButtonSprite[TOTAL_BUTTON_SPRITE];
SDL_Texture* quitButtonTexture;
SDL_Rect quitButtonSprite[TOTAL_BUTTON_SPRITE];

//Bridge
SDL_Texture* dot;

//Characters
SDL_Texture* yolkTexture;
SDL_Rect yolkIdle[TOTAL_YOLK_IDLE_SPRITE];
SDL_Rect yolkRun1[TOTAL_YOLK_RUN_SPRITE];
SDL_Rect yolkRun2[TOTAL_YOLK_RUN_SPRITE];
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
    //Load background texture
    backgroundTexture = loadFromFile("Assets/Background/Background.png", renderer);
    if (backgroundTexture == NULL){
        cout << "Fail to load background\n";
        return false;
    }

    backgroundLayer1Texture = loadFromFile("Assets/Background/BackgroundLayer1.png", renderer);
    if (backgroundLayer1Texture == NULL){
        cout << "Fail to load background layer 1\n";
        return false;
    }

    backgroundLayer2Texture = loadFromFile("Assets/Background/BackgroundLayer2.png", renderer);
    if (backgroundLayer2Texture == NULL){
        cout << "Fail to load background layer 2\n";
        return false;
    }

    backgroundLayer3Texture = loadFromFile("Assets/Background/BackgroundLayer3.png", renderer);
    if (backgroundLayer3Texture == NULL){
        cout << "Fail to load background layer 3\n";
        return false;
    }

    backgroundLayer4Texture = loadFromFile("Assets/Background/BackgroundLayer4.png", renderer);
    if (backgroundLayer4Texture == NULL){
        cout << "Fail to load background layer 4\n";
        return false;
    }

    backgroundLayer5Texture = loadFromFile("Assets/Background/BackgroundLayer5.png", renderer);
    if (backgroundLayer5Texture == NULL){
        cout << "Fail to load background layer 5\n";
        return false;
    }

    introTexture = loadFromFile("Assets/Background/Intro.png", renderer);
    if (introTexture == NULL){
        cout << "Fail to load intro texture\n";
        return false;
    }
    for (int i = 0; i < TOTAL_INTRO_SPRITE; i++){
        introSprite[i].x = SCREEN_WIDTH * i;
        introSprite[i].y = 0;
        introSprite[i].w = SCREEN_WIDTH;
        introSprite[i].h = SCREEN_HEIGHT;
    }

    //Load buttons
    startButtonTexture = loadFromFile("Assets/Buttons/Start.png", renderer);
    if (startButtonTexture == NULL){
        cout << "Fail to load start button\n";
        return false;
    }
    for (int i = 0; i < TOTAL_BUTTON_SPRITE; i++){
        startButtonSprite[i].x = START_BUTTON_WIDTH * i;
        startButtonSprite[i].y = 0;
        startButtonSprite[i].w = START_BUTTON_WIDTH;
        startButtonSprite[i].h = START_BUTTON_HEIGHT;
    }

    helpButtonTexture = loadFromFile("Assets/Buttons/Help.png", renderer);
    if (helpButtonTexture == NULL){
        cout << "Fail to load help button\n";
        return false;
    }
    for (int i = 0; i < TOTAL_BUTTON_SPRITE; i++){
        helpButtonSprite[i].x = HELP_BUTTON_WIDTH * i;
        helpButtonSprite[i].y = 0;
        helpButtonSprite[i].w = HELP_BUTTON_WIDTH;
        helpButtonSprite[i].h = HELP_BUTTON_HEIGHT;
    }

    pauseButtonTexture = loadFromFile("Assets/Buttons/Pause.png", renderer);
    if (pauseButtonTexture == NULL){
        cout << "Fail to load pause button\n";
        return false;
    }
    for (int i = 0; i < TOTAL_BUTTON_SPRITE; i++){
        pauseButtonSprite[i].x = PAUSE_BUTTON_WIDTH * i;
        pauseButtonSprite[i].y = 0;
        pauseButtonSprite[i].w = PAUSE_BUTTON_WIDTH;
        pauseButtonSprite[i].h = PAUSE_BUTTON_HEIGHT;
    }

    continueButtonTexture = loadFromFile("Assets/Buttons/Continue.png", renderer);
    if (continueButtonTexture == NULL){
        cout << "Fail to load continue button\n";
        return false;
    }
    for (int i = 0; i < TOTAL_BUTTON_SPRITE; i++){
        continueButtonSprite[i].x = CONTINUE_BUTTON_WIDTH * i;
        continueButtonSprite[i].y = 0;
        continueButtonSprite[i].w = CONTINUE_BUTTON_WIDTH;
        continueButtonSprite[i].h = CONTINUE_BUTTON_HEIGHT;
    }

    quitButtonTexture = loadFromFile("Assets/Buttons/Quit.png", renderer);
    if (quitButtonTexture == NULL){
        cout << "Fail to load quit button\n";
        return false;
    }
    for (int i = 0; i < TOTAL_BUTTON_SPRITE; i++){
        quitButtonSprite[i].x = QUIT_BUTTON_WIDTH * i;
        quitButtonSprite[i].y = 0;
        quitButtonSprite[i].w = QUIT_BUTTON_WIDTH;
        quitButtonSprite[i].h = QUIT_BUTTON_HEIGHT;
    }

    //Load dot texture
    dot = loadFromFile("Assets/Dot.png", renderer);
    if (dot == NULL){
        cout << "Fail to load dot\n";
        return false;
    }
    //Load yolk texture
    yolkTexture = loadFromFile("Assets/Cat.png", renderer);
    if (yolkTexture == NULL){
        cout << "Fail to load Yolk\n";
        return false;
    }
    //Set yolk sprite
    for (int i = 0; i < TOTAL_YOLK_IDLE_SPRITE; i++){
        yolkIdle[i].x = YOLK_WIDTH * i;
        yolkIdle[i].y = 0;
        yolkIdle[i].w = YOLK_WIDTH;
        yolkIdle[i].h = YOLK_HEIGHT;
    }

    yolkDie.x = 0;
    yolkDie.y = YOLK_HEIGHT;
    yolkDie.w = YOLK_WIDTH;
    yolkDie.h = YOLK_HEIGHT;

    for (int i = 0; i < TOTAL_YOLK_RUN_SPRITE; i++){
        yolkRun1[i].x = YOLK_WIDTH * i;
        yolkRun1[i].y = YOLK_HEIGHT*2;
        yolkRun1[i].w = YOLK_WIDTH;
        yolkRun1[i].h = YOLK_HEIGHT;
    }
    for (int i = 0; i < TOTAL_YOLK_RUN_SPRITE; i++){
        yolkRun2[i].x = YOLK_WIDTH * i;
        yolkRun2[i].y = YOLK_HEIGHT*3;
        yolkRun2[i].w = YOLK_WIDTH;
        yolkRun2[i].h = YOLK_HEIGHT;
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
        newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
        SDL_FreeSurface(loadSurface);
    }
    return newTexture;
}

SDL_Texture* Materials::getTexture(MAT_TYPE type)
{
    switch (type){
        case BACKGROUND:
            return backgroundTexture;
        case BACKGROUNDLAYER1:
            return backgroundLayer1Texture;
        case BACKGROUNDLAYER2:
            return backgroundLayer2Texture;
        case BACKGROUNDLAYER3:
            return backgroundLayer3Texture;
        case BACKGROUNDLAYER4:
            return backgroundLayer4Texture;
        case BACKGROUNDLAYER5:
            return backgroundLayer5Texture;
        case INTRO:
            return introTexture;

        case START_BUTTON:
            return startButtonTexture;
        case HELP_BUTTON:
            return helpButtonTexture;
        case PAUSE_BUTTON:
            return pauseButtonTexture;
        case CONTINUE_BUTTON:
            return continueButtonTexture;
        case QUIT_BUTTON:
            return quitButtonTexture;

        case BRIDGE:
            return dot;
        case YOLK:
            return yolkTexture;

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
        case INTRO:
            return introSprite[i];

        case START_BUTTON:
            return startButtonSprite[i];
        case HELP_BUTTON:
            return helpButtonSprite[i];
        case PAUSE_BUTTON:
            return pauseButtonSprite[i];
        case CONTINUE_BUTTON:
            return continueButtonSprite[i];
        case QUIT_BUTTON:
            return quitButtonSprite[i];

        case YOLK:
            switch (_type)
            {
                case IDLE:
                    return yolkIdle[i];
                case RUN:
                    return yolkRun1[i];
                case HIT:
                    return yolkRun2[i];
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

void Materials::setAlpha(SDL_Texture* _texture, Uint8 alpha)
{
    SDL_SetTextureAlphaMod(_texture, alpha);
}

void Materials::render(SDL_Renderer* renderer, SDL_Texture* _texture, SDL_Rect scrRect, SDL_Rect dstRect,
                       SDL_RendererFlip flip, double angle, SDL_Point* center)
{
    SDL_RenderCopyEx(renderer, _texture, &scrRect, &dstRect, angle, center, flip);
}

void Materials::free()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(backgroundLayer1Texture);
    SDL_DestroyTexture(backgroundLayer2Texture);
    SDL_DestroyTexture(backgroundLayer3Texture);
    SDL_DestroyTexture(backgroundLayer4Texture);
    SDL_DestroyTexture(backgroundLayer5Texture);
    SDL_DestroyTexture(introTexture);

    SDL_DestroyTexture(startButtonTexture);
    SDL_DestroyTexture(helpButtonTexture);
    SDL_DestroyTexture(pauseButtonTexture);
    SDL_DestroyTexture(continueButtonTexture);
    SDL_DestroyTexture(quitButtonTexture);

    SDL_DestroyTexture(dot);
    SDL_DestroyTexture(yolkTexture);

    SDL_DestroyTexture(radish);
    SDL_DestroyTexture(spike);
    SDL_DestroyTexture(bird);
    SDL_DestroyTexture(spikeBall);
    SDL_DestroyTexture(coin);
}
