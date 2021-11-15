#include "zombie_world.h"

int main()
{
    RemoveCursor();
    srand(time(0));
    system("mode con cols=130 lines=40"); //콘솔창 크기 조절

    DrawGameBoard();
    SettingMap();

    SetCurrentCursorPos(main_character_position.X, main_character_position.Y);
    ShowBlock(main_character[main_character_id]);
    MakeBossZombie();
    MakeNormalZombie();
    while (1)
    {
        ShowBossZombie();
        ShowNormalZombie();
        ShowEnergyWave();
        ProcessKeyInput(30);
        DeleteBossZombie();
        DeleteNormalZombie();
        DeleteEnergyWave();
        MoveEnergyWave();
        MoveNormalZombie();
        MoveBossZombie();
    }
    return 0;
}
