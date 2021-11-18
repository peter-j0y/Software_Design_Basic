//#pragma once
#include "zombie_world.h"

Normal_Zombie_Info* normal_zombie_list_head = NULL;
int STAGE;

void PrintNormalZombie(int zombie_x, int zombie_y)
{
	int board_array_x = (zombie_x - GBOARD_ORIGIN_X) / 2;
	int board_array_y = zombie_y - GBOARD_ORIGIN_Y;

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			SetCurrentCursorPos(zombie_x + (x * 2), zombie_y + y);
			printf("◆");
			game_board[board_array_y + y][board_array_x + x] = ZOMBIE;
		}
	}
	SetCurrentCursorPos(zombie_x, zombie_y);
}
void DeletePrintedNormalZombie(int zombie_x, int zombie_y)
{
	int board_array_x = (zombie_x - GBOARD_ORIGIN_X) / 2;
	int board_array_y = zombie_y - GBOARD_ORIGIN_Y;

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			SetCurrentCursorPos(zombie_x + (x * 2), zombie_y + y);
			printf("  ");
			game_board[board_array_y + y][board_array_x + x] = 0;
		}
	}
	SetCurrentCursorPos(zombie_x, zombie_y);
}

void ShowNormalZombie() {
	Normal_Zombie_Info* normal_zombie = normal_zombie_list_head;
	while (normal_zombie != NULL) {
		SetCurrentCursorPos(normal_zombie->x, normal_zombie->y);
		PrintNormalZombie(normal_zombie->x, normal_zombie->y);
		normal_zombie = normal_zombie->next;
	}
}

void ShowOneNormalZombie(Normal_Zombie_Info* normal_zombie) {
	SetCurrentCursorPos(normal_zombie->x, normal_zombie->y);
	PrintNormalZombie(normal_zombie->x, normal_zombie->y);
}

void DeleteNormalZombie() {
	Normal_Zombie_Info* normal_zombie = normal_zombie_list_head;
	while (normal_zombie != NULL) {
		SetCurrentCursorPos(normal_zombie->x, normal_zombie->y);
		DeletePrintedNormalZombie(normal_zombie->x, normal_zombie->y);
		normal_zombie = normal_zombie->next;
	}
}

void DeleteOneNormalZombie(Normal_Zombie_Info* normal_zombie) {
	SetCurrentCursorPos(normal_zombie->x, normal_zombie->y);
	DeletePrintedNormalZombie(normal_zombie->x, normal_zombie->y);
}

void MoveNormalZombie() {
	int dir;

	Normal_Zombie_Info* normal_zombie = normal_zombie_list_head;
	while (normal_zombie != NULL) {
		DeleteOneNormalZombie(normal_zombie);
		dir = rand() % 2;

		if (main_character_position.X - normal_zombie->x == 0) {
			dir = 1;
		}
		else if (main_character_position.Y - normal_zombie->y == 0) {
			dir = 0;
		}

		if (dir == 0)
		{
			if (main_character_position.X - normal_zombie->x < 0)
			{
				if (!NormalZombieDetectCollision(normal_zombie->x - 2, normal_zombie->y))
					normal_zombie->x -= 2;
			}
			else
			{
				if (!NormalZombieDetectCollision(normal_zombie->x + 2, normal_zombie->y))
					normal_zombie->x += 2;
			}
		}
		else if (dir == 1)
		{
			if (main_character_position.Y - normal_zombie->y < 0)
			{
				if (!NormalZombieDetectCollision(normal_zombie->x, normal_zombie->y - 1))
					normal_zombie->y--;
			}
			else
			{
				if (!NormalZombieDetectCollision(normal_zombie->x, normal_zombie->y + 1))
					normal_zombie->y++;
			}
		}
		ShowOneNormalZombie(normal_zombie);
		normal_zombie = normal_zombie->next;
	}
}

void MakeNormalZombie() {
	int x, y;
	int n = STAGE;
	int cnt = 0;

	Normal_Zombie_Info* normal_zombie = (Normal_Zombie_Info*)malloc(sizeof(Normal_Zombie_Info));
	normal_zombie->x = GBOARD_ORIGIN_X + GBOARD_WIDTH / 2 + 1;                                //좀비 리스폰 위치 추후 변경가능
	normal_zombie->y = GBOARD_ORIGIN_Y + 5;
	normal_zombie->next = NULL;
	if (normal_zombie_list_head == NULL) {
		normal_zombie_list_head = normal_zombie;
		return;
	}
	Normal_Zombie_Info* last_normal_zombie = normal_zombie_list_head;
	while (last_normal_zombie->next != NULL) {
		last_normal_zombie = last_normal_zombie->next;
	}
	last_normal_zombie->next = normal_zombie;



	//Num = (NormalZombie*)malloc(n * sizeof(NormalZombie));				// 스테이지 값을 이용한 연산으로 스테이지에 따라 일반 좀비의 숫자를 조절

}

void RemoveNormalZombie(Normal_Zombie_Info* dead_normal_zombie) {
	Normal_Zombie_Info* normal_zombie = normal_zombie_list_head;
	Normal_Zombie_Info* prev = NULL;
	while (normal_zombie != dead_normal_zombie) {
		prev = normal_zombie;
		normal_zombie = normal_zombie->next;
	}
	if (prev == NULL) {
		normal_zombie_list_head = NULL;
	}
	prev->next = dead_normal_zombie->next;
	free(dead_normal_zombie);
}

int NormalZombieDetectCollision(int position_x, int position_y)
{
	int check_another_zombie = 0;
	int board_array_x = (position_x - GBOARD_ORIGIN_X) / 2;
	int board_array_y = position_y - GBOARD_ORIGIN_Y;

	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			if (game_board[board_array_y + y][board_array_x + x] == MAP_BOUNDARY)
			{
				return 1;
			}
			if (game_board[board_array_y + y][board_array_x + x] == PLAYER || game_board[board_array_y + y][board_array_x + x] == PLAYER_RIGHT)
			{
				LifeDecrease();
				return 1;
			}
			if (game_board[board_array_y + y][board_array_x + x] == ZOMBIE)
			{
				return 1;
			}
			if (game_board[board_array_y][board_array_x] == GUN)
			{
				;
			}
			if (game_board[board_array_y + y][board_array_x + x] == ENERGY_WAVE)
			{
				EnergyWave_Info* remove_energy_wave = FindEnergyWave(position_x + x * 2, position_y + y);
				if (remove_energy_wave != NULL)
					RemoveEnergyWave(remove_energy_wave);
				return 1;
			}
			if (game_board[board_array_y + y][board_array_x + x] == ITEM)
			{
				return 1;
			}
		}
	}

	return 0;
}