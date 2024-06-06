#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "Utility.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

class LeaderBoard
{
public:
    LeaderBoard(std::string fileName);
    void print();
    void save(std::string name, int score);

private:
    std::string fileName;
    std::vector<std::pair<std::string, int>> results;
};

#endif