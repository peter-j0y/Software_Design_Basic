#include "zombie_world.h"

// 게임 실행
void PlayGame() 
{
    system("mode con cols=130 lines=40"); //콘솔창 크기 조절
    shoot_start = clock();
    gun_start = clock();
    item_start = clock();
    item_flag = 1;

    srand(time(0));

    DrawGameBoard();
    SettingMap();

    SetCurrentCursorPos(main_character_position.X, main_character_position.Y);


    ShowBlock(main_character[main_character_id]);
    MakeBossZombie();
    MakeNormalZombie();
    ShowBossZombie();
    ShowNormalZombie();
    while (1)
    {
        item_end = clock();
        double time = (double)(item_end - item_start) / CLOCKS_PER_SEC;
        if (item_flag == 1 && time > 5) {
            RandomItem();
            ShowItem();
            item_flag = 0;
        }// 아이템 쿨 타임

        ShowEnergyWave();
        ProcessKeyInput(30);
        MoveNormalZombie();
        MoveEnergyWave();
        MoveBossZombie();
        //DeleteEnergyWave();
    }
}