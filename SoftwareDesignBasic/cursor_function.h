#pragma once
#include <windows.h>
void RemoveCursor(void)             // 깜박이는 커서를 제거하기 위한 함수
{
    CONSOLE_CURSOR_INFO current_info;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &current_info);
    current_info.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &current_info);
}

void SetCurrentCursorPos(int x, int y)                  // 커서의 위치를 설정하는 함수
{
    COORD position = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

COORD GetCurrentCursorPos(void)                         // 현재 커서의 위치를 반환하는 함수
{
    COORD current_position;
    CONSOLE_SCREEN_BUFFER_INFO current_info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &current_info);
    current_position.X = current_info.dwCursorPosition.X;
    current_position.Y = current_info.dwCursorPosition.Y;

    return current_position;
}