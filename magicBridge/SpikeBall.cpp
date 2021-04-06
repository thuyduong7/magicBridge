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
    for (int i = 0; i < numOfRows; i++){
        for (int j = 0; j < NUM_OF_COLS; j++){
            ball[i][j].posY = (i * SPIKEBALL_WIDTH)+posY;
            ball[i][j].posX = j * SPIKEBALL_HEIGHT;
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

void SpikeBall::render(SDL_Renderer* renderer)
{
    for (int i = 0; i < numOfRows; i++){
        for (int j = 0; j < NUM_OF_COLS; j++){
            if ( (j < firstEmptyPos) || (j >= (firstEmptyPos + NUM_OF_EMPTY_POS)) ) ball[i][j].render(renderer);
        }
    }
}

SpikeBall::~SpikeBall()
{
    for (int i = 0; i < MAX_ROWS; i++)
        delete ball[i];
    delete []ball;
}
