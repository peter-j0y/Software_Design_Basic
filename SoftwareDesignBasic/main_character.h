#pragma once
#include <windows.h>
#include "cursor_function.h"
#include "block_function.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

char main_character[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};

void ShiftUp()
{
    COORD curPos = GetCurrentCursorPos();
    DeleteBlock(main_character);
    SetCurrentCursorPos(curPos.X, curPos.Y - 1);
    ShowBlock(main_character);
}

void ShiftDown()
{
    COORD curPos = GetCurrentCursorPos();
    DeleteBlock(main_character);
    SetCurrentCursorPos(curPos.X, curPos.Y + 1);
    ShowBlock(main_character);
}

void ShiftRight()
{
    COORD curPos = GetCurrentCursorPos();
    DeleteBlock(main_character);
    SetCurrentCursorPos(curPos.X + 2, curPos.Y);
    ShowBlock(main_character);
}

void ShiftLeft()
{
    COORD curPos = GetCurrentCursorPos();
    DeleteBlock(main_character);
    SetCurrentCursorPos(curPos.X - 2, curPos.Y);
    ShowBlock(main_character);
}

void ProcessKeyInput()
{
    int i, key;
    for (i = 0; i < 20; i++)
    {
        if (_kbhit() != 0)
        {
            key = _getch();
            switch (key)
            {
            case LEFT:
                ShiftLeft();
                break;
            case RIGHT:
                ShiftRight();
                break;
            case UP:
                ShiftUp();
                break;
            case DOWN:
                ShiftDown();
                break;
            }
        }
        Sleep(30);
    }
}