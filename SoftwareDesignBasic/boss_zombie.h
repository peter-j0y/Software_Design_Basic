#pragma once

#include <stdio.h>
#include "setting_map.h"
#include "main_character.h"

typedef struct Boss_Zombie_Info {
    COORD pos;
    int cool_time;
    struct Boss_Zombie_Info* next;
}Boss_Zombie_Info;

typedef struct EnergyWave_Info {
    COORD pos;
    int direction_x;
    int direction_y;
    struct EnergyWave_Info* next;
}EnergyWave_Info;

Boss_Zombie_Info* boss_zombie_list_head = NULL;
EnergyWave_Info* energy_wave_list_head = NULL;

void MakeBossZombie();                      //보스좀비 생성
void ShowBossZombie();                      //보스좀비들 화면에 출력
void MoveBossZombie();                      //보스좀비 이동
void DeleteBossZombie();                    //보스좀비들 화면에서 삭제
void RemoveBossZombie(Boss_Zombie_Info* dead_boss_zombie); //보스좀비 개체삭제
void MakeEnergyWave(int x, int y);          //에너지파 생성
void ShowEnergyWave();                      //보스좀비의 에너지파 화면 출력
void DeleteEnergyWave();                    //보스좀비의 에너지파 화면에서 삭제
EnergyWave_Info* RemoveEnergyWave(EnergyWave_Info* remove_energy_wave);         //에너지파 제거 
int BossZombieDetectCollision(int x, int y);                                    //보스좀비충돌 감지
int EnergyWaveDetectCollision(int x, int y);                                    //에너지파 충돌 감지
void SetGameBoardEnergyWave(int x, int y);                                      //에너지파의 위치 게임보드에 설정
void PrintBossZombie(int x, int y);                                             //3x3모양의 보스좀비 출력
void DeletePrintedBossZombie(int x, int y);                                     //3x3모양의 보스좀비 삭제    


void SetGameBoardEnergyWave(COORD pos)
{
    int board_array_x = (pos.X - GBOARD_ORIGIN_X) / 2;
    int board_array_y = pos.Y - GBOARD_ORIGIN_Y;
    if (game_board[board_array_y][board_array_x] == ENERGY_WAVE)
        game_board[board_array_y][board_array_x] = 0;
    else
        game_board[board_array_y][board_array_x] = ENERGY_WAVE;
}

void PrintBossZombie(COORD pos)
{
    int board_array_x = (pos.X - GBOARD_ORIGIN_X) / 2;
    int board_array_y = pos.Y - GBOARD_ORIGIN_Y;

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            SetCurrentCursorPos(pos.X + (x * 2), pos.Y + y);
            if (y == 1 && x == 1)
                printf("◈");
            else
                printf("※");
            game_board[board_array_y + y][board_array_x + x] = ZOMBIE;
        }
    }
    SetCurrentCursorPos(pos.X, pos.Y);
}
void DeletePrintedBossZombie(COORD pos)
{
    int board_array_x = (pos.X - GBOARD_ORIGIN_X) / 2;
    int board_array_y = pos.Y - GBOARD_ORIGIN_Y;

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            SetCurrentCursorPos(pos.X + (x * 2), pos.Y + y);
            printf("  ");
            game_board[board_array_y + y][board_array_x + x] = 0;
        }
    }
    SetCurrentCursorPos(pos.X, pos.Y);
}

void ShowBossZombie() {
    Boss_Zombie_Info* boss_zombie = boss_zombie_list_head;
    while (boss_zombie != NULL) {
        SetCurrentCursorPos(boss_zombie->pos.X, boss_zombie->pos.Y);
        PrintBossZombie(boss_zombie->pos);
        boss_zombie = boss_zombie->next;
    }
}
void DeleteBossZombie() {
    Boss_Zombie_Info* boss_zombie = boss_zombie_list_head;
    while (boss_zombie != NULL) {
        SetCurrentCursorPos(boss_zombie->pos.X, boss_zombie->pos.Y);
        DeletePrintedBossZombie(boss_zombie->pos);
        boss_zombie = boss_zombie->next;
    }
}
void ShowEnergyWave() {
    EnergyWave_Info* energy_wave = energy_wave_list_head;
    while (energy_wave != NULL) {
        SetCurrentCursorPos(energy_wave->pos.X, energy_wave->pos.Y);
        SetGameBoardEnergyWave(energy_wave->pos);
        printf("o");
        energy_wave = energy_wave->next;
    }
}
void DeleteEnergyWave() {
    EnergyWave_Info* energy_wave = energy_wave_list_head;
    while (energy_wave != NULL) {
        SetCurrentCursorPos(energy_wave->pos.X, energy_wave->pos.Y);
        SetGameBoardEnergyWave(energy_wave->pos);
        printf(" ");
        energy_wave = energy_wave->next;
    }
}
void MoveEnergyWave() {
    EnergyWave_Info* energy_wave = energy_wave_list_head;
    while (energy_wave != NULL) {
        if (EnergyWaveDetectCollision(energy_wave->pos.X + energy_wave->direction_x * 2, energy_wave->pos.Y + energy_wave->direction_y * 2))
            energy_wave = RemoveEnergyWave(energy_wave);
        else
        {
            energy_wave->pos.X += energy_wave->direction_x * 2;
            energy_wave->pos.Y += energy_wave->direction_y;
            energy_wave = energy_wave->next;
        }
    }
}
void MakeEnergyWave(COORD pos, int direction_x, int direction_y) {
    EnergyWave_Info* energy_wave = (EnergyWave_Info*)malloc(sizeof(EnergyWave_Info));
    energy_wave->pos.X = pos.X + 2 + direction_x * 2 * 2;
    energy_wave->pos.Y = pos.Y + 1 + direction_y * 2;
    energy_wave->direction_x = direction_x;
    energy_wave->direction_y = direction_y;
    energy_wave->next = NULL;
    if (energy_wave_list_head == NULL) {
        energy_wave_list_head = energy_wave;
        return;
    }
    EnergyWave_Info* last_energy_wave = energy_wave_list_head;
    while (last_energy_wave->next != NULL) {
        last_energy_wave = last_energy_wave->next;
    }
    last_energy_wave->next = energy_wave;
}
void MoveBossZombie() {
    Boss_Zombie_Info* boss_zombie = boss_zombie_list_head;
    while (boss_zombie != NULL) {
        if ((main_character_position.X == boss_zombie->pos.X + 2 || main_character_position.Y == boss_zombie->pos.Y + 1)
          ||(main_character_position.X + 2 == boss_zombie->pos.X + 2 || main_character_position.Y + 1 == boss_zombie->pos.Y + 1)) {
            if (boss_zombie->cool_time % 3 != 0)
            {
                boss_zombie->cool_time++;
            }
            else 
            {
                int direction_x = 0;
                int direction_y = 0;
                boss_zombie->cool_time++;
                if (main_character_position.X == boss_zombie->pos.X + 2 || main_character_position.X + 2 == boss_zombie->pos.X + 2)
                    direction_y = main_character_position.Y - (boss_zombie->pos.Y + 1)< 0 ? -1 : 1;
                else
                    direction_x = main_character_position.X - (boss_zombie->pos.X + 2)< 0 ? -1 : 1;
                MakeEnergyWave(boss_zombie->pos, direction_x, direction_y);
            }
        }
        else {
            boss_zombie->cool_time = 0;
            if (rand() % 2) {
                if (main_character_position.X - boss_zombie->pos.X < 0) {
                    if(!BossZombieDetectCollision(boss_zombie->pos.X - 2, boss_zombie->pos.Y))
                        boss_zombie->pos.X -= 2;
                }
                else {
                    if (!BossZombieDetectCollision(boss_zombie->pos.X + 2, boss_zombie->pos.Y))
                        boss_zombie->pos.X += 2;
                }
            }
            else {
                if (main_character_position.Y - boss_zombie->pos.Y < 0) {
                    if (!BossZombieDetectCollision(boss_zombie->pos.X, boss_zombie->pos.Y - 1))
                        boss_zombie->pos.Y--;
                }
                else {
                    if (!BossZombieDetectCollision(boss_zombie->pos.X, boss_zombie->pos.Y + 1))
                        boss_zombie->pos.Y++;
                }
            }
        }
        boss_zombie = boss_zombie->next;
    }
}

void MakeBossZombie() {
    Boss_Zombie_Info* boss_zombie = (Boss_Zombie_Info*)malloc(sizeof(Boss_Zombie_Info));
    boss_zombie->pos.X = GBOARD_ORIGIN_X + GBOARD_WIDTH / 2 + 1;                                //좀비 리스폰 위치 추후 변경가능
    boss_zombie->pos.Y = GBOARD_ORIGIN_Y + 10;
    boss_zombie->cool_time = 0;
    boss_zombie->next = NULL;
    if (boss_zombie_list_head == NULL) {
        boss_zombie_list_head = boss_zombie;
        return;
    }
    Boss_Zombie_Info* last_boss_zombie = boss_zombie_list_head;
    while (last_boss_zombie->next != NULL) {
        last_boss_zombie = last_boss_zombie->next;
    }
    last_boss_zombie->next = boss_zombie;
}

void RemoveBossZombie(Boss_Zombie_Info* dead_boss_zombie) {
    Boss_Zombie_Info* boss_zombie = boss_zombie_list_head;
    Boss_Zombie_Info* prev = NULL;
    while (boss_zombie != dead_boss_zombie) {
        prev = boss_zombie;
        boss_zombie = boss_zombie->next;
    }
    if (prev == NULL) {
        boss_zombie_list_head = NULL;
    }
    prev->next = dead_boss_zombie->next;
    free(dead_boss_zombie);
}

EnergyWave_Info* RemoveEnergyWave(EnergyWave_Info* remove_energy_wave) {
    EnergyWave_Info* energy_wave = energy_wave_list_head;
    EnergyWave_Info* prev = NULL;
    while (energy_wave != remove_energy_wave) {
        prev = energy_wave;
        energy_wave = energy_wave->next;
    }
    if (prev == NULL) {
        EnergyWave_Info* first = remove_energy_wave->next;
        energy_wave_list_head = first;
        free(remove_energy_wave);
        return first;
    }
    prev->next = remove_energy_wave->next;
    free(remove_energy_wave);
    return prev->next;
}

int BossZombieDetectCollision(int x, int y)
{
    int board_array_x = (x - GBOARD_ORIGIN_X) / 2;
    int board_array_y = y - GBOARD_ORIGIN_Y;

    if (game_board[board_array_y][board_array_x] == MAP_BOUNDARY)
    {
        return 1;
    }
    else if (game_board[board_array_y][board_array_x] == PLAYER)
    {
        LifeDecrease();
        return 1;
    }
    else if (game_board[board_array_y][board_array_x] == GUN)
    {
        ;
    }
    else if (game_board[board_array_y][board_array_x] == ZOMBIE)
    {
        ;
    }
    return 0;
}

int EnergyWaveDetectCollision(int x, int y)
{
    int board_array_x = (x - GBOARD_ORIGIN_X) / 2;
    int board_array_y = y - GBOARD_ORIGIN_Y;

    if (game_board[board_array_y][board_array_x] == MAP_BOUNDARY)
    {
        return 1;
    }
    else if (game_board[board_array_y][board_array_x] == PLAYER)
    {
        LifeDecrease();
        return 1;
    }
    else if (game_board[board_array_y][board_array_x] == ZOMBIE)
    {
        return 1;
    }
    return 0;
}