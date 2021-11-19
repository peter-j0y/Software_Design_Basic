#include "zombie_world.h"


int main()
{   
    shoot_start = clock();
    gun_start = clock();
    RemoveCursor();
    srand(time(0));
    system("mode con cols=130 lines=40"); //콘솔창 크기 조절

    DrawGameBoard();
    SettingMap();

    RandomItem();
    ShowItem();
  
    SetCurrentCursorPos(main_character_position.X, main_character_position.Y);
    ShowBlock(main_character[main_character_id]);
    MakeBossZombie();
    MakeNormalZombie();
    ShowBossZombie();
    ShowNormalZombie();
    while (1)
    {
        ShowEnergyWave();
        ProcessKeyInput(30);
        MoveNormalZombie();
        MoveEnergyWave();
        MoveBossZombie();
        //DeleteEnergyWave();
    }
    return 0;
}
