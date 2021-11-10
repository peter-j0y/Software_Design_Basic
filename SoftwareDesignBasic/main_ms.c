//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <windows.h>
//
//#pragma warining(disable:4996)
//
// //게임보드의 크기에 맞게 설정된 배열
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
