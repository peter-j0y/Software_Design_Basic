#pragma once
#include <Windows.h>
#include <conio.h>
#include "cursor_function.h"
#include "block_function.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define INITIAL_MAIN_CHARACTER_POS_X 65
#define INITIAL_MAIN_CHARACTER_POS_Y 20

extern COORD main_character_position = { INITIAL_MAIN_CHARACTER_POS_X ,INITIAL_MAIN_CHARACTER_POS_Y };

char main_character[4][4] =                     // 메인 캐릭터 표시
{
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};

void ShiftUp()                                  // 상하좌우 움직임
{
    DeleteBlock(main_character);
    SetCurrentCursorPos(main_character_position.X, main_character_position.Y -= 1);
    ShowBlock(main_character);
}

void ShiftDown()
{
    DeleteBlock(main_character);
    SetCurrentCursorPos(main_character_position.X, main_character_position.Y += 1);
    ShowBlock(main_character);
}

void ShiftRight()
{
    DeleteBlock(main_character);
    SetCurrentCursorPos(main_character_position.X += 2, main_character_position.Y);
    ShowBlock(main_character);
}

void ShiftLeft()
{
    DeleteBlock(main_character);
    SetCurrentCursorPos(main_character_position.X -= 2, main_character_position.Y);
    ShowBlock(main_character);
}

void ProcessKeyInput()              // 방향키를 입력받아 움직이는 함수 적용
{
    int key_input;
    for (int i = 0; i < 20; i++)
    {
        if (_kbhit() != 0)
        {
            key_input = _getch();
            switch (key_input)
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