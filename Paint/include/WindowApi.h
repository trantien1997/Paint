#include <Windows.h>

class WindowApi
{
public:
    static void gotoxy(int x, int y) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = {x, y};
        SetConsoleCursorPosition(hConsole, pos);
    }

    static void resizeConsole(int width, int height) {
        HWND console = GetConsoleWindow();
        RECT r;
        GetWindowRect(console, &r);
        MoveWindow(console, r.left, r.top, width, height, TRUE);
    }
};