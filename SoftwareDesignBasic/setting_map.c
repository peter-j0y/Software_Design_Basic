//#pragma once
#include "zombie_world.h"

int score = 0, life = 3, stage = 3, weapon = 3;  //점수, 생명력, 스테이지, 무기의 변수
const char* weapon_name[5] = { "권총", "기관단총", "샷건", "저격총", "바주카" }; //무기 종류

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
    SetCurrentCursorPos(LIFE_X, LIFE_Y);
    for (int i = 0; i < life; i++) {
        printf("♥ ");
    }
}
void WeaponSetting() {
    SetCurrentCursorPos(USE_WEAPON_X, USE_WEAPON_Y);
    for (int i = 1; i <= 5; i++) {
        if (i == weapon)
            printf("%s", weapon_name[i - 1]);
    }
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