#include "Game.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Background
Background* background;
Background* backgroundLayer1;
Background* backgroundLayer2;
Background* backgroundLayer3;
Background* backgroundLayer4;
Background* backgroundLayer5;
Background* backgroundLayer6;
Background* introBackground;

//Buttons
Button* startButton;
Button* helpButton;
Button* settingsButton;
Button* dayButton;
Button* nightButton;
Button* continueButton;
Button* quitButton;

// Objects
Bridge* bridge;
Yolk* yolk;
vector <Enemy*> enemy;
vector <Coin*> coins;

//Get the time to increase the speed of enemies
Timer timer;
//Use to render text
Text text;

//Set background
bool day, night;

//Multipliers of velocity
double mul;
int level, highScore;
MODE lastMode;
// The minimum distance between two enemies
int min_distance;

const int MIN_COIN_DISTANCE = SCREEN_HEIGHT/2;

//Colors of text
SDL_Color orange = {250,128,114};
SDL_Color blue = {100,149,237};
SDL_Color white = {255, 255, 255};

bool initGame()
{
    bool success = true;
    //Initialize background
    background = new Background(BACKGROUND);
    backgroundLayer1 = new Background(BACKGROUNDLAYER1);
    backgroundLayer2 = new Background(BACKGROUNDLAYER2);
    backgroundLayer3 = new Background(BACKGROUNDLAYER3);
    backgroundLayer4 = new Background(BACKGROUNDLAYER4);
    backgroundLayer5 = new Background(BACKGROUNDLAYER5);
    backgroundLayer6 = new Background(BACKGROUNDLAYER6);
    introBackground = new Background(INTRO);

    //Initialize buttons
    startButton = new Button(START_BUTTON);
    startButton->setPosition((SCREEN_WIDTH - START_BUTTON_WIDTH)/2, BRIDGE_IDLE_HEIGHT + 45);

    helpButton = new Button(HELP_BUTTON);
    helpButton->setPosition(SCREEN_WIDTH - QUIT_BUTTON_WIDTH - HELP_BUTTON_WIDTH - 10, 10);

    settingsButton = new Button(SETTINGS_BUTTON);
    settingsButton->setPosition
    (SCREEN_WIDTH - QUIT_BUTTON_WIDTH - HELP_BUTTON_WIDTH - PAUSE_BUTTON_WIDTH - 15, 10);

    dayButton = new Button(TICK_BUTTON);
    dayButton->setPosition(128,272);

    nightButton = new Button(TICK_BUTTON);
    nightButton->setPosition(128,396);

    continueButton = new Button(CONTINUE_BUTTON);

    quitButton = new Button(QUIT_BUTTON);
    quitButton->setPosition(SCREEN_WIDTH - QUIT_BUTTON_WIDTH - 5, 10);

    //Initialize bridge
    bridge = new Bridge [NUM_OF_DOTS];
    for (int i = 0; i < NUM_OF_DOTS; i++){
        bridge[i].posX = MIN_POS_X + i * DOT_WIDTH;
        bridge[i].posY = BRIDGE_IDLE_HEIGHT;
        if (bridge[i].texture == NULL) success = false;
    }

    // Set Yolk to stand on the bridge
    yolk = new Yolk((SCREEN_WIDTH - YOLK_WIDTH)/2, bridge[0].posY - YOLK_HEIGHT + STANDING_GAP);
    if (yolk->texture == NULL) success = false;

    // Set initial multiplier of velocity
    mul = 1;
    // Each level will have a particular multiplier of velocity
    level = 0;
    lastMode = START;
    //The initial minimum distance between two enemies
    min_distance = SCREEN_HEIGHT;
    // Get last high score
    ifstream score("Highscore.txt");
    score >> highScore;
    score.close();

    day = true;
    night = false;

    return success;
}

void handleEventStart(const SDL_Event& e, const Music& music, MODE& mode, bool& quit)
{
    startButton->handleEvent(e);
    settingsButton->handleEvent(e);
    helpButton->handleEvent(e);
    quitButton->handleEvent(e);
    if (startButton->click){
        Mix_PlayChannel(-1, music.pressStart, 0);
        SDL_Delay(200);
        mode = PLAYING;
        timer.start();
        Mix_PausedMusic();
        Mix_PlayMusic( music.themeSong, -1 );
    }
    if (settingsButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        mode = SETTINGS;
        lastMode = START;
    }
    if (helpButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        mode = HELP;
        lastMode = START;
    }
    if (quitButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        SDL_Delay(200);
        quit = true;
    }
}

void handleEventPlaying(const SDL_Event& e, const Music& music, MODE& mode, bool& quit)
{
    if (yolk->state == HIT_2){
        return;
    }
    //Handle mouse events
    settingsButton->handleEvent(e);
    helpButton->handleEvent(e);
    quitButton->handleEvent(e);
    if (settingsButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        lastMode = PLAYING;
        mode = SETTINGS;
        timer.pause();
    }
    if (helpButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        mode = HELP;
        lastMode = PLAYING;
    }
    if (quitButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        SDL_Delay(200);
        quit = true;
    }
    //Handle key events
    if (e.type == SDL_KEYDOWN){
        if (e.key.keysym.sym == SDLK_LEFT){
            bridge->dir = LEFT;
        }
        else if (e.key.keysym.sym == SDLK_RIGHT){
            bridge->dir = RIGHT;
        }
        if (bridge->move(bridge)) Mix_PlayChannel(-1, music.moveBridge, 0);
    }
    else if (e.type == SDL_KEYUP){
        if (e.key.keysym.sym == SDLK_LEFT){
            bridge->dir = TOTAL_OF_DIRECTION;
        }
        else if (e.key.keysym.sym == SDLK_RIGHT){
            bridge->dir = TOTAL_OF_DIRECTION;
        }
    }
}

void handleEventHelp(const SDL_Event& e, const Music& music, MODE& mode)
{
    continueButton->handleEvent(e);
    if (continueButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        continueButton->currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        if (lastMode == START) mode = START;
        else if (lastMode == PLAYING){
            mode = PLAYING;
            timer.unpause();
        }
    }
}

void handleEventSettings(const SDL_Event& e, const Music& music, MODE& mode)
{
    continueButton->handleEvent(e);
    dayButton->handleEvent(e);
    nightButton->handleEvent(e);
    if (continueButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        continueButton->currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        if (lastMode == START) mode = START;
        else if (lastMode == PLAYING){
            mode = PLAYING;
            timer.unpause();
        }
    }
    if (dayButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        day = true;
        night = false;
    }
    if (nightButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        day = false;
        night = true;
    }
}

void handleEventEnd(const SDL_Event& e, const Music& music, MODE& mode)
{
    continueButton->handleEvent(e);
    if (continueButton->click){
        Mix_PlayChannel(-1, music.showScore, 0);
        SDL_Delay(400);
        mode = START;
        //Free all remain enemies and coins
        for (vector <Enemy*>::iterator it = enemy.begin(); it != enemy.end();){
            it = enemy.erase(it);
        }
        for (vector <Coin*>::iterator it = coins.begin(); it != coins.end();){
            it = coins.erase(it);
        }
        initGame();
    }
}

void loop(const Music& music, MODE& mode)
{
    if (yolk->state == HIT_2){
        if (yolk->posY > SCREEN_HEIGHT){
            timer.stop();
            mode = END;
        }
        return;
    }
    if(Mix_PausedMusic() == 1) Mix_ResumeMusic();

    int chance = (rand() % 100) + 1;
    if ((( enemy.size() < 1) || ( (enemy.size() > 0) && (enemy[enemy.size()-1]->posY > min_distance) ))
        && (( coins.size() < 1) || ( (coins.size() > 0)
                                && (coins[coins.size()-1]->posY > 0))) ){
        if (chance > 75){
            enemy.push_back(new Radish);
            enemy[enemy.size()-1]->setPos();

        } else if (chance > 50){
            enemy.push_back(new Spike);
            enemy[enemy.size()-1]->setPos();

        } else if (chance > 25) {
            enemy.push_back(new Bird);
            enemy[enemy.size()-1]->setPos();

        } else if (chance > 1) {
            enemy.push_back(new SpikeBall);
            enemy[enemy.size()-1]->setPos();
        }
        if (min_distance > SCREEN_HEIGHT/3) min_distance -= SCREEN_HEIGHT/30;
    }
    if (( coins.size() < 1) || ( (coins.size() > 0)
                                && (coins[coins.size()-1]->posY > MIN_COIN_DISTANCE))){
        int coinChance = (rand() % 100);
        if (coinChance > 70){
            coins.push_back(new Coin);
            coins[coins.size()-1]->setPos(enemy);
        }
    }

    for (int i = 0; i < enemy.size(); i++){
        if (enemy[i]->checkCollision(yolk)){
            if (yolk->state == PLAY) Mix_PlayChannel(-1, music.hit, 0);
            else {
                Mix_PauseMusic();
                Mix_PlayChannel(-1, music.die, 0);
            }
            yolk->handleCollision();
            break;
        }
    }

    for (int i = 0; i < coins.size(); ){
        if (coins[i]->checkCollision(yolk)){
            coins.erase(coins.begin() + i);
            Mix_PlayChannel(-1, music.eatCoin, 0);
            yolk->score++;
        } else i++;
    }

    if (timer.getTicks() > 0 && (timer.getTicks() > (level+1)*5000)){
        level++;
        mul = (100 + level) / 100.00f;
    }
}

void update()
{
    if (yolk->state == HIT_2){
        return;
    }
    bridge->move(bridge);
    yolk->setDir(bridge[0].posY - BRIDGE_IDLE_HEIGHT);
    yolk->move(bridge);
    yolk->checkState();
    if ( (enemy.size() > 0) && ((enemy[0]->posY > SCREEN_HEIGHT) )){
        delete enemy[0];
        enemy.erase(enemy.begin());
    }
    if ( (coins.size() > 0) && ((coins[0]->posY > SCREEN_HEIGHT) )){
        delete coins[0];
        coins.erase(coins.begin());
    }
    for (int i = 0; i < enemy.size(); i++){
        enemy[i]->move(mul);
    }
    for (int i = 0; i < coins.size(); i++){
        coins[i]->move(mul);
    }
    background->move(mul);
    backgroundLayer5->move(mul);
}

void start(SDL_Renderer* renderer, const Music& music)
{
    if (Mix_PlayingMusic() == 0 || Mix_PausedMusic()){
        Mix_PlayMusic(music.themeSongStart, -1);
    }
    background->render(renderer);
    backgroundLayer5->render(renderer);
    introBackground->renderIntro(renderer);
    backgroundLayer1->render(renderer);

    yolk->render(renderer);
    for (int i = 0; i < NUM_OF_DOTS; i++){
        bridge[i].render(renderer);
    }

    if (text.loadText(renderer, to_string(highScore), 35, orange)){
            text.render(renderer,64,10);
    }
    if (text.loadText(renderer, "MAGIC", 63, blue)){
        text.render(renderer, 83, 90);
    }
    if (text.loadText(renderer, "BRIDGE!", 63, blue)){
        text.render(renderer, 43, 160);
    }

    startButton->render(renderer);
    settingsButton->render(renderer);
    helpButton->render(renderer);
    quitButton->render(renderer);
}

void playing(SDL_Renderer* renderer)
{
    background->render(renderer);
    background->renderOffset(renderer);
    backgroundLayer5->render(renderer);
    backgroundLayer5->renderOffset(renderer);
    switch (yolk->state){
        case PLAY: case PAUSE_1: case PAUSE_2: case HIT_1:
            yolk->render(renderer);
            for (int i = 0; i < coins.size(); i++){
                coins[i]->render(renderer,yolk->state);
            }
            for (int i = 0; i < enemy.size(); i++){
                enemy[i]->render(renderer,yolk->state);
            }
            for (int i = 0; i < NUM_OF_DOTS; i++){
                bridge[i].render(renderer);
            }
            break;

        case HIT_2:
            for (int i = 0; i < coins.size(); i++){
                coins[i]->render(renderer,HIT_2);
            }
            for (int i = 0; i < enemy.size(); i++){
                enemy[i]->render(renderer,HIT_2);
            }
            for (int i = 0; i < NUM_OF_DOTS; i++){
                bridge[i].render(renderer);
            }
            yolk->render(renderer);
    }
    backgroundLayer2->render(renderer);
    if (text.loadText(renderer, to_string(yolk->score), 35, orange)){
        text.render(renderer,64,10);
    }
    if (level < 10){
        if (text.loadText(renderer, "0", 48, orange)){
            text.render(renderer,177,16);
        }
        if (text.loadText(renderer, to_string(level), 48, orange)){
            text.render(renderer,225,16);
        }
    }
    else{
        if (text.loadText(renderer, to_string(level), 48, orange)){
            text.render(renderer,177,16);
        }
    }
    settingsButton->render(renderer);
    helpButton->render(renderer);
    quitButton->render(renderer);
}

void help(SDL_Renderer* renderer, const Music& music)
{
    if (lastMode == START) start(renderer,music);
    else if (lastMode == PLAYING){
        playing(renderer);
        if (Mix_PlayingMusic() == 1) Mix_PauseMusic();
    }
    backgroundLayer3->render(renderer);
    continueButton->setPosition(120,600);
    continueButton->render(renderer);
}

void settings(SDL_Renderer* renderer, const Music& music)
{
    if (lastMode == START) start(renderer, music);
    else{
        playing(renderer);
        if (yolk->dir != TOTAL_OF_DIRECTION) yolk->frame--;
        if (Mix_PlayingMusic() == 1){
            Mix_PauseMusic();
        }
    }
    backgroundLayer6->render(renderer);
    if (day && !night){
        background->getTexture(BACKGROUND);
        backgroundLayer1->getTexture(BACKGROUNDLAYER1);
        backgroundLayer2->getTexture(BACKGROUNDLAYER2);
        backgroundLayer5->getTexture(BACKGROUNDLAYER5);
        for (int i = 0; i < NUM_OF_DOTS; i++){
            bridge[i].getTexture(BRIDGE);
        }
        dayButton->currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
        nightButton->currentSprite = BUTTON_SPRITE_MOUSE_OUT;
    }
    if (!day && night){
        background->getTexture(BACKGROUND2);
        backgroundLayer1->getTexture(BACKGROUNDLAYER1_2);
        backgroundLayer2->getTexture(BACKGROUNDLAYER2_2);
        backgroundLayer5->getTexture(BACKGROUNDLAYER5_2);
        for (int i = 0; i < NUM_OF_DOTS; i++){
            bridge[i].getTexture(BRIDGE2);
        }
        dayButton->currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        nightButton->currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
    }
    dayButton->render(renderer);
    nightButton->render(renderer);
    continueButton->setPosition(120,518);
    continueButton->render(renderer);
}

void pause(SDL_Renderer* renderer)
{
    playing(renderer);

}

void end(SDL_Renderer* renderer){
    // Check high score
    if (yolk->score > highScore){
        highScore = yolk->score;
        ofstream score("highScore.txt");
        score << yolk->score;
        score.close();
    }

    playing(renderer);

    backgroundLayer4->render(renderer);
    if (text.loadText(renderer, to_string(highScore), 50, white)){
        text.render(renderer,235,215);
    }
    if (text.loadText(renderer, to_string(yolk->score), 50, white)){
        text.render(renderer,235,315);
    }
    continueButton->setPosition(120,413);
    continueButton->render(renderer);
}

void freeGame()
{
    for (int i = 0; i < enemy.size(); i++){
        enemy.erase(enemy.begin() + i);
        delete enemy[i];
    }
    for (int i = 0; i < coins.size(); i++){
        coins.erase(coins.begin() + i);
        delete coins[i];
    }
    delete background;
    delete backgroundLayer1;
    delete backgroundLayer2;
    delete backgroundLayer3;
    delete backgroundLayer4;
    delete backgroundLayer5;
    delete backgroundLayer6;
    delete introBackground;

    delete startButton;
    delete helpButton;
    delete settingsButton;
    delete dayButton;
    delete nightButton;
    delete continueButton;
    delete quitButton;

    delete []bridge;
    delete yolk;
}
