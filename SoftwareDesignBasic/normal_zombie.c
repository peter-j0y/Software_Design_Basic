//#pragma once
#include "zombie_world.h"

Normal_Zombie_Info* normal_zombie_list_head = NULL;
normal_zombie_start = 0;
normal_zombie_end = 0;
void PrintNormalZombie(int zombie_x, int zombie_y)
{
	int board_array_x = (zombie_x - GBOARD_ORIGIN_X) / 2;
	int board_array_y = zombie_y - GBOARD_ORIGIN_Y;

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			SetCurrentCursorPos(zombie_x + (x * 2), zombie_y + y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("◆");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
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
		SetCurrentCursorPos(normal_zombie->pos.X, normal_zombie->pos.Y);
		PrintNormalZombie(normal_zombie->pos.X, normal_zombie->pos.Y);
		normal_zombie = normal_zombie->next;
	}
}

void ShowOneNormalZombie(Normal_Zombie_Info* normal_zombie) {
	SetCurrentCursorPos(normal_zombie->pos.X, normal_zombie->pos.Y);
	PrintNormalZombie(normal_zombie->pos.X, normal_zombie->pos.Y);
}

void DeleteNormalZombie() {
	Normal_Zombie_Info* normal_zombie = normal_zombie_list_head;
	while (normal_zombie != NULL) {
		SetCurrentCursorPos(normal_zombie->pos.X, normal_zombie->pos.Y);
		DeletePrintedNormalZombie(normal_zombie->pos.X, normal_zombie->pos.Y);
		normal_zombie = normal_zombie->next;
	}
}

void DeleteOneNormalZombie(Normal_Zombie_Info* normal_zombie) {
	SetCurrentCursorPos(normal_zombie->pos.X, normal_zombie->pos.Y);
	DeletePrintedNormalZombie(normal_zombie->pos.X, normal_zombie->pos.Y);
}

void MoveNormalZombie() {
	int dir;
	double diff_x;
	double diff_y;
	Normal_Zombie_Info* normal_zombie = normal_zombie_list_head;

	while (normal_zombie != NULL) {
		DeleteOneNormalZombie(normal_zombie);
		dir = rand() % 2;

		diff_x = main_character_position.X - normal_zombie->pos.X;
		diff_y = main_character_position.Y - normal_zombie->pos.Y;
		if (sqrt(diff_x * diff_x + diff_y * diff_y) > GBOARD_WIDTH) {
			int random = rand() % 4;
			if (random == 0) {
				if (!NormalZombieDetectCollision(normal_zombie->pos.X - 2, normal_zombie->pos.Y, 1))
					normal_zombie->pos.X -= 2;
			}
			else if (random == 1) {
				if (!NormalZombieDetectCollision(normal_zombie->pos.X + 2, normal_zombie->pos.Y, 1))
					normal_zombie->pos.X += 2;
			}
			else if (random == 2) {
				if (!NormalZombieDetectCollision(normal_zombie->pos.X, normal_zombie->pos.Y - 1, 1))
					normal_zombie->pos.Y--;
			}
			else if (random == 3) {
				if (!NormalZombieDetectCollision(normal_zombie->pos.X, normal_zombie->pos.Y + 1, 1))
					normal_zombie->pos.Y++;
			}
		}
		else {
			if (main_character_position.X - normal_zombie->pos.X == 0) {
				dir = 1;
			}
			else if (main_character_position.Y - normal_zombie->pos.Y == 0) {
				dir = 0;
			}

			if (dir == 0)
			{
				if (main_character_position.X - normal_zombie->pos.X < 0)
				{
					if (!NormalZombieDetectCollision(normal_zombie->pos.X - 2, normal_zombie->pos.Y, 1))
						normal_zombie->pos.X -= 2;
				}
				else
				{
					if (!NormalZombieDetectCollision(normal_zombie->pos.X + 2, normal_zombie->pos.Y, 1))
						normal_zombie->pos.X += 2;
				}
			}
			else if (dir == 1)
			{
				if (main_character_position.Y - normal_zombie->pos.Y < 0)
				{
					if (!NormalZombieDetectCollision(normal_zombie->pos.X, normal_zombie->pos.Y - 1, 1))
						normal_zombie->pos.Y--;
				}
				else
				{
					if (!NormalZombieDetectCollision(normal_zombie->pos.X, normal_zombie->pos.Y + 1, 1))
						normal_zombie->pos.Y++;
				}
			}
		}
		ShowOneNormalZombie(normal_zombie);
		normal_zombie = normal_zombie->next;
	}
}

void MakeNormalZombie() {
	int cnt = 0;

	normal_zombie_end = clock();
	COORD pos = MakeNormalZombiePos();
	if (pos.X == -1)
		return;
	double time = (double)(normal_zombie_end - normal_zombie_start) / CLOCKS_PER_SEC;
	if (time > 0.5)
		normal_zombie_start = clock();
	else
		return;
	if (stage_info[stage - 1].made_number_of_normal_zombie >= stage_info[stage - 1].number_of_normal_zombie)
		return;
	stage_info[stage - 1].made_number_of_normal_zombie++;
	Normal_Zombie_Info* normal_zombie = (Normal_Zombie_Info*)malloc(sizeof(Normal_Zombie_Info));
	//normal_zombie->pos.X = GBOARD_ORIGIN_X + GBOARD_WIDTH / 2 + 1;                                //좀비 리스폰 위치 추후 변경가능
	//normal_zombie->pos.Y = GBOARD_ORIGIN_Y + 5;
	normal_zombie->pos = pos;
	normal_zombie->hp = 70;
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

Normal_Zombie_Info* RemoveNormalZombie(Normal_Zombie_Info* dead_normal_zombie) {
	Normal_Zombie_Info* normal_zombie = normal_zombie_list_head;
	Normal_Zombie_Info* prev = NULL;

	stage_info[stage - 1].killed_normal_zombie++;
	while (normal_zombie != dead_normal_zombie) {
		prev = normal_zombie;
		normal_zombie = normal_zombie->next;
	}
	if (prev == NULL) {
		normal_zombie_list_head = dead_normal_zombie->next;
		free(dead_normal_zombie);
		return normal_zombie_list_head;
	}
	prev->next = dead_normal_zombie->next;
	free(dead_normal_zombie);
	return prev->next;
}

int NormalZombieDetectCollision(int position_x, int position_y, int flag) // 여기서 flag는 좀비 이동시 충돌검사할때 == 1, 좀비좌표 구하는 함수에서 사용할때 == 2
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
				if (flag==1)
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
				if (flag == 1) {
					EnergyWave_Info* remove_energy_wave = FindEnergyWave(position_x + x * 2, position_y + y);
					if (remove_energy_wave != NULL)
						RemoveEnergyWave(remove_energy_wave);
				}
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
void findNormalZombie(int x, int y)
{
	Normal_Zombie_Info* normal_zombie = normal_zombie_list_head;

	while (normal_zombie)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (normal_zombie->pos.X + i * 2 == x && normal_zombie->pos.Y + j == y
					|| normal_zombie->pos.X + i * 2 + 1 == x && normal_zombie->pos.Y + j == y) {
					DecreaseNormalZombieHp(normal_zombie);
					return;
				}
			}
		}
		normal_zombie = normal_zombie->next;
	}
	return NULL;
}

Normal_Zombie_Info* DecreaseNormalZombieHp(Normal_Zombie_Info* normal_zombie)
{	
	int damage;
	switch (weapon) {
	case 1:
		damage = 20;
		break;
	case 2:
		damage = 10;
		break;
	case 3:
		damage = 150;
		break;
	case 4:
		damage = 100;
		break;
	case 5:
		damage = 200;
		break;
	}

	normal_zombie->hp -= damage;
	if (normal_zombie->hp < 0)
	{	
		score += 50;
		if (score_flag == 0) {
			score += 50;
		}
		ScoreSetting();
		DeleteOneNormalZombie(normal_zombie);
		return RemoveNormalZombie(normal_zombie);
	}
}

COORD MakeNormalZombiePos()
{
	COORD pos;
	pos.X = -1;
	pos.Y = -1;
	int cnt = 0;
	while (1) {
		int random = rand() % 4;
		cnt++;
		if (cnt > 10) {
			pos.X = -1;
			pos.Y = -1;
			break;
		}
		if (random == 0) {                //동
			pos.X = ((GBOARD_WIDTH - 3) * 2 + GBOARD_ORIGIN_X) / 2 * 2 - 1;
			pos.Y = rand() % (GBOARD_HEIGHT - 3 - GBOARD_HEIGHT / 2) + GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 4;
		}
		else if (random == 1) {        //서
			if (stage < 2)
				continue;
			pos.X = (GBOARD_ORIGIN_X)+4 + 1;
			pos.Y = rand() % (GBOARD_HEIGHT - 3 - GBOARD_HEIGHT / 2) + GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 4;
		}
		else if (random == 2) {         //남
			if (stage < 3)
				continue;
			pos.X = (rand() % (GBOARD_WIDTH - 3 - GBOARD_WIDTH / 6) * 2 + (GBOARD_ORIGIN_X + GBOARD_WIDTH / 6) * 2) / 2 * 2 + 1;
			pos.Y = GBOARD_HEIGHT - 3 + GBOARD_ORIGIN_Y - 1;
		}
		else if (random == 3) {         //북
			if (stage < 4)
				continue;
			pos.X = (rand() % (GBOARD_WIDTH - 3 - GBOARD_WIDTH / 6) * 2 + (GBOARD_ORIGIN_X + GBOARD_WIDTH / 6)) / 2 * 2 + 1;
			pos.Y = GBOARD_ORIGIN_Y + 1;
		}
		if (pos.X == -1)
			continue;
		if (!NormalZombieDetectCollision(pos.X, pos.Y, 2)) {
			break;
		}
	}
	return pos;
}