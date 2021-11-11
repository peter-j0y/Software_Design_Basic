#pragma once
#include <stdio.h>
#include <windows.h>
#include "cursor_function.h"


#define GBOARD_ORIGIN_X 10  //게임보드가 존재하기 전 x축 공백
#define GBOARD_ORIGIN_Y 3   //게임보드가 존재하기 전 y축 공백

#define GBOARD_WIDTH 53     //게임보드의 크기 (경계선 포함 X)
#define GBOARD_HEIGHT 32    //게임보드의 크기 (경계선 포함 X)

#define SCORE_X 10          //SCORE, STAGE 등 화면에 보이는 UI의 좌표값들
#define SCORE_Y 1           //만약 SCORE 점수를 수정한다면    
#define STAGE_X 56          //SetCurrentPos에 SCORE_X, SCORE_Y를 넣고 점수를 적으면 됨
#define STAGE_Y 1
#define LIFE_X 107
#define LIFE_Y 1
#define USE_WEAPON_X 19
#define USE_WEAPON_Y 37
#define USABLE_WEAPON_X 57
#define USABLE_WEAPON_Y 37


extern int score = 0, life = 3, stage = 3, weapon = 3;  //점수, 생명력, 스테이지, 무기의 변수
extern const char* weapon_name[5] = { "권총", "기관단총", "샷건", "저격총", "바주카" }; //무기 종류

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

    for (x = 1; x <= GBOARD_WIDTH; x++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y);
        printf("─");
        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
        printf("─");
    }

    for (int i = 0; i <= GBOARD_HEIGHT; i++) {
        game_board[i][0] = 1;
        game_board[i][GBOARD_WIDTH + 2] = 1;
    }

    for (int i = 0; i < GBOARD_WIDTH + 2; i++) {
        game_board[0][i] = 1;
        game_board[GBOARD_HEIGHT + 1][i] = 1;
    }
}

void ScoreSetting() {
    SetCurrentCursorPos(SCORE_X, SCORE_Y);
    printf("%d", score);
}

void LifeSetting() {
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