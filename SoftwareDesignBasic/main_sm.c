#include "zombie_world.h"

void Menual();

int main()
{
    RemoveCursor();

    int choose_menu_flag = 1;
    while (1)
    {
        if (choose_menu_flag == 1)
        {
            SetCurrentCursorPos(48, 10);
            printf("▶");
        }
        SetCurrentCursorPos(52, 10);
        printf("게임 시작");
        SetCurrentCursorPos(52, 13);
        printf("게임 설명");
        SetCurrentCursorPos(52, 16);
        printf("게임 종료");
        for (int i = 0; i < 20; i++)
        {
            int key_input;
            if (_kbhit() != 0)
            {
                key_input = _getch();
                switch (key_input)
                {
                case ENTER:
                    if (choose_menu_flag == 1)
                    {
                        // 게임 실행
                        system("cls");
                        PlayGame();
                    }
                    if (choose_menu_flag == 2)
                    {
                        // 게임 설명 화면
                        system("cls");
                        Menual();
                    }
                    if (choose_menu_flag == 3)
                    {
                        // 게임 종료
                        exit(0);
                    }
                    break;
                case DOWN:
                    if (choose_menu_flag == 1)
                    {
                        SetCurrentCursorPos(48, 10);
                        printf("  ");
                        SetCurrentCursorPos(48, 13);
                        printf("▶");
                        choose_menu_flag++;
                    }
                    else if (choose_menu_flag == 2)
                    {
                        SetCurrentCursorPos(48, 13);
                        printf("  ");
                        SetCurrentCursorPos(48, 16);
                        printf("▶");
                        choose_menu_flag++;
                    }
                    break;
                case UP:
                    if (choose_menu_flag == 3)
                    {
                        SetCurrentCursorPos(48, 16);
                        printf("  ");
                        SetCurrentCursorPos(48, 13);
                        printf("▶");
                        choose_menu_flag--;
                    }
                    else if (choose_menu_flag == 2)
                    {
                        SetCurrentCursorPos(48, 13);
                        printf("  ");
                        SetCurrentCursorPos(48, 10);
                        printf("▶");
                        choose_menu_flag--;
                    }
                    break;
                }
            }
        }
    }
    return 0;
}

void Menual()
{
    system("cls");
    SetCurrentCursorPos(44, 10);
    printf("**********조작법**********");
    SetCurrentCursorPos(32, 12);
    printf("△");
    SetCurrentCursorPos(30, 13);
    printf("◁");
    SetCurrentCursorPos(34, 13);
    printf("▷");
    SetCurrentCursorPos(32, 14);
    printf("▽");
    SetCurrentCursorPos(42, 13);
    printf("방향키를 이용해 주인공을 움직일 수 있어요");
    SetCurrentCursorPos(28, 17);
    printf("SPACE BAR");
    SetCurrentCursorPos(42, 17);
    printf("스페이스 바를 이용해 총을 쏘아 좀비를 처치할 수 있어요");
    SetCurrentCursorPos(28, 21);
    printf("①②③④⑤");
    SetCurrentCursorPos(42, 21);
    printf("숫자 키를 이용해 무기의 종류를 바꿀 수 있어요");

    SetCurrentCursorPos(38, 25);
    printf("아무 키나 눌러 게임을 시작해 보세요!");

    while (1)
    {
        if (_kbhit() != 0)
        {
            system("cls");
            PlayGame();
        }
    }
}