#include "LeaderBoard.h"

LeaderBoard::LeaderBoard(std::string fileName) : fileName(fileName) {}

void LeaderBoard::print()
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    std::ifstream fin(fileName);
    if (!fin)
    {
        std::u32string message = convert.from_bytes("Поки що немає результатів");
        int indentX = (WIDTH - static_cast<int>(message.length())) / 2;
        int indentY = (HEIGHT - 1) / 2;
        gotoxy(indentX, indentY);

        std::cout << convert.to_bytes(message) << std::endl;
    }
    else
    {
        std::string str;
        std::string name;
        results.clear();
        while (getline(fin, name) && results.size() < 10)
        {
            getline(fin, str);
            int result = stoi(str);
            results.push_back(make_pair(name, result));
        }

        if (results.empty())
        {
            std::u32string message = convert.from_bytes("Поки що немає результатів");
            int indentX = (WIDTH - static_cast<int>(message.length())) / 2;
            int indentY = (HEIGHT - 1) / 2;
            gotoxy(indentX, indentY);
            std::cout << convert.to_bytes(message) << std::endl;
        }
        else
        {
            int maxWidth = 0;
            for (auto pair : results)
            {
                std::u32string result_name = convert.from_bytes(pair.first);
                if (static_cast<int>(result_name.length()) > maxWidth)
                    maxWidth = static_cast<int>(result_name.length());
            }
            int indentX = (WIDTH - maxWidth) / 2 - 3; // 3 - " - "
            int indentY = (HEIGHT - results.size()) / 2;

            std::sort(results.begin(), results.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
                      { return a.second > b.second; });

            for (auto pair : results)
            {
                gotoxy(indentX, indentY++);
                std::cout << pair.first << " - " << pair.second << std::endl;
            }
        }
    }

    gotoxy(0, HEIGHT);
    std::cout << "Натисніть Enter щоб продовжити...";
    std::cin.get();

    fin.close();
}

void LeaderBoard::save(std::string name, int result)
{
    std::ifstream fin(fileName);
    if (!fin)
    {
        std::ofstream fout(fileName);

        fout << name << std::endl
             << result << std::endl;
        fout.close();
        return;
    }

    std::string temp_name;
    std::string str;
    bool isFound = false;
    results.clear();
    while (getline(fin, temp_name))
    {
        getline(fin, str);
        int temp_result = stoi(str);
        if (temp_name == name)
        {
            isFound = true;
            results.push_back(make_pair(temp_name, temp_result > result ? temp_result : result));
        }
        else
        {
            results.push_back(make_pair(temp_name, temp_result));
        }
    }

    if (!isFound)
    {
        results.push_back(make_pair(name, result));
    }

    std::ofstream fout(fileName);

    std::sort(results.begin(), results.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
              { return a.second > b.second; });

    for (auto pair : results)
    {
        fout << pair.first << std::endl
             << pair.second << std::endl;
    }

    fout.close();
}