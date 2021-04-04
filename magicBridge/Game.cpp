#include "Game.h"
#include "Core.h"
#include "Materials.h"
#include <iostream>
using namespace std;

vector <Enemy*> enemy;
int MIN_DISTANCE = SCREEN_HEIGHT;

bool Game::init()
{
    bool success = true;
    //Initialize background
    background = new Background;
    //Initialize bridge
    bridge = new Bridge [NUM_OF_DOTS];
    for (int i = 0; i < NUM_OF_DOTS; i++){
        bridge[i].posX = i * DOT_WIDTH;
        // 80 gives enough space for bridge to move dowm
        bridge[i].posY = BRIDGE_IDLE_HEIGHT;

        if (bridge[i].texture == NULL)success = false;
    }
    // Set Yolk to stand on the bridge
    yolk = new Yolk((SCREEN_WIDTH - YOLK_WIDTH)/2, bridge[0].posY - YOLK_HEIGHT);
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

void Game::loop()
{
    ++(background->offset);
    if( background->offset > background->height )
				{
					background->offset = 0;
				}
    if (bridge->checkDir(bridge)) yolk->run(bridge[0].posY - BRIDGE_IDLE_HEIGHT);
    yolk->move(bridge);
    //if (enemy.size() > 0) cout << enemy[0]->posY << endl;
    if ( (enemy.size() > 0) &&  enemy[0]->posY > SCREEN_HEIGHT){
            delete enemy[0];
            enemy.erase(enemy.begin());
    }
    int chance = (rand() % 100) + 1;
    if (( enemy.size() < 1) || ( (enemy.size() > 0) && (enemy[enemy.size()-1]->posY > MIN_DISTANCE) ) ){
        if (chance > 70){
            enemy.push_back(new Radish);
            enemy[enemy.size()-1]->setPos();
        } else if (chance > 30){
            enemy.push_back(new Spike);
            enemy[enemy.size()-1]->setPos();
        } else if (chance > 0) {
            enemy.push_back(new Bird);
            enemy[enemy.size()-1]->setPos();
        }
        if (MIN_DISTANCE > SCREEN_HEIGHT/5) MIN_DISTANCE -= SCREEN_HEIGHT/30;
    }
}

void Game::render(SDL_Renderer* renderer)
{
    background->render(renderer);
    background->renderOffset(renderer);
    yolk->render(renderer, bridge);
    for (int i = 0; i < enemy.size(); i++){
        enemy[i]->render(renderer);
    }
    for (int i = 0; i < NUM_OF_DOTS; i++){
        bridge[i].render(renderer);
    }
}

void Game::free()
{
    delete background;
    delete bridge;
    delete yolk;
    //delete radish;
    //delete spike;
    //delete bird;
}


