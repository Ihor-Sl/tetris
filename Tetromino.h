#ifndef TETROMINO_H
#define TETROMINO_H

#include "Utility.h"
#include "Point.h"

#include <cstdlib>

class Tetromino
{
public:
    Tetromino();
    void rotate();
    void undoRotate();
    void move(int dx, int dy);
    int getPointX(int i);
    int getPointY(int i);
    int getColorId();

private:
    Point points[TETROMINO_BLOCK_COUNT];
    int x;
    int y;
    int colorId;
};

#endif
