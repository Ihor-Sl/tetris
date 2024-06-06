#include "Game.h"
#include "Utility.h"
#include "LeaderBoard.h"

#include <locale>
#include <vector>

int main()
{
    std::setlocale(LC_ALL, "");
    srand(time(0));
    std::cout << "\e[8;" << HEIGHT << ";" << WIDTH << "t";

    system("clear");
    printBannerTetris();
    
    system("clear");

    std::string playerName = inputPlayerName();

    std::vector<std::string> menuOptions = {
        "Почати гру",
        "Змінити ім'я",
        "Список лідерів",
        "Вибір складності",
        "Вихід"};

    std::vector<std::string> difficulties = {
        "Легко (1 очко за лінію)",
        "Нормально (4 очки за лінію)",
        "Важко (7 очків за лінію)"};

    LeaderBoard leaderBoard("leaderboard.txt");

    int score;
    int choice;
    int difficulty = 1;

    while (true)
    {
        Game game;
        showMenu(menuOptions, choice);

        switch (choice)
        {
        case 0:
            score = game.run(difficulty);
            leaderBoard.save(playerName, score);
            break;
        case 1:
            playerName = inputPlayerName();
            break;
        case 2:
            leaderBoard.print();
            break;
        case 3:
            showMenu(difficulties, difficulty);
            break;
        case 4:
            return 0;
        }
    }

    return 0;
}