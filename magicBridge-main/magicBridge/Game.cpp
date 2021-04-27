#include "Game.h"


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector <Enemy*> enemy;
vector <Coin*> coins;
int MIN_COIN_DISTANCE = SCREEN_HEIGHT/2;

double BACKGROUND_VEL = 2;
//int numOfCoins = 0;

//Color of text
SDL_Color pink = {255, 73, 134};
SDL_Color white = {255, 255, 255};

Game::Game()
{

}

bool Game::init()
{
    bool success = true;
    //Initialize background
    background = new Background(BACKGROUND);
    backgroundLayer1 = new Background(BACKGROUNDLAYER1);
    backgroundLayer2 = new Background(BACKGROUNDLAYER2);
    backgroundLayer3 = new Background(BACKGROUNDLAYER3);
    backgroundLayer4 = new Background(BACKGROUNDLAYER4);
    introBackground = new Background(INTRO);

    //Buttons
    startButton = new Button(START_BUTTON);
    startButton->setPosition((SCREEN_WIDTH - START_BUTTON_WIDTH)/2, BRIDGE_IDLE_HEIGHT + 45);

    helpButton = new Button(HELP_BUTTON);
    helpButton->setPosition(SCREEN_WIDTH - QUIT_BUTTON_WIDTH - HELP_BUTTON_WIDTH - 10, 10);

    pauseButton = new Button(PAUSE_BUTTON);
    pauseButton->setPosition
    (SCREEN_WIDTH - QUIT_BUTTON_WIDTH - HELP_BUTTON_WIDTH - PAUSE_BUTTON_WIDTH - 15, 10);

    continueButton = new Button(CONTINUE_BUTTON);


    quitButton = new Button(QUIT_BUTTON);
    quitButton->setPosition(SCREEN_WIDTH - QUIT_BUTTON_WIDTH - 5, 10);

    //Initialize bridge
    bridge = new Bridge [NUM_OF_DOTS];
    for (int i = 0; i < NUM_OF_DOTS; i++){
        bridge[i].posX = MIN_POS_X + i * DOT_WIDTH;
        // 80 gives enough space for bridge to move dowm
        bridge[i].posY = BRIDGE_IDLE_HEIGHT;

        if (bridge[i].texture == NULL)success = false;
    }
    // Set Yolk to stand on the bridge
    yolk = new Yolk((SCREEN_WIDTH - YOLK_WIDTH)/2, bridge[0].posY - YOLK_HEIGHT + STANDING_GAP);
    if (yolk->texture == NULL) success = false;

    // Set initial multiplier of velocity
    mul = 1;
    // Each round will have a particular multiplier of velocity
    round = 0;
    lastMode = 1;
    min_distance = SCREEN_HEIGHT;
    // Get last high score
    ifstream score("Highscore.txt");
    score >> highScore;
    score.close();

    return success;
}

void Game::handleEventStart(SDL_Event& e, const Music& music, int& mode, bool& quit)
{
    startButton->handleEvent(e);
    helpButton->handleEvent(e);
    quitButton->handleEvent(e);
    if (startButton->click){
            Mix_PlayChannel(-1, music.pressStart, 0);
            mode = 2;
            timer.start();
            Mix_PausedMusic();
            //Mix_PlayMusic( music.themeSong, -1 );
    }
    if (helpButton->click){
            Mix_PlayChannel(-1, music.click, 0);
            mode = 3;
            lastMode = 1;
            //inHelp = true;
            timer.pause();
    }
    if (quitButton->click){
            Mix_PlayChannel(-1, music.click, 0);
            SDL_Delay(200);
            quit = true;
    }
}

void Game::handleEventHelp(SDL_Event& e, const Music& music, int& mode)
{
    continueButton->handleEvent(e);
    if (continueButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        continueButton->currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        if (lastMode == 1) mode = 1;
        else if (lastMode == 2){
            mode = 2;
            timer.unpause();
            //cout << "UNPAUSE" << ' ' << timer.isPaused() << endl;
        }

    }
}

void Game::handleEventPlaying(SDL_Event& e, const Music& music, int& mode, bool& quit)
{
    //when main character dies, mode will be changed to END
    if (yolk->state == HIT_2){
        return;
    }
    pauseButton->handleEvent(e);
    helpButton->handleEvent(e);
    quitButton->handleEvent(e);
    if (pauseButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        mode = 4;
        timer.pause();
    }
    if (helpButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        mode = 3;
        lastMode = 2;
    }
    if (quitButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        SDL_Delay(200);
        quit = true;
    }

    if (e.type == SDL_KEYDOWN){
        if (e.key.keysym.sym == SDLK_LEFT){
            bridge->dir = LEFT;
            //bridge->setDir(LEFT, bridge);
            //yolk->setDir(bridge[0].posY - BRIDGE_IDLE_HEIGHT);
        }
        else if (e.key.keysym.sym == SDLK_RIGHT){
            bridge->dir = RIGHT;
            //bridge->setDir(RIGHT, bridge);
            //yolk->setDir(bridge[0].posY - BRIDGE_IDLE_HEIGHT);
        }
        if (bridge->move(bridge)) Mix_PlayChannel(-1, music.moveBridge, 0);
    }
    else if (e.type == SDL_KEYUP){
        if (e.key.keysym.sym == SDLK_LEFT){
            bridge->dir = TOTAL_OF_DIRECTION;
            //bridge->setDir(TOTAL_OF_DIRECTION, bridge);
            //yolk->setDir(bridge[0].posY - BRIDGE_IDLE_HEIGHT);
            //yolk->setDir(TOTAL_OF_DIRECTION);
        }
        else if (e.key.keysym.sym == SDLK_RIGHT){
            bridge->dir = TOTAL_OF_DIRECTION;
            //bridge->setDir(TOTAL_OF_DIRECTION, bridge);
            //yolk->setDir(bridge[0].posY - BRIDGE_IDLE_HEIGHT);
            //yolk->setDir(TOTAL_OF_DIRECTION);
        }
    }
}

void Game::handleEventPause(SDL_Event& e, const Music& music, int& mode)
{
    pauseButton->handleEvent(e);
    if (pauseButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        mode = 2;
        timer.unpause();
    }
}

void Game::handleEventEnd(SDL_Event& e, const Music& music, int& mode)
{
    continueButton->handleEvent(e);
    if (continueButton->click){
        Mix_PlayChannel(-1, music.click, 0);
        mode = 1;
        for (vector <Enemy*>::iterator it = enemy.begin(); it != enemy.end();){
            it = enemy.erase(it);
        }
        for (vector <Coin*>::iterator it = coins.begin(); it != coins.end();){
            it = coins.erase(it);
        }
        init();
    }
}

void Game::loop(bool& quit, const Music& music, int& mode)
{
    if (yolk->state == HIT_2){
        if (yolk->posY > SCREEN_HEIGHT){
            timer.stop();
            mode = 5;
        }
        return;
    }

    if( Mix_PausedMusic() == 1 )
    {
        Mix_ResumeMusic();
    }
    bridge->move(bridge);
    yolk->setDir(bridge[0].posY - BRIDGE_IDLE_HEIGHT);
    yolk->move(bridge);
    //if (enemy.size() > 0) cout << enemy[0]->posY << endl;
    if ( (enemy.size() > 0) && ((enemy[0]->posY > SCREEN_HEIGHT) )){
            delete enemy[0];
            enemy.erase(enemy.begin());
    }
    if ( (coins.size() > 0) && ((coins[0]->posY > SCREEN_HEIGHT) )){
            delete coins[0];
            coins.erase(coins.begin());
    }
    int chance = (rand() % 100) + 1;

    if ((( enemy.size() < 1) || ( (enemy.size() > 0) && (enemy[enemy.size()-1]->posY > min_distance) ))
        && (( coins.size() < 1) || ( (coins.size() > 0)
                                && (coins[coins.size()-1]->posY > 0))) ){
        if (chance > 80){
            //cout << "Radish" << endl;
            enemy.push_back(new Radish);
            enemy[enemy.size()-1]->setPos();
            //cout << enemy[enemy.size()-1]->posY;
        } else if (chance > 60){
            //cout << "Spike" << endl;
            enemy.push_back(new Spike);
            //cout << enemy[enemy.size()-1]->posY;
            enemy[enemy.size()-1]->setPos();
        } else if (chance > 40) {
            //cout << "Bird" << endl;
            enemy.push_back(new Bird);
            enemy[enemy.size()-1]->setPos();
            //cout << enemy[enemy.size()-1]->posY;
        } else if (chance > 20) {
            cout << "Spikeball" << endl;
            enemy.push_back(new SpikeBall);
            enemy[enemy.size()-1]->setPos();
            //cout << enemy[enemy.size()-1]->posY;
        }
        if (min_distance > SCREEN_HEIGHT/3) min_distance -= SCREEN_HEIGHT/30;
    }
    if (( coins.size() < 1) || ( (coins.size() > 0)
                                && (coins[coins.size()-1]->posY > MIN_COIN_DISTANCE))){
        int coinChance = (rand() % 100);
        if (coinChance > 70){
            //cout << "Coin" << endl;
            coins.push_back(new Coin);
            coins[coins.size()-1]->setPos(enemy);
        }
    }

    for (int i = 0; i < enemy.size(); i++){
        if (enemy[i]->checkCollision(yolk)){
            //quit = true;
            if (yolk->state == PLAY) Mix_PlayChannel(-1, music.hit, 0);
            else Mix_PlayChannel(-1, music.die, 0);
            yolk->handleCollision();
            break;
        }
    }

    for (int i = 0; i < coins.size(); i++){
        if (coins[i]->checkCollision(yolk)){
            coins.erase(coins.begin() + i);
            Mix_PlayChannel(-1, music.eatCoin, 0);
            yolk->numOfCoins++;
            cout << yolk->numOfCoins << endl;
        }
    }
    //cout << timer.getTicks() << endl;
    if (timer.getTicks() > 0 && (timer.getTicks() > (round+1)*5000)){
        round++;
        //cout << (100 + round*2) / 100.00f << endl;
        mul = (100 + round) / 100.00f;
        if (mul > 1.5) mul = 1.5;
    }
}

void Game::update()
{
    if (yolk->state == HIT_2){
        Mix_PauseMusic();
        return;
    }
    for (int i = 0; i < enemy.size(); i++){
        enemy[i]->move(mul);
    }
    for (int i = 0; i < coins.size(); i++){
        coins[i]->move(mul);
    }
    yolk->checkState();
    background->offset += BACKGROUND_VEL * mul;
    if( background->offset > background->height )
    {
        background->offset = 0;
    }
}

void Game::start(SDL_Renderer* renderer, bool& quit, const Music& music)
{
    if (Mix_PlayingMusic() == 0 || Mix_PausedMusic()){
        Mix_PlayMusic(music.themeSongStart, -1);
        cout << "start music" << endl;
    }
    background->render(renderer);
    background->renderOffset(renderer);
    introBackground->renderIntro(renderer);
    yolk->render(renderer,bridge,quit);

    for (int i = 0; i < NUM_OF_DOTS; i++){
        bridge[i].render(renderer);
    }

    backgroundLayer1->render(renderer);

    if (text.loadText(renderer, to_string(highScore), 35, pink)){
            text.render(renderer,64,16);
    }
    if (text.loadText(renderer, "MAGIC", 63, pink)){
        text.render(renderer, 83, 90);
    }
    if (text.loadText(renderer, "BRIDGE!", 63, pink)){
        text.render(renderer, 43, 160);
    }

    startButton->render(renderer);
    helpButton->render(renderer);
    quitButton->render(renderer);

}

void Game::help(SDL_Renderer* renderer, bool& quit, const Music& music)
{
    if (lastMode == 1) start(renderer,quit,music);
    else if (lastMode == 2){
        playing(renderer,quit);
        if (Mix_PlayingMusic() == 1){
            Mix_PauseMusic();
        }
    }
    backgroundLayer3->render(renderer);
    continueButton->setPosition(120,600);
    continueButton->render(renderer);
}

void Game::playing(SDL_Renderer* renderer, bool& quit)
{
    background->render(renderer);
    background->renderOffset(renderer);
    switch (yolk->state){
        case PLAY: case PAUSE_1: case PAUSE_2: case HIT_1:
            yolk->render(renderer, bridge, quit);
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
            yolk->render(renderer, bridge, quit);
    }

    backgroundLayer2->render(renderer);
    if (text.loadText(renderer, to_string(yolk->numOfCoins), 35, pink)){
            text.render(renderer,64,16);
    }
    if (round < 10){
        if (text.loadText(renderer, "0", 48, pink)){
            text.render(renderer,177,16);
        }
        if (text.loadText(renderer, to_string(round), 48, pink)){
            text.render(renderer,225,16);
        }
    }
    else{
        if (text.loadText(renderer, to_string(round), 48, pink)){
            text.render(renderer,177,16);
        }
    }


    pauseButton->render(renderer);
    helpButton->render(renderer);
    quitButton->render(renderer);
}

void Game::pause(SDL_Renderer* renderer, bool& quit)
{
    playing(renderer,quit);
    if (yolk->dir != TOTAL_OF_DIRECTION) yolk->frame--;
    if (Mix_PlayingMusic() == 1){
        Mix_PauseMusic();
    }
}

void Game::end(SDL_Renderer* renderer, bool& quit){
    // Check high score
    if (yolk->numOfCoins > highScore){
        ofstream score("highScore.txt");
        score << yolk->numOfCoins;
        score.close();
    }

    playing(renderer,quit);

    backgroundLayer4->render(renderer);
    if (text.loadText(renderer, to_string(highScore), 50, white)){
        text.render(renderer,235,215);
    }
    if (text.loadText(renderer, to_string(yolk->numOfCoins), 50, white)){
        text.render(renderer,235,315);
    }
    continueButton->setPosition(120,413);
    continueButton->render(renderer);
}

void Game::free()
{
    for (int i = 0; i < enemy.size(); i++){
        enemy[i]->free();
        enemy.erase(enemy.begin() + i);
        delete enemy[i];
    }
    for (int i = 0; i < coins.size(); i++){
        coins[i]->free();
        coins.erase(coins.begin() + i);
        delete coins[i];
    }
    delete background;
    delete backgroundLayer1;
    delete backgroundLayer2;
    delete backgroundLayer3;
    delete backgroundLayer4;

    delete startButton;
    delete helpButton;
    delete pauseButton;
    delete continueButton;
    delete quitButton;

    delete []bridge;
    delete yolk;
}


