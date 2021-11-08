//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <windows.h>
//
//#pragma warining(disable:4996)
//
//#define GBOARD_ORIGIN_X 10  //게임보드가 존재하기 전 x축 공백
//#define GBOARD_ORIGIN_Y 3   //게임보드가 존재하기 전 y축 공백
//
//#define GBOARD_WIDTH 53     //게임보드의 크기 (경계선 포함 X)
//#define GBOARD_HEIGHT 32    //게임보드의 크기 (경계선 포함 X)
//
//#define SCORE_X 10          //SCORE, STAGE 등 화면에 보이는 UI의 좌표값들
//#define SCORE_Y 1           //만약 SCORE 점수를 수정한다면    
//#define STAGE_X 56          //SetCurrentPos에 SCORE_X, SCORE_Y를 넣고 점수를 적으면 됨
//#define STAGE_Y 1
//#define LIFE_X 107
//#define LIFE_Y 1
//#define USE_WEAPON_X 19
//#define USE_WEAPON_Y 37
//#define USABLE_WEAPON_X 57
//#define USABLE_WEAPON_Y 37
//
//
//int score = 0, life = 3, stage = 3, weapon = 3;  //점수, 생명력, 스테이지, 무기의 변수
//char* weaponName[5] = { "권총", "기관단총", "샷건", "저격총", "바주카" }; //무기 종류
//int curPosX, curPosY;                   //마우스 커서
//int gameBoard[GBOARD_HEIGHT + 2][GBOARD_WIDTH + 2]; //게임보드의 크기에 맞게 설정된 배열
//                                                    //테두리에 1로 되있음 그러니깐 GBOARD_WIDTH * GBORAD_HEIGHT의
//                                                    //그만큼의 공간은 시작했을때 0임
//
//void RemoveCursor(void); //커서 깜빡이는 거 삭제
//void SetCurrentCursorPos(int pos_x, int pos_y); //커서 위치 설정함수
//void DrawGameBoard();           //처음 시작 시 gameboard 그려주는거
//void SettingMap();              //처음 시작시 기본 UI 그려줌
//void ScoreSetting();            //SCORE가 바뀔때 호출해주는 함수
//void LifeSetting();             //LIFE가 바뀔 떄 호출해주는 함수
//void WeaponSetting();           //무기를 교체할때 호출해주는 함수
//void StageSetting();            //STAGE가 올라갈때 호출해주는 함수
//
//int main() {
//
//    RemoveCursor();
//    srand(time(0));
//    system("mode con cols=130 lines=40"); //콘솔창 크기 조절
//
//    DrawGameBoard();
//    SettingMap();
//
//
//    while (1) {
//
//    }
//
//    return 0;
//}
//
//void SetCurrentCursorPos(int pos_x, int pos_y) {
//    COORD p1 = { pos_x, pos_y };
//
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p1);
//}
//
//void RemoveCursor(void)
//{
//    CONSOLE_CURSOR_INFO curInfo;
//    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
//    curInfo.bVisible = 0;
//    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
//}
//
//void DrawGameBoard() {
//    int x, y;
//    for (y = 0; y <= GBOARD_HEIGHT; y++) {
//        SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
//        if (y == 0)
//            printf("┌");
//        else if (y == GBOARD_HEIGHT)
//            printf("└");
//        else
//            printf("│");
//    }
//
//    for (y = 0; y <= GBOARD_HEIGHT; y++) {
//        SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);
//        if (y == 0)
//            printf("┐");
//        else if (y == GBOARD_HEIGHT)
//            printf("┘");
//        else
//            printf("│");
//    }
//
//    for (x = 1; x <= GBOARD_WIDTH; x++) {
//        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y);
//        printf("─");
//        SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
//        printf("─");
//    }
//
//    for (int i = 0; i <= GBOARD_HEIGHT; i++) {
//        gameBoard[i][0] = 1;
//        gameBoard[i][GBOARD_WIDTH + 2];
//    }
//
//    for (int i = 0; i < GBOARD_WIDTH + 2; i++) {
//        gameBoard[0][i] = 1;
//        gameBoard[GBOARD_HEIGHT + 1][i];
//    }
//}
//
//void SettingMap() {
//    SetCurrentCursorPos(SCORE_X - 8, SCORE_Y);
//    puts("SCORE : ");
//    SetCurrentCursorPos(STAGE_X - 8, STAGE_Y);
//    puts("STAGE : ");
//    SetCurrentCursorPos(LIFE_X - 7, LIFE_Y);
//    puts("LIFE : ");
//    SetCurrentCursorPos(USE_WEAPON_X - 17, USE_WEAPON_Y);
//    puts("사용 중인 무기 : ");
//    SetCurrentCursorPos(USABLE_WEAPON_X - 17, USABLE_WEAPON_Y);
//    puts("교체 가능 무기 : ");
//
//    ScoreSetting();
//    LifeSetting();
//    WeaponSetting();
//    StageSetting();
//}
//
//void ScoreSetting() {
//    SetCurrentCursorPos(SCORE_X, SCORE_Y);
//    printf("%d", score);
//}
//
//void LifeSetting() {
//    SetCurrentCursorPos(LIFE_X, LIFE_Y);
//    for (int i = 0; i < life; i++) {
//        printf("♥ ");
//    }
//}
//void WeaponSetting() {
//    SetCurrentCursorPos(USE_WEAPON_X, USE_WEAPON_Y);
//    for (int i = 1; i <= 5; i++) {
//        if (i == weapon)
//            printf("%s", weaponName[i - 1]);
//    }
//    SetCurrentCursorPos(USABLE_WEAPON_X, USABLE_WEAPON_Y);
//    for (int i = 1; i <= 5; i++) {
//        if (i != weapon && i <= stage) {
//            printf("%s  ", weaponName[i - 1]);
//        }
//    }
//}
//void StageSetting() {
//    SetCurrentCursorPos(STAGE_X, STAGE_Y);
//    for (int i = 0; i < stage; i++) {
//        printf("★ ");
//    }
//}