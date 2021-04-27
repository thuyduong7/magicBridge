#include "Coin.h"

Coin::Coin() : Enemy(COIN)
{
    posY = -COIN_HEIGHT;
    sumOFCoins = 0;
}

Coin::~Coin()
{

}

void Coin::setPos(vector<Enemy*> &enemy)
{
    bool touch = false;
    if (enemy.empty()){
        posX = rand()%(PLAYING_SCREEN_WIDTH - COIN_WIDTH) + (MIN_POS_X);
        return;
    }
    if ( (enemy[enemy.size()-1]->type == SPIKEBALL)){
        posY -= (enemy[enemy.size()-1]->height + (rand() % SCREEN_HEIGHT/5) + SCREEN_HEIGHT/10);
    }
    if ( (enemy[enemy.size()-1]->type == BIRD)){
        posY -= (BIRD_HEIGHT + (rand() % SCREEN_HEIGHT/5) + 1);
    }
    do {
        posX = rand()%(PLAYING_SCREEN_WIDTH - COIN_WIDTH) + (MIN_POS_X);
        for (int i = 0; i < enemy.size(); i++){
            if (checkCollisionEnemy(enemy[i])){
                touch = true;
                break;
            }
            if (i == enemy.size()-1) touch = false;
        }
    } while (touch);
}

void Coin::move(double mul)
{
    posY += (velY * mul);
}

bool Coin::checkCollision(Yolk* yolk)
{
    collider.w = (COIN_WIDTH*3)/5;
    collider.h = (COIN_HEIGHT*3)/5;
    collider.x = posX;
    collider.y = posY;
    Enemy::checkCollision(yolk);
}

bool Coin::checkCollisionEnemy(Enemy* enemy)
{
    collider.w = COIN_WIDTH;
    collider.h = COIN_HEIGHT;
    collider.x = posX;
    collider.y = posY;

    SDL_Rect enemyCollider;
    enemyCollider.w = enemy->width;
    enemyCollider.h = enemy->height;
    enemyCollider.x = enemy->posX;
    enemyCollider.y = enemy->posY;

    double leftCoin, leftEnemy;
    double rightCoin, rightEnemy;
    double topCoin, topEnemy;
    double bottomCoin, bottomEnemy;

    leftCoin = collider.x;
    rightCoin = collider.x + collider.w;
    topCoin = collider.y;
    bottomCoin = collider.y + collider.h;

    leftEnemy = enemyCollider.x - PLAYING_SCREEN_WIDTH/5;
    rightEnemy = enemyCollider.x + enemyCollider.w + PLAYING_SCREEN_WIDTH/5;
    topEnemy = enemyCollider.y - SCREEN_HEIGHT/10;
    bottomEnemy = enemyCollider.y + enemyCollider.h + SCREEN_HEIGHT/10;

    if(bottomCoin <= topEnemy) return false;

    if(topCoin >= bottomEnemy) return false;

    if(rightCoin <= leftEnemy) return false;

    if(leftCoin >= rightEnemy) return false;
    return true;
}

void Coin::render(SDL_Renderer* renderer, STATE state)
{
    srcRect = enemyMat.getSprite(COIN, RUN, frame/FRAME_VALUE);
    dstRect = {posX, posY, width, height};
    enemyMat.render(renderer, texture, srcRect, dstRect);
    if (state != HIT_2) frame++;
    if (frame/FRAME_VALUE >= TOTAL_COIN_SPRITE) frame = 0;
}
