#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "cursor_function.h"
#include "main_character.h"
#include "block_function.h"
#include "boss_zombie.h"
#include "setting_map.h"

int main()
{
    RemoveCursor();
    srand(time(0));
    system("mode con cols=130 lines=40"); //콘솔창 크기 조절

    DrawGameBoard();
    SettingMap();

    SetCurrentCursorPos(main_character_position.X, main_character_position.Y);
    ShowBlock(main_character);
    MakeBossZombie();
    while (1)
    {
        ShowBossZombie();
        //ShowEnergyWave();
        ProcessKeyInput(30);
        DeleteBossZombie();
        //DeleteEnergyWave();
        //MoveEnergyWave();
        MoveBossZombie();
    }
    return 0;
}