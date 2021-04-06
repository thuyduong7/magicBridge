#include "SpikeBall.h"

SpikeBall::SpikeBall()
{
    ball = new Ball*[MAX_ROWS];
    for (int i = 0; i < MAX_ROWS; i++){
            *(ball+i) = new Ball[NUM_OF_COLS];
    }
}

void SpikeBall::setPos()
{
    numOfRows = (rand() % MAX_ROWS) + 1;
    //cout << numOfRows << endl;
    firstEmptyPos = rand() % (NUM_OF_COLS - NUM_OF_EMPTY_POS + 1);
    posY = -numOfRows*SPIKEBALL_HEIGHT;

    lastEmptyPos = firstEmptyPos + NUM_OF_EMPTY_POS - 1;
    for (int i = 0; i < numOfRows; i++){
        for (int j = 0; j < NUM_OF_COLS; j++){
            ball[i][j].posY = (i * SPIKEBALL_WIDTH)+posY;
            ball[i][j].posX = j * SPIKEBALL_HEIGHT;

            if ( (j < firstEmptyPos) || (j > lastEmptyPos) ) ball[i][j].setBall = true;
        }
    }
}

void SpikeBall::move()
{
    posY++;
    for (int i = 0; i < numOfRows; i++){
        for (int j = 0; j < NUM_OF_COLS; j++){
            ball[i][j].posY++;
        }
    }
}

bool SpikeBall::checkCollision(Yolk* yolk)
{
    // collider here is the blank space where the main character can go through between two blocks of balls
    // "+/-SPIKEBALL_HEIGHT", "+/-SPIKEBALL_HEIGHT/2" will make the collision look like real
    collider.h = (numOfRows * SPIKEBALL_HEIGHT) - SPIKEBALL_HEIGHT;
    collider.w = ((lastEmptyPos - firstEmptyPos + 1) * SPIKEBALL_WIDTH) + SPIKEBALL_WIDTH;
    collider.x = firstEmptyPos * SPIKEBALL_WIDTH - (SPIKEBALL_WIDTH/2);
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

    // (MIN_POS_Y,MAX_POS_Y) is the space where the collision could occur
    if (bottomEmptyPos < MIN_POS_Y) return false;
    if (topEmptyPos > MAX_POS_Y) return false;
    if (bottomYolk < topEmptyPos) return false;

    cout << leftEmptyPos << ' ' << rightEmptyPos << ' ' << topEmptyPos << ' ' << bottomEmptyPos << endl;
    cout << leftYolk << ' ' << rightYolk << ' ' << topYolk << ' ' << bottomYolk << endl;
    cout << "////\n";

    // If Yolk is inside the blank space (collider), it will pass through the balls with no collisions
    if( rightYolk <= rightEmptyPos && leftYolk >= leftEmptyPos)
    {
        return false;
    }

    return true;
}

void SpikeBall::render(SDL_Renderer* renderer)
{
    for (int i = 0; i < numOfRows; i++){
        for (int j = 0; j < NUM_OF_COLS; j++){
            if ( ball[i][j].setBall ) ball[i][j].render(renderer);
        }
    }
}

SpikeBall::~SpikeBall()
{
    for (int i = 0; i < MAX_ROWS; i++)
        delete ball[i];
    delete []ball;
}
