#include "zombie_world.h";

void RandomItem() {                                         // 아이템의 생성 위치와 종류 결정
	item_location = rand() % 4;
	item_type = rand() % 3;

	if (item_location == 0) {
		item_pos.X = (rand() % GBOARD_WIDTH) + (GBOARD_ORIGIN_X + 1);
		item_pos.Y = (rand() % (GBOARD_HEIGHT / 2)) + (GBOARD_ORIGIN_Y + 1);
	}

	else if (item_location == 1) {
		item_pos.X = (rand() % GBOARD_WIDTH) + (GBOARD_ORIGIN_X + GBOARD_WIDTH);
		item_pos.Y = (rand() % (GBOARD_HEIGHT / 2)) + (GBOARD_ORIGIN_Y + 1);
	}

	else if (item_location == 2) {
		item_pos.X = (rand() % GBOARD_WIDTH) + (GBOARD_ORIGIN_X + 1);
		item_pos.Y = (rand() % (GBOARD_HEIGHT / 2)) + (GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 2);
	}

	else if (item_location == 3) {
		item_pos.X = (rand() % GBOARD_WIDTH) + (GBOARD_ORIGIN_X + GBOARD_WIDTH);
		item_pos.Y = (rand() % (GBOARD_HEIGHT / 2)) + (GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 2);
	}

	board_array_x = (item_pos.X - GBOARD_ORIGIN_X) / 2;
	board_array_y = item_pos.Y - GBOARD_ORIGIN_Y;
}

void ShowItem() {       // 아이템 보여주기
	SetCurrentCursorPos(item_pos.X, item_pos.Y);
	printf("♣");
	game_board[board_array_y][board_array_x] = ITEM;
}

void DeleteItem() {     // 아이템 삭제
	SetCurrentCursorPos(item_pos.X, item_pos.Y);
	printf("  ");
	game_board[board_array_y][board_array_x] = 0;
}

void ItemEffect() {   // 아이템을 먹었을 시 발생하는 효과
	DeleteItem();
	item_start = clock();
	item_flag = 1;
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
	if (item_flag == 1 && time > 1) {
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