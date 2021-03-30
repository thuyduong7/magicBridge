#include "Game.h"
#include "Core.h"
#include "Materials.h"
#include <iostream>
using namespace std;

Enemy radish(RADISH);
Enemy spike(SPIKE);
vector <Enemy> enemy;

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
    //Initialize radish
    //radish = new Enemy(RADISH);
    radish.texture = radish.getTexture();
    if (radish.texture == NULL) success = false;
    //Initialize spike
    spike.texture = spike.getTexture();
    if (spike.texture == NULL) success = false;
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
    if (bridge->checkDir(bridge)) yolk->run(bridge[0].posY - BRIDGE_IDLE_HEIGHT);
    yolk->move(bridge);
    cout << enemy.size() << " now\n";
    for (int i = 0; i < enemy.size(); i++){
        if (enemy[i].posY > SCREEN_HEIGHT) {enemy.erase(enemy.begin()+i);
        cout << "die";
        cout << endl << enemy.size();
        }
    }
    int chance = (rand() % 100) + 1;
    if (( enemy.size() <1) || (enemy.size() > 0 && enemy[enemy.size()-1].posY > SCREEN_HEIGHT/4) ){
        if (chance > 70){
            enemy.push_back(radish);
            enemy[enemy.size()-1].setPos(RADISH);
        } else if (chance > 60){
            enemy.push_back(spike);
            enemy[enemy.size()-1].setPos(SPIKE);
        }
    }
}

void Game::render(SDL_Renderer* renderer)
{
    background -> render(renderer);
    yolk->render(renderer, bridge);
    //spike->render(renderer);
    //radish->render(renderer);
    for (int i = 0; i < enemy.size(); i++){
        enemy[i].render(renderer);
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
}


