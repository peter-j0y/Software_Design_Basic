#include "zombie_world.h"

// 게임 실행
void PlayGame() 
{
    system("mode con cols=130 lines=40"); //콘솔창 크기 조절
    life = 3;
    score = 0;
    stage = 5;

    shoot_start = clock();
    gun_start = clock();
    item_start = clock();
    zombie_speed_decrease_start = clock();
    double_score_start = clock();
    item_flag = 1;
    zombie_speed_flag = 1;
    score_flag = 1;
    stage_start_flag = 1;

    srand(time(0));

    DrawGameBoard();
    SettingMap();

    SetCurrentCursorPos(main_character_position.X, main_character_position.Y);

    ShowBlock(main_character[main_character_id]);
    while (1)
    {
        if (life <= 0)
        {
            system("cls");
            return;
        }
        SetStage();
        ZombieSpeedTimer(); // ProcessKeyInput 가지고 있음
        ScoreTimer();
        ItemTimer();

        MakeBossZombie();
        MoveBossZombie();
        ShowEnergyWave();
        MakeNormalZombie();
        MoveNormalZombie();
        MoveEnergyWave();
        MoveBazukaBullet();
        MoveBazukaBullet();
        MoveBazukaBullet();
        //DeleteEnergyWave();
    }
}

void Menual()
{
    system("cls");
    SetCurrentCursorPos(44, 2);
    printf("*********게임소개********");
    SetCurrentCursorPos(5, 4);
    printf("나는 바이러스 연구소장 이민석...");
    SetCurrentCursorPos(72, 5);
    printf("※※※");
    SetCurrentCursorPos(60, 6);
    printf("보스좀비 :");
    SetCurrentCursorPos(72, 6);
    printf("※◈※");
    SetCurrentCursorPos(80, 6);
    printf("일반좀비 :");
    SetCurrentCursorPos(92, 6);
    printf("◆◆");
    SetCurrentCursorPos(98, 6);
    printf("아이템 :");
    SetCurrentCursorPos(108, 6);
    printf("♣");

    SetCurrentCursorPos(92, 7);
    printf("◆◆");
    SetCurrentCursorPos(72, 7);
    printf("※※※");
    SetCurrentCursorPos(5, 6);
    printf("누군가에 의해 좀비 바이러스가 유출됐다...!");
    SetCurrentCursorPos(5, 8);
    printf("어서 이곳을 탈출하고 세상을 구해야해!!!");
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

void ChooseMenu()
{
    RemoveCursor();
    TitleDraw();
    int choose_menu_flag = 1;
    while (1)
    {
        if (choose_menu_flag == 1)
        {
            SetCurrentCursorPos(48, 18);
            printf("▶");
        }
        SetCurrentCursorPos(52, 18);
        printf("게임 시작");
        SetCurrentCursorPos(52, 21);
        printf("게임 설명");
        SetCurrentCursorPos(52, 24);
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
                        SetCurrentCursorPos(48, 18);
                        printf("  ");
                        SetCurrentCursorPos(48, 21);
                        printf("▶");
                        choose_menu_flag++;
                    }
                    else if (choose_menu_flag == 2)
                    {
                        SetCurrentCursorPos(48, 21);
                        printf("  ");
                        SetCurrentCursorPos(48, 24);
                        printf("▶");
                        choose_menu_flag++;
                    }
                    break;
                case UP:
                    if (choose_menu_flag == 3)
                    {
                        SetCurrentCursorPos(48, 24);
                        printf("  ");
                        SetCurrentCursorPos(48, 21);
                        printf("▶");
                        choose_menu_flag--;
                    }
                    else if (choose_menu_flag == 2)
                    {
                        SetCurrentCursorPos(48, 21);
                        printf("  ");
                        SetCurrentCursorPos(48, 18);
                        printf("▶");
                        choose_menu_flag--;
                    }
                    break;
                }
            }
        }
        if (life <= 0)
            break;
    }
    system("cls");
    EndGame();
}

void EndGame()
{
    int end_game_menu_flag = 1;
    while (1)
    {
        SetCurrentCursorPos(50, 10);
        printf("결국 세상을 지켜내지 못했군...");
        if (end_game_menu_flag == 1)
        {
            SetCurrentCursorPos(54, 15);
            printf("▶");
        }
        SetCurrentCursorPos(61, 15);
        printf("다시 시작");
        SetCurrentCursorPos(62, 17);
        printf("끝내기");
        for (int i = 0; i < 20; i++)
        {
            int key_input;
            if (_kbhit() != 0)
            {
                key_input = _getch();
                switch (key_input)
                {
                case ENTER:
                    if (end_game_menu_flag == 1)
                    {
                        // 다시 시작
                        system("cls");
                        resetGame();
                        PlayGame();
                    }
                    if (end_game_menu_flag == 2)
                    {
                        // 게임 종료
                        exit(0);
                    }
                    break;
                case DOWN:
                    if (end_game_menu_flag == 1)
                    {
                        SetCurrentCursorPos(54, 15);
                        printf("  ");
                        SetCurrentCursorPos(54, 17);
                        printf("▶");
                        end_game_menu_flag++;
                    }
                    break;
                case UP:
                    if (end_game_menu_flag == 2)
                    {
                        SetCurrentCursorPos(54, 17);
                        printf("  ");
                        SetCurrentCursorPos(54, 15);
                        printf("▶");
                        end_game_menu_flag--;
                    }
                    break;
                }
            }
        }
    }
}

void TitleDraw() {
    int x=30, y=4;

    SetCurrentCursorPos(x, y++);
    printf("#####    ####   ##       ##  ######   #####    ##### ");
    SetCurrentCursorPos(x, y++);
    printf("   #    #    #  # #     # #  #   ##     #      #     ");
    SetCurrentCursorPos(x, y++);
    printf("  #     #    #  #  #   #  #  ####       #      ####  ");
    SetCurrentCursorPos(x, y++);
    printf(" #      #    #  #   # #   #  #   ##     #      #     ");
    SetCurrentCursorPos(x, y++);
    printf("#####    ####   #    #    #  ######   #####    ##### ");
    y++;
    SetCurrentCursorPos(x, y++);
    printf("  #    #    #    ####    ######   #        #####     ");
    SetCurrentCursorPos(x, y++);
    printf("  #   # #   #   #    #   #    #   #        #    #    ");
    SetCurrentCursorPos(x, y++);
    printf("  #  #   #  #   #    #   #####    #        #     #   ");
    SetCurrentCursorPos(x, y++);
    printf("  # #     # #   #    #   #   #    #        #    #    ");
    SetCurrentCursorPos(x, y++);
    printf("  ##       ##    ####    #    #   ######   #####     ");
}
