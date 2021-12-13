//#pragma once
#include "zombie_world.h"

int score = 0, life = 3, stage = 1, weapon = 1;  //점수, 생명력, 스테이지, 무기의 변수
int stage_initial_flag[4] = { 0 };
const char* weapon_name[5] = { "권총", "기관단총", "샷건", "저격총", "바주카" }; //무기 종류
Stage_Info stage_info[5] = { {1,1,0,0,0,0},{3,10,0,0,0,0} ,{7,15,0,0,0,0} ,{10,20,0,0,0,0} ,{15,30,0,0,0,0} };  //보스좀비수, 일반좀비수, , 만든보스좀비수, 만든일반좀비수, 죽인보스좀비수, 죽인일반좀비수

int game_board[GBOARD_HEIGHT + 2][GBOARD_WIDTH + 2];

void DrawGameBoard() {
    int x, y;
    for (y = 0; y <= GBOARD_HEIGHT; y++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
        if (y == 0)
            printf("┌");
        else if (y == GBOARD_HEIGHT)
            printf("└");
        else
            printf("│");
    }

    for (y = 0; y <= GBOARD_HEIGHT; y++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);
        if (y == 0)
            printf("┐");
        else if (y == GBOARD_HEIGHT)
            printf("┘");
        else
            printf("│");
    }

    for (x = 1; x <= GBOARD_WIDTH * 2; x++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x, GBOARD_ORIGIN_Y);
        printf("─");
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
        printf("─");
    }

    for (int y = 0; y < GBOARD_HEIGHT + 2; y++)
    {
        for (int x = 0; x < GBOARD_WIDTH + 2; x++)
        {
            if (x == 0 || y == 0 || x == GBOARD_WIDTH || y == GBOARD_HEIGHT)
                game_board[y][x] = 1;
            else
                game_board[y][x] = 0;
        }
    }

    /*for (int i = 0; i <= GBOARD_HEIGHT; i++) {
        game_board[i][0] = 1;
        game_board[i][GBOARD_WIDTH + 2] = 1;
    }

    for (int i = 0; i < GBOARD_WIDTH + 2; i++) {
        game_board[0][i] = 1;
        game_board[GBOARD_HEIGHT + 1][i] = 1;
    }*/

}

void ScoreSetting() {
    SetCurrentCursorPos(SCORE_X, SCORE_Y);
    printf("%d", score);
}

void LifeSetting() {
    SetCurrentCursorPos(LIFE_X, LIFE_Y);
    for (int i = 0; i < 3; i++) {
        printf("    ");
    }
    if (life > 3) {
        life = 3;
    }
    SetCurrentCursorPos(LIFE_X, LIFE_Y);
    for (int i = 0; i < life; i++) {
        printf("♥ ");
    }
}
void WeaponSetting() {
    SetCurrentCursorPos(USE_WEAPON_X, USE_WEAPON_Y);
    for (int i = 1; i <= 5; i++) {
        if (i == weapon)
            printf("%s    ", weapon_name[i - 1]);
    }
    SetCurrentCursorPos(USABLE_WEAPON_X, USABLE_WEAPON_Y);
    for (int i = 1; i <= 5; i++) {
        if (i != weapon && i <= stage) {
            printf("%s  ", weapon_name[i - 1]);
        }
    }
    printf("                        ");
}
void StageSetting() {
    SetCurrentCursorPos(STAGE_X, STAGE_Y);
    for (int i = 0; i < stage; i++) {
        printf("★ ");
    }
}

void SettingMap() {
    SetCurrentCursorPos(SCORE_X - 8, SCORE_Y);
    puts("SCORE : ");
    SetCurrentCursorPos(STAGE_X - 8, STAGE_Y);
    puts("STAGE : ");
    SetCurrentCursorPos(LIFE_X - 7, LIFE_Y);
    puts("LIFE : ");
    SetCurrentCursorPos(USE_WEAPON_X - 17, USE_WEAPON_Y);
    puts("사용 중인 무기 : ");
    SetCurrentCursorPos(USABLE_WEAPON_X - 17, USABLE_WEAPON_Y);
    puts("교체 가능 무기 : ");

    ScoreSetting();
    LifeSetting();
    WeaponSetting();
    StageSetting();
}

void SetStage()
{
    if ((stage_info[stage - 1].killed_boss_zombie >= stage_info[stage - 1].number_of_boss_zombie) && (stage_info[stage - 1].killed_normal_zombie >= stage_info[stage - 1].number_of_normal_zombie)) {
        stage++;
        DeleteBlock(main_character[main_character_id]);
        main_character_position.X = INITIAL_MAIN_CHARACTER_POS_X;
        main_character_position.Y = INITIAL_MAIN_CHARACTER_POS_Y;
        SetCurrentCursorPos(INITIAL_MAIN_CHARACTER_POS_X, INITIAL_MAIN_CHARACTER_POS_Y);
        ShowBlock(main_character[main_character_id]);
        StageSetting();
        WeaponSetting();

        EnergyWave_Info* energy_wave = energy_wave_list_head;
        DeleteEnergyWave();
        while (energy_wave) {
            energy_wave = RemoveEnergyWave(energy_wave);
        }
        stage_start_flag = 1;
    }

    if (stage_start_flag == 1) {
        StageDraw();
        Sleep(2000);
        StageErase();
        stage_start_flag = 0;
    }

    if (stage == 2 && stage_initial_flag[0]==0)
    {
        int start_x, start_y;
        start_x = GBOARD_ORIGIN_X + 21;
        start_y = GBOARD_ORIGIN_Y + 7;

        SetCurrentCursorPos(start_x, start_y);
        printf("┌──────────────────────────────────────────────────────────────────┐");
        for (int i = 0; i < 35; i++)
        {
            game_board[7][10 + i] = 1;
        }
        SetCurrentCursorPos(start_x, ++start_y);
        printf("│                                                                  │ ");
        for (int i = 0; i < 34; i++)
        {
            game_board[8][10 + i] = 1;
        }
        SetCurrentCursorPos(start_x, ++start_y);
        printf("└──────────────────────────────────────────────────────────────────┘");
        for (int i = 0; i < 34; i++)
        {
            game_board[9][10 + i] = 1;
        }


        SetCurrentCursorPos(start_x, start_y+=16);
        printf("┌──────────────────────────────────────────────────────────────────┐");
        for (int i = 0; i < 34; i++)
        {
            game_board[25][10 + i] = 1;
        }
        SetCurrentCursorPos(start_x, ++start_y);
        printf("│                                                                  │ ");
        for (int i = 0; i < 34; i++)
        {
            game_board[26][10 + i] = 1;
        }
        SetCurrentCursorPos(start_x, ++start_y);
        printf("└──────────────────────────────────────────────────────────────────┘");
        for (int i = 0; i < 34; i++)
        {
            game_board[27][10 + i] = 1;
        }
        /*for (int i = 0; i < 40; i++)
        {
            SetCurrentCursorPos(GBOARD_ORIGIN_X+19+i, GBOARD_ORIGIN_Y+10);
            if (i == 0)
                printf("┌");
            else {
                printf("─");
            }
            if(i<20)
                game_board[10][9+i] = 1;
        }*/

        /*for (int i = 1; i < 5; i++)
        {
            SetCurrentCursorPos(GBOARD_ORIGIN_X + 19, GBOARD_ORIGIN_Y + 10 + i);
            printf("│");
            game_board[10 + i][9] = 1;
        }*/
        
        stage_initial_flag[0] = 1;
    }
}

void resetGame()
{
    stage = 1;
    weapon = 1;

    DeleteBlock(main_character[main_character_id]);
    main_character_position.X = INITIAL_MAIN_CHARACTER_POS_X;
    main_character_position.Y = INITIAL_MAIN_CHARACTER_POS_Y;
    SetCurrentCursorPos(INITIAL_MAIN_CHARACTER_POS_X, INITIAL_MAIN_CHARACTER_POS_Y);
    ShowBlock(main_character[main_character_id]);

    Boss_Zombie_Info* boss_zombie = boss_zombie_list_head;
    DeleteBossZombie();
    while (boss_zombie) {
        boss_zombie = RemoveBossZombie(boss_zombie);
    }
    Normal_Zombie_Info* normal_zombie = normal_zombie_list_head;
    DeleteNormalZombie();
    while (normal_zombie) {
        normal_zombie = RemoveNormalZombie(normal_zombie);
    }
    EnergyWave_Info* energy_wave = energy_wave_list_head;
    DeleteEnergyWave();
    while (energy_wave) {
        energy_wave = RemoveEnergyWave(energy_wave);
    }
    for (int i = 0; i < 5; i++) {
        stage_info[i].killed_boss_zombie = 0;
        stage_info[i].killed_normal_zombie = 0;
        stage_info[i].made_number_of_boss_zombie = 0;
        stage_info[i].made_number_of_normal_zombie = 0;
    }
}

void StageDraw() {
    int x = 40, y = 8;
    int num_x = x + 45, num_y = y;
    
    SetCurrentCursorPos(x, y++);
    printf(" ####   #####     ##        #####    ######    ");
    SetCurrentCursorPos(x, y++);
    printf("#         #      #  #      #         #         ");
    SetCurrentCursorPos(x, y++);
    printf(" ###      #     ######    #   ####   #####     ");
    SetCurrentCursorPos(x, y++);
    printf("    #     #    #      #    #    #    #         ");
    SetCurrentCursorPos(x, y++);
    printf("####      #   #        #    #####    ######    ");

    if (stage == 1) {
        SetCurrentCursorPos(num_x, num_y++);
        printf("  #   ");
        SetCurrentCursorPos(num_x, num_y++);
        printf(" ##   ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("  #   ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("  #   ");
        SetCurrentCursorPos(num_x, num_y++);
        printf(" ###  ");
    }
    if (stage == 2) {
        SetCurrentCursorPos(num_x, num_y++);
        printf("##### ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("    # ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("##### ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("#     ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("##### ");
    }
    if (stage == 3) {
        SetCurrentCursorPos(num_x, num_y++);
        printf("##### ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("    # ");
        SetCurrentCursorPos(num_x, num_y++);
        printf(" #### ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("    # ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("##### ");
    }
    if (stage == 4) {
        SetCurrentCursorPos(num_x, num_y++);
        printf("  # #   ");
        SetCurrentCursorPos(num_x, num_y++);
        printf(" #  #   ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("####### ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("    #   ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("    #   ");
    }
    if (stage == 5) {
        SetCurrentCursorPos(num_x, num_y++);
        printf("##### ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("#     ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("##### ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("    # ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("##### ");
    }
}

void StageErase() {
    int x = 40, y = 8;
    int num_x = x + 45, num_y = y;

    SetCurrentCursorPos(x, y++);
    printf("                                               ");
    SetCurrentCursorPos(x, y++);
    printf("                                               ");
    SetCurrentCursorPos(x, y++);
    printf("                                               ");
    SetCurrentCursorPos(x, y++);
    printf("                                               ");
    SetCurrentCursorPos(x, y++);
    printf("                                               ");

    if (stage == 1) {
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");        
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
    }
    if (stage == 2) {
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
    }
    if (stage == 3) {
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
    }
    if (stage == 4) {
        SetCurrentCursorPos(num_x, num_y++);
        printf("        ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("        ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("        ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("        ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("        ");
    }
    if (stage == 5) {
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
        SetCurrentCursorPos(num_x, num_y++);
        printf("      ");
    }
}