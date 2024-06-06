#ifndef GAME_H
#define GAME_H

#include "Tetromino.h"
#include "Utility.h"

#include <ncurses.h>
#include <unistd.h>

class Game
{
public:
    Game();
    int run(int difficulty);

private:
    bool isRunning = false;
    void render();
    void update();
    void processInput();

    static const int width = 10;
    static const int height = 20;
    static const int renderDelay = 10000;
    int score = 0;
    int difficulty = 1;
    int slow = 0;
    int ticksPerRender;

    int field[height][width] = {};

    Tetromino tetromino;
    Tetromino tetrominoNext;
    Tetromino tetrominoDown = tetromino;
    bool checkCollision(Tetromino tetromino);
    void lockBlock();
    int clearFullRows();
};

#endif