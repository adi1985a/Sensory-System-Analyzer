#pragma once
#include <windows.h>
#include <string>
#include <iostream>

namespace helpers {
    enum ConsoleColor {
        COL_DEFAULT = 7,
        COL_HIGHLIGHT = 14,  // Yellow
        COL_SUCCESS = 10,    // Green
        COL_ERROR = 12,      // Red
        COL_INFO = 11        // Light Cyan
    };

    void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void drawLine(char symbol = '-', int length = 50) {
        std::string line(length, symbol);
        std::cout << line << std::endl;
    }

    void clearScreen() {
        system("cls");
    }

    void waitForKeyPress() {
        std::cout << "\nPress any key to continue...";
        std::cin.ignore();
        std::cin.get();
    }
}
