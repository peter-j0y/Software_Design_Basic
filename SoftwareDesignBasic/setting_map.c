//#pragma once
#include "zombie_world.h"

int score = 0, life = 3, stage = 1, weapon = 1, get_vaccine = 0;  //점수, 생명력, 스테이지, 무기의 변수
int stage_initial_flag[4] = { 0 };
const char* weapon_name[5] = { "권총", "기관단총", "샷건", "저격총", "바주카" }; //무기 종류
Stage_Info stage_info[5] = { {1,3,0,0,0,0},{3,10,0,0,0,0} ,{7,15,0,0,0,0} ,{10,20,0,0,0,0} ,{15,30,0,0,0,0} };  //보스좀비수, 일반좀비수, , 만든보스좀비수, 만든일반좀비수, 죽인보스좀비수, 죽인일반좀비수

int game_board[GBOARD_HEIGHT + 2][GBOARD_WIDTH + 2];

void DrawGameBoard() {
    int x, y;
    for (y = 0; y <= GBOARD_HEIGHT; y++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
        if (y == 0)
            printf("▒");
        else if (y == GBOARD_HEIGHT)
            printf("▒");
        else
            printf("▒");
    }

    for (y = 0; y <= GBOARD_HEIGHT; y++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);
        if (y == 0)
            printf("▒");
        else if (y == GBOARD_HEIGHT)
            printf("▒");
        else
            printf("▒");
    }

    for (x = 1; x <= GBOARD_WIDTH * 2; x++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x, GBOARD_ORIGIN_Y);
        printf("▒");
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
        printf("▒");
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
}

void ScoreSetting() {
    SetCurrentCursorPos(SCORE_X, SCORE_Y);
    printf("%d", score);
}

void VaccineSetting()
{
    if (get_vaccine == 0)
    {
        SetCurrentCursorPos(USABLE_WEAPON_X + 35, USABLE_WEAPON_Y);
        printf("                                    ");
        SetCurrentCursorPos(USABLE_WEAPON_X + 35, USABLE_WEAPON_Y);
        printf("A동 백신 보관실에서 백신을 찾으세요!");
    }
    else
    {
        SetCurrentCursorPos(USABLE_WEAPON_X + 35, USABLE_WEAPON_Y);
        printf("                                    ");
        SetCurrentCursorPos(USABLE_WEAPON_X + 35, USABLE_WEAPON_Y);
        printf("백신 획득! 건물을 탈출하세요!");
    }
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
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("♥ ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    }
}

void WeaponSetting() {
    SetCurrentCursorPos(USE_WEAPON_X, USE_WEAPON_Y);
    for (int i = 1; i <= 5; i++) {
        if (i == weapon)
            printf("%s    ", weapon_name[i - 1]);
    }
    SetCurrentCursorPos(USABLE_WEAPON_X, USABLE_WEAPON_Y);
    printf("                                  ");
    SetCurrentCursorPos(USABLE_WEAPON_X, USABLE_WEAPON_Y);
    for (int i = 1; i <= 5; i++) {
        if (i != weapon && i <= stage) {
                printf("%s  ", weapon_name[i - 1]);
        }
    }
}

void StageSetting() {
    SetCurrentCursorPos(STAGE_X, STAGE_Y);
    for (int i = 0; i < stage; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("★ ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    switch (stage) {
    case 1: printf("(A동 3층 연구실 복도)");
        break;
    case 2 :printf("(A동 203호 연구실)");
        break;
    case 3:printf("(A동 백신 보관실)");
        break;
    case 4:printf("(A동 1층 로비)");
        break;
    case 5:printf("(운동장)");
        break;
    default:
        break;
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
    VaccineSetting();
    StageSetting();
}

void SetStage()
{
    ItemTimer();

    if ((stage_info[stage - 1].killed_boss_zombie >= stage_info[stage - 1].number_of_boss_zombie) && (stage_info[stage - 1].killed_normal_zombie >= stage_info[stage - 1].number_of_normal_zombie)) {
        if (stage == 3) {
            if (get_vaccine == 1)
            {
                stage++;
                DeleteItem();
                DeleteBlock(main_character[main_character_id]);
                main_character_position.X = INITIAL_MAIN_CHARACTER_POS_X;
                main_character_position.Y = INITIAL_MAIN_CHARACTER_POS_Y;
                
                StageSetting();
                WeaponSetting();
                EnergyWave_Info* energy_wave = energy_wave_list_head;
                DeleteEnergyWave();
                while (energy_wave) {
                    energy_wave = RemoveEnergyWave(energy_wave);
                }
                stage_start_flag = 1;
            }
        }
        else {
            stage++;
            DeleteItem();
            if (stage==6) {
                GameClear();
            }
            DeleteBlock(main_character[main_character_id]);
            main_character_position.X = INITIAL_MAIN_CHARACTER_POS_X;
            main_character_position.Y = INITIAL_MAIN_CHARACTER_POS_Y;
            
            StageSetting();
            WeaponSetting();
            EnergyWave_Info* energy_wave = energy_wave_list_head;
            DeleteEnergyWave();
            while (energy_wave) {
                energy_wave = RemoveEnergyWave(energy_wave);
            }
            stage_start_flag = 1;
        }
    }

    if (stage_start_flag == 1) {
        if (stage == 1)
        {
            StageDraw();
            Sleep(2000);
            StageErase();
            PrintStage1Map();
            SetCurrentCursorPos(INITIAL_MAIN_CHARACTER_POS_X, INITIAL_MAIN_CHARACTER_POS_Y);
            ShowBlock(main_character[main_character_id]);
            stage_start_flag = 0;
        }
        if (stage == 2)
        {
            RemoveStage1Map();
            StageDraw();
            Sleep(2000);
            StageErase();
            PrintStage2Map();
            SetCurrentCursorPos(INITIAL_MAIN_CHARACTER_POS_X, INITIAL_MAIN_CHARACTER_POS_Y);
            ShowBlock(main_character[main_character_id]);
            stage_start_flag = 0;
        }
        if (stage == 3)
        {
            RemoveStage2Map();
            StageDraw();
            Sleep(2000);
            StageErase();
            PrintStage3Map();
            SetCurrentCursorPos(INITIAL_MAIN_CHARACTER_POS_X, INITIAL_MAIN_CHARACTER_POS_Y);
            ShowBlock(main_character[main_character_id]);
            CreateVaccine();
            stage_start_flag = 0;
        }
        if (stage == 4)
        {
            RemoveStage3Map();
            StageDraw();
            Sleep(2000);
            StageErase();
            PrintStage4Map();
            SetCurrentCursorPos(INITIAL_MAIN_CHARACTER_POS_X, INITIAL_MAIN_CHARACTER_POS_Y);
            ShowBlock(main_character[main_character_id]);
            stage_start_flag = 0;
        }
        if (stage == 5)
        {
            RemoveStage4Map();
            StageDraw();
            Sleep(2000);
            StageErase();
            SetCurrentCursorPos(INITIAL_MAIN_CHARACTER_POS_X, INITIAL_MAIN_CHARACTER_POS_Y);
            ShowBlock(main_character[main_character_id]);
            stage_start_flag = 0;
        }
    }

}

void PrintStage1Map() {
    int start_x, start_y;
    start_x = GBOARD_ORIGIN_X + 31;
    start_y = GBOARD_ORIGIN_Y;

    for (int i = 1; i <= 10; i++)
    {
        SetCurrentCursorPos(start_x, ++start_y);
        printf("■");
        game_board[i][15] = 1;
    }

    start_y = GBOARD_ORIGIN_Y + 21;
    for (int i = 22; i <= 31; i++)
    {
        SetCurrentCursorPos(start_x, ++start_y);
        printf("■");
        game_board[i][15] = 1;
    }

    start_x = GBOARD_ORIGIN_X + 75;
    start_y = GBOARD_ORIGIN_Y;

    for (int i = 1; i <= 11; i++)
    {
        SetCurrentCursorPos(start_x, ++start_y);
        printf("■");
        game_board[i][37] = 1;
    }

    start_x = GBOARD_ORIGIN_X + 75;
    start_y = GBOARD_ORIGIN_Y + 21;

    for (int i = 22; i <= 31; i++)
    {
        SetCurrentCursorPos(start_x, ++start_y);
        printf("■");
        game_board[i][37] = 1;
    }

    start_x = GBOARD_ORIGIN_X + 2;
    start_y = GBOARD_ORIGIN_Y + 11;
    SetCurrentCursorPos(start_x, start_y);
    printf(" ■■■■■■■■■■■■■■■");

    for (int i = 2; i <= 15; i++)
        game_board[11][i] = 1;

    start_x = GBOARD_ORIGIN_X + 75;
    start_y = GBOARD_ORIGIN_Y + 11;
    SetCurrentCursorPos(start_x, start_y);
    printf("■■■■■■■■■■■■■■■■");

    for (int i = 37; i <= 51; i++)
        game_board[11][i] = 1;

    start_x = GBOARD_ORIGIN_X + 2;
    start_y = GBOARD_ORIGIN_Y + 21;
    SetCurrentCursorPos(start_x, start_y);
    printf(" ■■■■■■■■■■■■■■■");

    for (int i = 2; i <= 15; i++)
        game_board[21][i] = 1;

    start_x = GBOARD_ORIGIN_X + 75;
    start_y = GBOARD_ORIGIN_Y + 21;
    SetCurrentCursorPos(start_x, start_y);
    printf("■■■■■■■■■■■■■■■■");

    for (int i = 37; i <= 51; i++)
        game_board[21][i] = 1;
}

void RemoveStage1Map() {
    int start_x, start_y;
    start_x = GBOARD_ORIGIN_X + 31;
    start_y = GBOARD_ORIGIN_Y;

    for (int i = 1; i <= 10; i++)
    {
        SetCurrentCursorPos(start_x, ++start_y);
        printf("  ");
        game_board[i][15] = 0;
    }

    start_y = GBOARD_ORIGIN_Y + 21;
    for (int i = 22; i <= 31; i++)
    {
        SetCurrentCursorPos(start_x, ++start_y);
        printf("  ");
        game_board[i][15] = 0;
    }

    start_x = GBOARD_ORIGIN_X + 75;
    start_y = GBOARD_ORIGIN_Y;

    for (int i = 1; i <= 11; i++)
    {
        SetCurrentCursorPos(start_x, ++start_y);
        printf("  ");
        game_board[i][37] = 0;
    }

    start_x = GBOARD_ORIGIN_X + 75;
    start_y = GBOARD_ORIGIN_Y + 21;

    for (int i = 22; i <= 31; i++)
    {
        SetCurrentCursorPos(start_x, ++start_y);
        printf("  ");
        game_board[i][37] = 0;
    }

    start_x = GBOARD_ORIGIN_X + 2;
    start_y = GBOARD_ORIGIN_Y + 11;
    SetCurrentCursorPos(start_x, start_y);
    printf("                               ");

    for (int i = 2; i <= 15; i++)
        game_board[11][i] = 0;

    start_x = GBOARD_ORIGIN_X + 75;
    start_y = GBOARD_ORIGIN_Y + 11;
    SetCurrentCursorPos(start_x, start_y);
    printf("                                ");

    for (int i = 37; i <= 51; i++)
        game_board[11][i] = 0;

    start_x = GBOARD_ORIGIN_X + 2;
    start_y = GBOARD_ORIGIN_Y + 21;
    SetCurrentCursorPos(start_x, start_y);
    printf("                               ");

    for (int i = 2; i <= 15; i++)
        game_board[21][i] = 0;

    start_x = GBOARD_ORIGIN_X + 75;
    start_y = GBOARD_ORIGIN_Y + 21;
    SetCurrentCursorPos(start_x, start_y);
    printf("                                ");

    for (int i = 37; i <= 51; i++)
        game_board[21][i] = 0;
}

void PrintStage2Map()
{
    int start_x, start_y;
    start_x = GBOARD_ORIGIN_X + 21;
    start_y = GBOARD_ORIGIN_Y + 7;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[7][10 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[8][10 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[9][10 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 51;
    start_y = GBOARD_ORIGIN_Y + 7;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[7][25 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[8][25 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[9][25 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 81;
    start_y = GBOARD_ORIGIN_Y + 7;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[7][40 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[8][40 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[9][40 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 21;
    start_y = GBOARD_ORIGIN_Y + 23;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[23][10 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[24][10 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[25][10 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 51;
    start_y = GBOARD_ORIGIN_Y + 23;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[23][25 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[24][25 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[25][25 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 81;
    start_y = GBOARD_ORIGIN_Y + 23;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[23][40 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[23][40 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[23][40 + i] = 1;
}

void RemoveStage2Map()
{
    int start_x, start_y;
    start_x = GBOARD_ORIGIN_X + 21;
    start_y = GBOARD_ORIGIN_Y + 7;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[7][10 + i] = 0;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[8][10 + i] = 0;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[9][10 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 51;
    start_y = GBOARD_ORIGIN_Y + 7;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[7][25 + i] = 0;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[8][25 + i] = 0;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[9][25 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 81;
    start_y = GBOARD_ORIGIN_Y + 7;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[7][40 + i] = 0;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[8][40 + i] = 0;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[9][40 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 21;
    start_y = GBOARD_ORIGIN_Y + 23;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[23][10 + i] = 0;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[24][10 + i] = 0;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[25][10 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 51;
    start_y = GBOARD_ORIGIN_Y + 23;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[23][25 + i] = 0;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[24][25 + i] = 0;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[25][25 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 81;
    start_y = GBOARD_ORIGIN_Y + 23;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[23][40 + i] = 0;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[23][40 + i] = 0;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[23][40 + i] = 0;
}

void PrintStage3Map()
{
    int start_x, start_y;
    start_x = GBOARD_ORIGIN_X + 31;
    start_y = GBOARD_ORIGIN_Y + 7;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■■");
    for (int i = 0; i < 4; i++)
        game_board[7][15 + i] = 1;
    SetCurrentCursorPos(start_x, ++start_y);
    printf("■    ■");
    for (int i = 0; i < 4; i++)
        game_board[8][15 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■■");
    for (int i = 0; i < 4; i++)
        game_board[9][15 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 51;
    start_y = GBOARD_ORIGIN_Y + 14;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■■");
    for (int i = 0; i < 4; i++)
        game_board[14][25 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■    ■");
    for (int i = 0; i < 4; i++)
        game_board[15][25 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■■");
    for (int i = 0; i < 4; i++)
        game_board[16][25 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 71;
    start_y = GBOARD_ORIGIN_Y + 21;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■■");
    for (int i = 0; i < 4; i++)
        game_board[21][35 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■    ■");
    for (int i = 0; i < 4; i++)
        game_board[22][35 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■■");
    for (int i = 0; i < 4; i++)
        game_board[23][35 + i] = 1;
}

void RemoveStage3Map()
{
    int start_x, start_y;
    start_x = GBOARD_ORIGIN_X + 31;
    start_y = GBOARD_ORIGIN_Y + 7;

    SetCurrentCursorPos(start_x, start_y);
    printf("        ");
    for (int i = 0; i < 4; i++)
        game_board[7][15 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("        ");
    for (int i = 0; i < 4; i++)
        game_board[8][15 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("        ");
    for (int i = 0; i < 4; i++)
        game_board[9][15 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 51;
    start_y = GBOARD_ORIGIN_Y + 14;

    SetCurrentCursorPos(start_x, start_y);
    printf("        ");
    for (int i = 0; i < 4; i++)
        game_board[14][25 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("        ");
    for (int i = 0; i < 4; i++)
        game_board[15][25 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("        ");
    for (int i = 0; i < 4; i++)
        game_board[16][25 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 71;
    start_y = GBOARD_ORIGIN_Y + 21;

    SetCurrentCursorPos(start_x, start_y);
    printf("        ");
    for (int i = 0; i < 4; i++)
        game_board[21][35 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("        ");
    for (int i = 0; i < 4; i++)
        game_board[22][35 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("        ");
    for (int i = 0; i < 4; i++)
        game_board[23][35 + i] = 0;
}

void PrintStage4Map() {
    int start_x, start_y;
    start_x = GBOARD_ORIGIN_X + 51;
    start_y = GBOARD_ORIGIN_Y + 6;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[6][25 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[7][25 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[8][25 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 37;
    start_y = GBOARD_ORIGIN_Y + 10;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[10][18 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[11][18 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[12][18 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 65;
    start_y = GBOARD_ORIGIN_Y + 10;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[10][32 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[11][32 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[12][32 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 23;
    start_y = GBOARD_ORIGIN_Y + 14;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[14][11 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[15][11 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[16][11 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 79;
    start_y = GBOARD_ORIGIN_Y + 14;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[14][39 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[15][39 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[16][39 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 37;
    start_y = GBOARD_ORIGIN_Y + 19;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[19][18 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[20][18 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[21][18 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 65;
    start_y = GBOARD_ORIGIN_Y + 19;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[19][32 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[20][32 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[21][32 + i] = 1;

    start_x = GBOARD_ORIGIN_X + 51;
    start_y = GBOARD_ORIGIN_Y + 24;

    SetCurrentCursorPos(start_x, start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[24][25 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■  ■");
    for (int i = 0; i < 3; i++)
        game_board[25][25 + i] = 1;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("■■■");
    for (int i = 0; i < 3; i++)
        game_board[26][25 + i] = 1;
}

void RemoveStage4Map()
{
    int start_x, start_y;
    start_x = GBOARD_ORIGIN_X + 51;
    start_y = GBOARD_ORIGIN_Y + 6;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[6][25 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[7][25 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[8][25 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 37;
    start_y = GBOARD_ORIGIN_Y + 10;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[10][18 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[11][18 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[12][18 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 65;
    start_y = GBOARD_ORIGIN_Y + 10;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[10][32 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[11][32 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[12][32 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 23;
    start_y = GBOARD_ORIGIN_Y + 14;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[14][11 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[15][11 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[16][11 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 79;
    start_y = GBOARD_ORIGIN_Y + 14;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[14][39 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[15][39 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[16][39 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 37;
    start_y = GBOARD_ORIGIN_Y + 19;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[19][18 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[19][18 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[20][18 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 65;
    start_y = GBOARD_ORIGIN_Y + 19;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[21][32 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[20][32 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[21][32 + i] = 0;

    start_x = GBOARD_ORIGIN_X + 51;
    start_y = GBOARD_ORIGIN_Y + 24;

    SetCurrentCursorPos(start_x, start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[24][25 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[25][25 + i] = 0;

    SetCurrentCursorPos(start_x, ++start_y);
    printf("      ");
    for (int i = 0; i < 3; i++)
        game_board[26][25 + i] = 0;
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