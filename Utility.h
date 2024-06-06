#ifndef UTILITY_H
#define UTILITY_H

#include "Colors.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <codecvt>

#define HEIGHT 48
#define WIDTH 160
#define RENDER_SCALE_X 4
#define RENDER_SCALE_Y 2
#define TETROMINO_BLOCK_COUNT 4
#define TETROMINO_START_X 5
#define TETROMINO_START_Y 1

void showMenu(std::vector<std::string> options, int &choice);
void gotoxy(int x, int y);
std::string inputPlayerName();
void printBannerTetris();
bool kbhit();
char _getch();

#endif
