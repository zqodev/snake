#include <windows.h>

void set_console_color(int textColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorCode = textColor;
    SetConsoleTextAttribute(hConsole, colorCode);
}