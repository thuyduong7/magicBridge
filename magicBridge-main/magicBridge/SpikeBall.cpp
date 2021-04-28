#include "SpikeBall.h"

Ball::Ball() : Enemy(SPIKEBALL)
{
    setBall = false;
}

Ball::~Ball()
{

}

void Ball::render(SDL_Renderer* renderer, STATE state)
{
    dstRect = {posX, posY, width, height};
    enemyMat.render(renderer, texture, srcRect, dstRect);
}

SpikeBall::SpikeBall():Enemy(SPIKEBALL)
{
    posX = MIN_POS_X;
    posY = 0;
    width = PLAYING_SCREEN_WIDTH;
    ball = new Ball*[MAX_ROWS];
    for (int i = 0; i < MAX_ROWS; i++){
            *(ball+i) = new Ball[NUM_OF_COLS];
    }
    coin = new Coin[MAX_ROWS];
    setCoin = false;
    _music.loadMusic();
}

SpikeBall::~SpikeBall()
{
    _music.free();
    for (int i = 0; i < MAX_ROWS; i++){
        delete ball[i];
    }
    delete []ball;
    for (int i = 0; i < fcoin.size(); i++){
        fcoin.erase(fcoin.begin() + i);
        delete fcoin[i];
    }
}

void SpikeBall::setPos()
{
    numOfRows = (rand() % MAX_ROWS) + 1;
    firstEmptyPos = rand() % (NUM_OF_COLS - NUM_OF_EMPTY_POS + 1);
    posY = -numOfRows*SPIKEBALL_HEIGHT;
    lastEmptyPos = firstEmptyPos + NUM_OF_EMPTY_POS - 1;
    int coinChance = rand()%2;
    if (coinChance == 1) setCoin = true;
    for (int i = 0; i < numOfRows; i++){
        for (int j = 0; j < NUM_OF_COLS; j++){
            ball[i][j].posY = (i * SPIKEBALL_HEIGHT) + posY;
            ball[i][j].posX = MIN_POS_X + j * SPIKEBALL_WIDTH;

            if ( (j < firstEmptyPos) || (j > lastEmptyPos) ) ball[i][j].setBall = true;
        }
    }
    if (setCoin){
        for (int i = 0; i < numOfRows; i++){
            fcoin.push_back(new Coin);
            fcoin[i]->posX = firstEmptyPos * SPIKEBALL_WIDTH + (EMPTY_POS_WIDTH - COIN_WIDTH)/2 + MIN_POS_X;
            //cout << ball[i][0].posY << endl;
            fcoin[i]->posY = ball[i][0].posY + (SPIKEBALL_HEIGHT - COIN_HEIGHT)/2;
        }
    }
    height = numOfRows * SPIKEBALL_HEIGHT;
}

void SpikeBall::move(const double& mul)
{
    posY += (velY * mul);
    for (int i = 0; i < numOfRows; i++){
        for (int j = 0; j < NUM_OF_COLS; j++){
            ball[i][j].posY += (velY * mul);
        }
    }
    if (setCoin){
        //cout << fcoin.size();
        for (int i = 0; i < fcoin.size(); i++){
            fcoin[i]->move(mul);
            if (fcoin[i]->posY > SCREEN_HEIGHT) {
                    delete fcoin[i];
                    fcoin.erase(fcoin.begin() + i);
            }
        }
    }
}

bool SpikeBall::checkCollision(Yolk* yolk)
{
    // Check if Yolk has eaten coins
    if (setCoin){
        for (int i = fcoin.size() - 1; i >= 0; i--){
            if (fcoin[i]->checkCollision(yolk)){
                Mix_PlayChannel(-1,_music.eatCoin,0);
                delete fcoin[i];
                fcoin.erase(fcoin.begin() + i);
                yolk->score++;
            }
        }
    }

    if (yolk->state == PAUSE_1) return false;

    // collider here is the blank space where the main character can go through between two blocks of balls
    // "+/-SPIKEBALL_HEIGHT", "+/-SPIKEBALL_HEIGHT/2" will make the collision look like real
    collider.h = (numOfRows * SPIKEBALL_HEIGHT) - SPIKEBALL_HEIGHT;
    collider.w = ((lastEmptyPos - firstEmptyPos + 1) * SPIKEBALL_WIDTH) + SPIKEBALL_WIDTH;
    collider.x = MIN_POS_X + firstEmptyPos * SPIKEBALL_WIDTH - (SPIKEBALL_WIDTH/2);
    collider.y = posY + (SPIKEBALL_HEIGHT/2);

    int leftYolk, leftEmptyPos;
    int rightYolk, rightEmptyPos;
    int topYolk, topEmptyPos;
    int bottomYolk, bottomEmptyPos;

    leftEmptyPos = collider.x;
    rightEmptyPos = collider.x + collider.w;
    topEmptyPos = collider.y;
    bottomEmptyPos = collider.y + collider.h;

    leftYolk = yolk->posX;
    rightYolk = yolk->posX + yolk->width;
    topYolk = yolk->posY;
    bottomYolk = yolk->posY + yolk->height;

    if (bottomEmptyPos < topYolk) {
            return false;
    }
    if (topEmptyPos > bottomYolk) {
            return false;
    }

    // If Yolk is inside the blank space (collider), it will pass through the balls with no collisions
    if( rightYolk <= rightEmptyPos && leftYolk >= leftEmptyPos)
    {
        return false;
    }
    return true;
}

void SpikeBall::render(SDL_Renderer* renderer, STATE state)
{
    for (int i = 0; i < numOfRows; i++){
        for (int j = 0; j < NUM_OF_COLS; j++){
            if ( ball[i][j].setBall ) ball[i][j].render(renderer, state);
        }
    }
    if (setCoin){
        for (int i = 0; i < fcoin.size(); i++){
            fcoin[i]->render(renderer, state);
        }
    }
}
