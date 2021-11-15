#pragma once
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

//////////////////////////////////////bosszombie.h에 있던거/////////////////////////////////////
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

extern Boss_Zombie_Info* boss_zombie_list_head;
extern EnergyWave_Info* energy_wave_list_head;

void MakeBossZombie();                      //보스좀비 생성
void ShowBossZombie();                      //보스좀비들 화면에 출력
void MoveBossZombie();                      //보스좀비 이동
void DeleteBossZombie();                    //보스좀비들 화면에서 삭제
void RemoveBossZombie(Boss_Zombie_Info* dead_boss_zombie); //보스좀비 개체삭제
void MakeEnergyWave(COORD pos, int direction_x, int direction_y);          //에너지파 생성
void ShowEnergyWave();                      //보스좀비의 에너지파 화면 출력
void MoveEnergyWave();
void DeleteEnergyWave();                    //보스좀비의 에너지파 화면에서 삭제
EnergyWave_Info* RemoveEnergyWave(EnergyWave_Info* remove_energy_wave);         //에너지파 제거 
int BossZombieDetectCollision(int x, int y);                                    //보스좀비충돌 감지
int EnergyWaveDetectCollision(int x, int y);                                    //에너지파 충돌 감지
void SetGameBoardEnergyWave(COORD pos);                                      //에너지파의 위치 게임보드에 설정
void PrintBossZombie(COORD pos);                                             //3x3모양의 보스좀비 출력
void DeletePrintedBossZombie(COORD pos);                                     //3x3모양의 보스좀비 삭제    

void RemoveCursor(void);
void SetCurrentCursorPos(int x, int y);
COORD GetCurrentCursorPos(void);

//////////////////////////////////////bosszombie.h에 있던거/////////////////////////////////////


//////////////////////////////////////mainchar.h에 있던거/////////////////////////////////////
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define INITIAL_MAIN_CHARACTER_POS_X 65
#define INITIAL_MAIN_CHARACTER_POS_Y 20

extern COORD main_character_position;
extern int main_character_id;
extern int invincibility_flag;

extern char main_character[][2][2];               // 메인 캐릭터 표시


void DeleteBlock(char main_character[2][2]);
void ShowBlock(char main_character[2][2]);
void ShiftUp();
void ShiftDown();
void ShiftRight();
void ShiftLeft();
void ProcessKeyInput(int time);
void LifeDecrease(int damaged);
int MainCharacterDetectCollision(int position_x, int position_y, char main_character[2][2]);

//////////////////////////////////////mainchar.h에 있던거/////////////////////////////////////

//////////////////////////////////////normal_zombie.h에 있던거/////////////////////////////////////
typedef struct Normal_Zombie_Info {
    int x;
    int y;
    int hp;
    struct Normal_Zombie_Info* next;
}Normal_Zombie_Info;

extern Normal_Zombie_Info* normal_zombie_list_head;

extern int STAGE;																// 스테이지										
void PrintNormalZombie(int zombie_x, int zombie_y);
void DeletePrintedNormalZombie(int zombie_x, int zombie_y);
void MakeNormalZombie();												// 일반 좀비 리스폰 위치에 랜덤으로 생성
void ShowNormalZombie();												// 일반좀비들 화면에 출력
void DeleteNormalZombie();												// 일반좀비들 이동을 위해 화면에서 삭제
void MoveNormalZombie();                      // 일반좀비 이동
void RemoveNormalZombie(Normal_Zombie_Info* dead_normal_zombie);		// 일반좀비 개체삭제(체력이 0이 되면 삭제)
int NormalZombieDetectCollision(int x, int y);							// 일반좀비 충돌감지

//////////////////////////////////////normal_zombie.h에 있던거/////////////////////////////////////

//////////////////////////////////////setting_map.h에 있던거/////////////////////////////////////

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

#define MAP_BOUNDARY 1
#define PLAYER 2
#define ZOMBIE 3
#define GUN 4
#define ITEM 5
#define ENERGY_WAVE 6
#define PLAYER_RIGHT 7


extern int score, life, stage, weapon; //점수, 생명력, 스테이지, 무기의 변수
extern const char* weapon_name[5]; //무기 종류

extern int game_board[GBOARD_HEIGHT + 2][GBOARD_WIDTH + 2];


void DrawGameBoard();
void ScoreSetting();
void LifeSetting();
void WeaponSetting();
void StageSetting();
void SettingMap();
//////////////////////////////////////setting_map.h에 있던거/////////////////////////////////////
