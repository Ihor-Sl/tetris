#include "Utility.h"

void showMenu(std::vector<std::string> options, int &choice)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    choice = 0;

    int maxWidth = 0;
    for (std::string option : options)
    {
        std::u32string option32 = convert.from_bytes(option);
        if (static_cast<int>(option32.length()) > maxWidth)
            maxWidth = static_cast<int>(option32.length());
    }

    int indentX = (WIDTH - maxWidth) / 2;
    int indentY = (HEIGHT - options.size()) / 2;

    std::cout << "\033c";
    bool changed = true;
    while (true)
    {
        if (changed)
        {
            std::cout << "\033c";
            changed = false;
            for (int i = 0; i < static_cast<int>(options.size()); i++)
            {
                if (i == choice)
                {
                    gotoxy(indentX - 2, indentY + i);
                    std::cout << "> " << setColor(Color::Red) << options[i] << setColor(Color::Reset);
                }
                else
                {
                    gotoxy(indentX, indentY + i);
                    std::cout << options[i];
                }
            }
        }

        if (kbhit())
        {
            char key = tolower(_getch());
            if ((key == 'w') && choice > 0)
            {
                choice--;
                changed = true;
            }
            else if ((key == 's') && choice < static_cast<int>(options.size()) - 1)
            {
                choice++;
                changed = true;
            }
            else if (key == '\n')
            {
                std::cout << "\033c";
                break;
            }
        }
    }
    std::cout << "\033c";
}

void gotoxy(int x, int y)
{
    std::cout << "\033[" << y << ";" << x << "H";
}

std::string inputPlayerName()
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    std::string name = "";
    for (int i = 0; i < 10; i++)
    {
        std::cout << std::endl;
    }

    std::u32string message = convert.from_bytes("Введіть своє ім'я: ");
    int indentX = (WIDTH - static_cast<int>(message.length())) / 2;
    int indentY = (HEIGHT - 1) / 2;

    gotoxy(indentX, indentY);
    std::cout << convert.to_bytes(message);
    do
    {
        getline(std::cin, name);
        name.erase(0, name.find_first_not_of("\t\n\v\f\r "));
        name.erase(name.find_last_not_of("\t\n\v\f\r ") + 1);
    } while (name.length() == 0);

    message = convert.from_bytes("Привіт, ");
    indentX = (WIDTH - static_cast<int>(message.length())) / 2;
    indentY++;
    gotoxy(indentX, indentY);
    std::cout << convert.to_bytes(message) << name << std::endl;
    for (int i = 0; i < 10; i++)
    {
        std::cout << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return name;
}

void printBannerTetris()
{

    std::vector<std::string> T = {
        " _______ ",
        "|__   __|",
        "   | |   ",
        "   | |   ",
        "   | |   ",
        "   |_|   "};
    std::vector<std::string> E = {
        " _______  ",
        "|  _____| ",
        "| |____   ",
        "|  _____| ",
        "| |____   ",
        "|_______| "};
    std::vector<std::string> R = {
        " _______  ",
        "|  ___  \\ ",
        "| |   \\  \\",
        "| |___/  /",
        "|  ___  \\ ",
        "|_/   \\__\\"};
    std::vector<std::string> I = {
        " _______ ",
        "|__   __|",
        "   | |   ",
        "   | |   ",
        " __| |__ ",
        "|_______|"};
    std::vector<std::string> S = {
        "  _______ ",
        " /  _____|",
        "|  |____  ",
        " \\_____  \\",
        "  _____| |",
        " |_______/"};

    int indentX = (WIDTH - static_cast<int>(T[0].length() + 1) * 6) / 2;
    int indentY = (HEIGHT - T.size()) / 2;

    for (size_t i = 0; i < T.size(); i++)
    {
        gotoxy(indentX, indentY + i);
        std::cout << setColor(Color::Red) << T[i] << " "
                  << setColor(Color::Yellow) << E[i] << " "
                  << setColor(Color::Green) << T[i] << " "
                  << setColor(Color::Cyan) << R[i] << " "
                  << setColor(Color::Blue) << I[i] << " "
                  << setColor(Color::Magenta) << S[i]
                  << setColor(Color::Reset) << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

bool kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return true;
    }

    return false;
}

char _getch()
{
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}