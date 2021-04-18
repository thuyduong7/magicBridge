#include "Game.h"
#include "Core.h"
#include "Materials.h"
#include <iostream>
#include <vector>

using namespace std;

vector <Enemy*> enemy;
vector <Coin*> coins;
int MIN_DISTANCE = SCREEN_HEIGHT;
int MIN_COIN_DISTANCE = SCREEN_HEIGHT/2;
//int numOfCoins = 0;

bool Game::init()
{
    bool success = true;
    //Initialize background
    background = new Background(BACKGROUND);
    backgroundLayer = new Background(BACKGROUNDLAYER);
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
    /**
    //Initialize radish
    radish = new Radish;
    //radish->texture = radish.getTexture();
    if (radish->texture == NULL) success = false;
    //Initialize spike
    spike = new Spike;
    //spike.texture = spike.getTexture();
    if (spike->texture == NULL) success = false;
    //Initialize bird
    bird = new Bird;
    //spike.texture = spike.getTexture();
    if (bird->texture == NULL) success = false;
    */
    return success;
}

void Game::handleEvent(SDL_Event& e)
{
    if (e.key.keysym.sym == SDLK_LEFT){
        bridge->setDir(LEFT);
        yolk->setDir(LEFT);
    }
    else if (e.key.keysym.sym == SDLK_RIGHT){
        bridge->setDir(RIGHT);
        yolk->setDir(RIGHT);
    }
}

void Game::keypressed(SDL_Event& e)
{
    if (e.key.keysym.sym == SDLK_LEFT){
        bridge->setDir(LEFT);
        yolk->setDir(LEFT);
    }
    else if (e.key.keysym.sym == SDLK_RIGHT){
        bridge->setDir(RIGHT);
        yolk->setDir(RIGHT);
    }
}

void Game::keyreleased(SDL_Event& e)
{
    if (e.key.keysym.sym == SDLK_LEFT){
        bridge->setDir(TOTAL_OF_DIRECTION);
        //yolk->setDir(TOTAL_OF_DIRECTION);
    }
    else if (e.key.keysym.sym == SDLK_RIGHT){
        bridge->setDir(TOTAL_OF_DIRECTION);
        //yolk->setDir(TOTAL_OF_DIRECTION);
    }
}

void Game::loop(bool& quit)
{
    background->offset += 2;
    if( background->offset > background->height )
    {
        background->offset = 0;
    }
    if (bridge->checkDir(bridge)) yolk->run(bridge[0].posY - BRIDGE_IDLE_HEIGHT);
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

    if ((( enemy.size() < 1) || ( (enemy.size() > 0) && (enemy[enemy.size()-1]->posY > MIN_DISTANCE) ))
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
        if (MIN_DISTANCE > SCREEN_HEIGHT/4) MIN_DISTANCE -= SCREEN_HEIGHT/30;
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
            quit = true;
            break;
        }

    }

    for (int i = 0; i < coins.size(); i++){
        if (coins[i]->checkCollision(yolk)){
            coins.erase(coins.begin() + i);
            yolk->numOfCoins++;
            cout << yolk->numOfCoins << endl;
            break;
        }
    }
}

void Game::update()
{
    for (int i = 0; i < enemy.size(); i++){
        enemy[i]->move();
    }
    for (int i = 0; i < coins.size(); i++){
        coins[i]->move();
    }
}

void Game::render(SDL_Renderer* renderer, bool& quit, bool& die)
{
    background->render(renderer);
    background->renderOffset(renderer);
    if (!quit) yolk->render(renderer, bridge, quit, die);
    for (int i = 0; i < coins.size(); i++){
        coins[i]->render(renderer,quit);
    }
    for (int i = 0; i < enemy.size(); i++){
        enemy[i]->render(renderer,quit);
    }
    for (int i = 0; i < NUM_OF_DOTS; i++){
        bridge[i].render(renderer);
    }
    backgroundLayer->render(renderer);
    if (quit && !die) yolk->render(renderer, bridge, quit, die);
}

void Game::free()
{
    delete background;
    delete backgroundLayer;
    delete []bridge;
    delete yolk;
    for (int i = 0; i < enemy.size(); i++){
        enemy[i]->free();
        delete enemy[i];
        enemy.erase(enemy.begin() + i);
    }
    for (int i = 0; i < coins.size(); i++){
        coins[i]->free();
        delete coins[i];
        coins.erase(coins.begin() + i);
    }
    //delete radish;
    //delete spike;
    //delete bird;
}


