#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

typedef struct Normal_Zombie_Info {
	int x;
	int y;
	int hp;
	struct Normal_Zombie_Info *next;
}Normal_Zombie_Info;

typedef struct {
	Normal_Zombie_Info *header;
}Normal_Zombie_Info_h;

Normal_Zombie_Info_h* createZombieList();

int STAGE;																// 스테이지
													
Normal_Zombie_Info_h* createZombieList();								// 일반 좀비와 보스 좀비의 수가 0이 되면 스테이지 클리어
int MakeNormalZombie();													// 일반 좀비 리스폰 위치에 랜덤으로 생성
void ShowNormalZombie();												// 일반좀비들 화면에 출력
void DeleteNormalZombie();												// 일반좀비들 이동을 위해 화면에서 삭제
void MoveNormalZombie(int player_x, int player_y);                      // 일반좀비 이동
void Remove_Normal_Zombie();											// 일반좀비 개체삭제(체력이 0이 되면 삭제)


void SetCurrentCursorPos(int x, int y);
COORD GetCurrentCursorPos();
void ShowBlock(char blockinfo[4][4]);
void DeleteBlock(char blockinfo[4][4]);
void Move(int dir, int x, int y);

int main() {
	int i;
	int dir;
	int x, y;
	int num;

	srand(time(NULL));

	num = MakeNormalZombie();

	MoveNormalZombie(player_x, player_y,num);
	

	getchar();
	return 0;
}

Normal_Zombie_Info_h* createZombieList() {
	Normal_Zombie_Info_h *L;
	L = (Normal_Zombie_Info_h*)malloc(sizeof(Normal_Zombie_Info_h));
	L->header = (Normal_Zombie_Info*)malloc(sizeof(Normal_Zombie_Info));
	
	L->header->next = NULL;

	return L;
}

int MakeNormalZombie() {
	int x, y;
	int n = STAGE;

	Num = (NormalZombie*)malloc(n*sizeof(NormalZombie));				// 스테이지 값을 이용한 연산으로 스테이지에 따라 일반 좀비의 숫자를 조절
	
	x = rand() % 180;		// 리스폰 위치(나머지 하는 값은 수정)/
	y = rand() % 47;

	return n;
}

void ShowNormalZombie() {
	COORD p = GetCurrentCursorPos();
	int x, y;
	
	printf("◆");
	SetCurrentCursorPos(p.X, p.Y);
}

void DeleteNormalZombie() {
	COORD p = GetCurrentCursorPos();
	int x, y;

	printf("  ");
	SetCurrentCursorPos(p.X, p.Y);
}

void MoveNormalZombie(int num) {
	int dir, i;
	int x, y;
	
	for (i = 0; i < num;i++) {
		dir = rand() % 2;

		if (player_x == Num[i].x) {
			dir == 1;
		}
		else if (player_y == Num[i].y) {
			dir == 0;
		}

		if (dir==0) {
			if (player_x - Num[i].x < 0) {
				Num[i].x--;
				SetCurrentCursorPos(x, y);
				ShowNormalZombie();
				Sleep(100);
				DeleteNormalZombie();
			}
			else if (player_x - Num[i].x > 0) {
				Num[i].x++;
				SetCurrentCursorPos(x, y);
				ShowNormalZombie();
				Sleep(100);
				DeleteNormalZombie();
			}
		}

		else if(dir==1){
			if (player_y - Num[i].y < 0) {
				Num[i].y--;
				SetCurrentCursorPos(x, y);
				ShowNormalZombie();
				Sleep(100);
				DeleteNormalZombie();
			}
			else if (player_y - Num[i].y > 0) {
				Num[i].y++;
				SetCurrentCursorPos(x, y);
				ShowNormalZombie();
				Sleep(100);
				DeleteNormalZombie();
			}
		}
	}
}

void Remove_Normal_Zombie(int num) {
	int i;

	for (i = 0; i < num; i++)
	if (Num[i].hp == 0) {

	}
}


COORD GetCurrentCursorPos() {
	CONSOLE_SCREEN_BUFFER_INFO curinfo;
	COORD curpoint;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
	curpoint.X = curinfo.dwCursorPosition.X;
	curpoint.Y = curinfo.dwCursorPosition.Y;

	return curpoint;
}

void SetCurrentCursorPos(int x, int y) {
	COORD p = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}