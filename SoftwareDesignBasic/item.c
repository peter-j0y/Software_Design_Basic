#include "zombie_world.h"

void RandomItem() {                                         // 아이템의 생성 위치와 종류 결정
	int temp_item_location;
	temp_item_location = rand() % 4;
	while (temp_item_location == item_location)
	{
		temp_item_location = rand() % 4;
	}
	item_location = temp_item_location;
	item_type = rand() % 3;

	if (item_location == 0) {
		item_pos.X = GBOARD_ORIGIN_X + 53;
		item_pos.Y = GBOARD_ORIGIN_Y + 5;
	}

	else if (item_location == 1) {
		item_pos.X = GBOARD_ORIGIN_X + 11;
		item_pos.Y = GBOARD_ORIGIN_Y + 16;
	}

	else if (item_location == 2) {
		item_pos.X = GBOARD_ORIGIN_X + 89;
		item_pos.Y = GBOARD_ORIGIN_Y + 16;
	}

	else if (item_location == 3) {
		item_pos.X = GBOARD_ORIGIN_X + 53;
		item_pos.Y = GBOARD_ORIGIN_Y + 27;
	}

	board_array_x = (item_pos.X - GBOARD_ORIGIN_X) / 2;
	board_array_y = item_pos.Y - GBOARD_ORIGIN_Y;
}

void ShowItem() {       // 아이템 보여주기
	SetCurrentCursorPos(item_pos.X, item_pos.Y);
	if (item_type == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("♥ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	if (item_type == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		printf("▼");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	if (item_type == 2) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("X2");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	game_board[board_array_y][board_array_x] = ITEM;
}

void CreateVaccine()
{
	if (stage == 3 && get_vaccine == 0)
	{
		SetCurrentCursorPos(20, 5);
		printf("VC");
		game_board[5 - GBOARD_ORIGIN_Y][(20 - GBOARD_ORIGIN_X) / 2] = VACCINE;
	}
}

void DeleteVaccine()
{
	SetCurrentCursorPos(20, 5);
	printf("  ");
	game_board[(21 - GBOARD_ORIGIN_X) / 2][5 - GBOARD_ORIGIN_Y] = 0;
	get_vaccine = 1;
	VaccineSetting();
}

void DeleteItem() {     // 아이템 삭제
	SetCurrentCursorPos(item_pos.X, item_pos.Y);
	printf("  ");
	game_board[board_array_y][board_array_x] = 0;
	item_start = clock();
	item_flag = 1;
}

void ItemEffect() {   // 아이템을 먹었을 시 발생하는 효과
	DeleteItem();
	if (item_type == 0) {
		LifeIncreaseItem();
	}
	else if (item_type == 1) {
		ZombieSpeedDecreaseItem();
	}
	else if (item_type == 2) {
		DoubleScoreItem();
	}
}

void LifeIncreaseItem() { // 생명 증가
	life++;
	LifeSetting();
}

void ZombieSpeedDecreaseItem() { // 좀비 속도 느려지기
	zombie_speed_decrease_start = clock();
	zombie_speed_flag = 0;
}

void DoubleScoreItem() { // 점수 2배
	double_score_start = clock();
	score_flag = 0;
}

void ItemTimer() {
	item_end = clock();
	double time = (double)(item_end - item_start) / CLOCKS_PER_SEC;
	if (item_flag == 1 && time > 10) {
		RandomItem();
		ShowItem();
		item_flag = 0;
	}// 아이템 쿨 타임
}

void ZombieSpeedTimer() {
	zombie_speed_decrease_end = clock();
	double time = (double)(zombie_speed_decrease_end - zombie_speed_decrease_start) / CLOCKS_PER_SEC;
	if (zombie_speed_flag == 1) {
		ProcessKeyInput(30);
	}
	else if (zombie_speed_flag == 0) {
		ProcessKeyInput(55);
		if (time > 5) {
			zombie_speed_flag = 1;
		}
	}
}

void ScoreTimer() {
	double_score_end = clock();
	double time = (double)(double_score_end - double_score_start) / CLOCKS_PER_SEC;
	if (score_flag == 0 && time > 10) {
		score_flag = 1;
	}
}