#include "Tetromino.h"

Tetromino::Tetromino() : x(TETROMINO_START_X), y(TETROMINO_START_Y)
{
    switch (rand() % 7)
    {
    case 0: // I
        points[0] = {0, 0};
        points[1] = {-1, 0};
        points[2] = {-2, 0};
        points[3] = {1, 0};
        colorId = 1;
        break;
    case 1: // O
        points[0] = {0, -1};
        points[1] = {-1, -1};
        points[2] = {-1, 0};
        points[3] = {0, 0};
        colorId = 2;
        break;
    case 2: // Z
        points[0] = {0, 0};
        points[1] = {-1, 0};
        points[2] = {-1, 1};
        points[3] = {0, -1};
        colorId = 3;
        break;
    case 3: // S
        points[0] = {0, 0};
        points[1] = {-1, 0};
        points[2] = {0, 1};
        points[3] = {-1, -1};
        colorId = 4;
        break;
    case 4: // L
        points[0] = {0, 0};
        points[1] = {0, -1};
        points[2] = {0, 1};
        points[3] = {-1, -1};
        colorId = 5;
        break;
    case 5: // J
        points[0] = {0, 0};
        points[1] = {0, -1};
        points[2] = {0, 1};
        points[3] = {1, -1};
        colorId = 6;
        break;
    case 6: // T
        points[0] = {0, 0};
        points[1] = {0, -1};
        points[2] = {0, 1};
        points[3] = {-1, 0};
        colorId = 7;
        break;
    }
}

void Tetromino::rotate()
{
    for (int i = 0; i < TETROMINO_BLOCK_COUNT; i++)
    {
        int x = points[i].x - points[0].x;
        int y = points[i].y - points[0].y;
        points[i].x = points[0].x - y;
        points[i].y = points[0].y + x;
    }
}

void Tetromino::undoRotate()
{
    for (int i = 0; i < TETROMINO_BLOCK_COUNT; i++)
    {
        int x = points[i].x - points[0].x;
        int y = points[i].y - points[0].y;
        points[i].x = points[0].x + y;
        points[i].y = points[0].y - x;
    }
}

void Tetromino::move(int dx, int dy)
{
    x += dx;
    y += dy;
}

int Tetromino::getPointX(int i)
{
    return points[i].x + x;
}

int Tetromino::getPointY(int i)
{
    return points[i].y + y;
}

int Tetromino::getColorId()
{
    return colorId;
}
