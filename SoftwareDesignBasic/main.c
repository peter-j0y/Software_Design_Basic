#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "cursor_function.h"
#include "main_character.h"
#include "block_function.h"

int main()
{
    RemoveCursor();
    COORD current_pos = { 65, 20 };
    SetCurrentCursorPos(current_pos.X, current_pos.Y);
    ShowBlock(main_character);
    while (1)
    {
        ProcessKeyInput();
    }
    return 0;
}