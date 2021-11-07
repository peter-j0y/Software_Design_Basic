#pragma once
#include <windows.h>
#include <stdio.h>
#include "cursor_function.h"
#include "main_character.h"

void DeleteBlock(char main_character[4][4])               // 출력된 블록을 삭제하는 함수
{
    int y, x;
    COORD curPos = GetCurrentCursorPos();
    for (y = 0; y < 4; y++)
    {
        for (x = 0; x < 4; x++)
        {
            SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
            if (main_character[y][x] == 1)
                printf("  ");
        }
    }
    SetCurrentCursorPos(curPos.X, curPos.Y);
}

void ShowBlock(char main_character[4][4])                // 블록을 출력하는 함수
{
    int y, x;
    COORD curPos = GetCurrentCursorPos();
    for (y = 0; y < 4; y++)
    {
        for (x = 0; x < 4; x++)
        {
            SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
            if (main_character[y][x] == 1)               // if문을 제거하면 안된다 -> 다른 블록에 영향을 미칠 수 있기 때문에
                printf("■");
        }
    }
    SetCurrentCursorPos(curPos.X, curPos.Y);
}