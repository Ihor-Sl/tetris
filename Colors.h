#ifndef COLORS_H
#define COLORS_H

#include <string>

enum class Color {
    Reset = 0,
    Red = 91,
    Green = 92,
    Yellow = 93,
    Blue = 94,
    Magenta = 95,
    Cyan = 96,
    White = 97
};

inline std::string setColor(Color color) {
    return "\033[" + std::to_string(static_cast<int>(color)) + "m";
}

#endif