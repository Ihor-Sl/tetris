#include "Game.h"

Game::Game() {}

int Game::run(int difficulty)
{
    this->difficulty = difficulty;
    ticksPerRender = 40 - difficulty * 15;
    isRunning = true;
    initscr();
    start_color();
    noecho();
    timeout(0);
    curs_set(0);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    while (isRunning)
    {
        erase();
        render();
        update();
        processInput();
        usleep(renderDelay);
    }
    mvaddstr(HEIGHT - 1, 0, "Гру завершено, натисніть ENTER щоб повернутися у меню ... ");
    refresh();
    while (getch() != '\n')
        ;
    endwin();
    return score;
}

void Game::render()
{
    mvprintw(2, 56, "Рахунок: %d", score);

    mvaddstr(4, 56, "W - повернути");
    mvaddstr(5, 56, "A - вліво");
    mvaddstr(6, 56, "D - вправо");
    mvaddstr(7, 56, "SPACE - пришвидшити падіння");
    mvaddstr(8, 56, "Q - завершити гру");

    mvaddstr(11, 56, "Наступна фігура:");

    //Відмальовка наступної фігури
    for (int i = 0; i < TETROMINO_BLOCK_COUNT; i++)
    {
        attron(COLOR_PAIR(tetrominoNext.getColorId()));
        mvaddstr((tetrominoNext.getPointY(i) + 7) * 2, (tetrominoNext.getPointX(i) + 11) * 4, "████");
        mvaddstr((tetrominoNext.getPointY(i) + 7) * 2 + 1, (tetrominoNext.getPointX(i) + 11) * 4, "████");
        attroff(COLOR_PAIR(tetrominoNext.getColorId()));
    }

    //Встановлення позиції проекції фігури
    tetrominoDown = tetromino;
    while (true)
    {
        tetrominoDown.move(0, 1);
        if (checkCollision(tetrominoDown))
        {
            tetrominoDown.move(0, -1);
            break;
        }
    }

    //Відмальовка проекції фігури
    for (int i = 0; i < TETROMINO_BLOCK_COUNT; i++)
    {
        attron(COLOR_PAIR(tetrominoDown.getColorId()));
        mvaddstr((tetrominoDown.getPointY(i) + 1) * RENDER_SCALE_Y, (tetrominoDown.getPointX(i) + 1) * RENDER_SCALE_X, "####");
        mvaddstr((tetrominoDown.getPointY(i) + 1) * RENDER_SCALE_Y + 1, (tetrominoDown.getPointX(i) + 1) * RENDER_SCALE_X, "####");
        attroff(COLOR_PAIR(tetrominoDown.getColorId()));
    }

    //Відмальовка поточної фігури
    for (int i = 0; i < TETROMINO_BLOCK_COUNT; i++)
    {
        attron(COLOR_PAIR(tetromino.getColorId()));
        mvaddstr((tetromino.getPointY(i) + 1) * RENDER_SCALE_Y, (tetromino.getPointX(i) + 1) * RENDER_SCALE_X, "████");
        mvaddstr((tetromino.getPointY(i) + 1) * RENDER_SCALE_Y + 1, (tetromino.getPointX(i) + 1) * RENDER_SCALE_X, "████");
        attroff(COLOR_PAIR(tetromino.getColorId()));
    }

    //Відмальовка поля
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (field[y][x] != 0)
            {
                attron(COLOR_PAIR(field[y][x]));
                mvaddstr((y + 1) * RENDER_SCALE_Y, (x + 1) * RENDER_SCALE_X, "████");
                mvaddstr((y + 1) * RENDER_SCALE_Y + 1, (x + 1) * RENDER_SCALE_X, "████");
                attroff(COLOR_PAIR(field[y][x]));
            }
        }
    }

    //Відмальовка рамки
    for (int x = 0; x < width + 2; x++)
    {
        for (int y = 1; y < height + 2; y++)
        {
            if (x % (width + 1) == 0 || y == height + 1)
            {
                mvaddstr(y * RENDER_SCALE_Y, x * RENDER_SCALE_X, "████");
                mvaddstr(y * RENDER_SCALE_Y + 1, x * RENDER_SCALE_X, "████");
            }
        }
    }
}

void Game::update()
{
    if (checkCollision(tetromino))
    {
        isRunning = false;
        return;
    }
    slow++;
    if (slow % ticksPerRender == 0)
    {
        tetromino.move(0, 1);
        if (checkCollision(tetromino))
        {
            tetromino.move(0, -1);
            lockBlock();
        }
    }
    score += clearFullRows() * (difficulty * 3 + 1);
}

void Game::processInput()
{
    switch (getch())
    {
    case 'a':
        tetromino.move(-1, 0);
        if (checkCollision(tetromino))
        {
            tetromino.move(1, 0);
        }
        break;

    case 'd':
        tetromino.move(1, 0);
        if (checkCollision(tetromino))
        {
            tetromino.move(-1, 0);
        }
        break;

    case 'w':
        tetromino.rotate();
        if (checkCollision(tetromino))
        {
            tetromino.undoRotate();
        }
        break;

    case ' ':
        tetromino.move(0, 1);
        if (checkCollision(tetromino))
        {
            tetromino.move(0, -1);
            lockBlock();
        }
        break;

    case 'q':
        isRunning = false;
        break;

    default:
        break;
    }
}

bool Game::checkCollision(Tetromino tetromino)
{
    for (int i = 0; i < TETROMINO_BLOCK_COUNT; i++)
    {
        if (tetromino.getPointX(i) < 0 || tetromino.getPointX(i) >= width || tetromino.getPointY(i) < -1 || tetromino.getPointY(i) >= height)
        {
            return true;
        }
        if (field[tetromino.getPointY(i)][tetromino.getPointX(i)] != 0)
        {
            return true;
        }
    }
    return false;
}

void Game::lockBlock()
{
    for (int i = 0; i < TETROMINO_BLOCK_COUNT; i++)
    {
        field[tetromino.getPointY(i)][tetromino.getPointX(i)] = tetromino.getColorId();
    }
    tetromino = tetrominoNext;
    tetrominoNext = Tetromino();
}

int Game::clearFullRows()
{
    int completed = 0;
    for (int row = height - 1; row >= 0; row--)
    {
        bool isFull = true;
        for (int column = 0; column < width; column++)
        {
            if (field[row][column] == 0)
            {
                isFull = false;
            }
        }
        if (isFull)
        {
            for (int column = 0; column < width; column++)
            {
                field[row][column] = 0;
            }
            completed++;
        }
        else if (completed > 0)
        {
            for (int column = 0; column < width; column++)
            {
                field[row + completed][column] = field[row][column];
                field[row][column] = 0;
            }
        }
    }
    return completed;
}