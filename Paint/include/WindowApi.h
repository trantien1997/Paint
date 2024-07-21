/***********************************************************
 *  WindowApi.h                                            *
 *  Created by Tien, NguyenTran on 07.20.2024.             *
 *  Copyright © 2024. All rights reserved.                 *
 ***********************************************************/

#pragma once

#include <Windows.h>

class WindowApi
{
public:
    /**
     * A function to move the console cursor to the specified coordinates.
     *
     * @param x the x-coordinate
     * @param y the y-coordinate
     *
     * @return void
     *
     * @throws N/A
     */
    static void gotoxy(int x, int y) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = {x, y};
        SetConsoleCursorPosition(hConsole, pos);
    }

    /**
     * A function to resize the console window to the specified width and height.
     *
     * @param width the new width of the console window
     * @param height the new height of the console window
     *
     * @return void
     *
     * @throws N/A
     */
    static void resizeConsole(int width, int height) {
        HWND console = GetConsoleWindow();
        RECT r;
        GetWindowRect(console, &r);
        MoveWindow(console, r.left, r.top, width, height, TRUE);
    }
};
