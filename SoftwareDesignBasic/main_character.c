#include "zombie_world.h"

COORD main_character_position = { INITIAL_MAIN_CHARACTER_POS_X ,INITIAL_MAIN_CHARACTER_POS_Y };
int main_character_id = 0;
int invincibility_flag = 0;
int GunDirection = UP;



char main_character[][2][2] =                     // 메인 캐릭터 표시
{
    {
        {2, 7},
        {2, 2}
    },
    {
        {7, 2},
        {2, 2}
    },
    {
        {2, 2},
        {7, 2}
    },
    {
        {2, 2},
        {2, 7}
    }
};

void DeleteBlock(char main_character[2][2])               // 출력된 블록을 삭제하는 함수
{
    int y, x;
    COORD current_position = main_character_position;
    int board_array_x = (current_position.X - GBOARD_ORIGIN_X) / 2;
    int board_array_y = current_position.Y - GBOARD_ORIGIN_Y;

    for (y = 0; y < 2; y++)
    {
        for (x = 0; x < 2; x++)
        {
            SetCurrentCursorPos(current_position.X + (x * 2), current_position.Y + y);
            if (main_character[y][x] == 2 || main_character[y][x] == 7)              // 메인 캐릭터에 적용
            {
                printf("  ");
                game_board[board_array_y + y][board_array_x + x] = 0;
            }
        }
    }
    SetCurrentCursorPos(current_position.X, current_position.Y);
}

void ShowBlock(char main_character[2][2])                // 블록을 출력하는 함수
{
    int y, x;
    COORD current_position = main_character_position;
    int board_array_x = (current_position.X - GBOARD_ORIGIN_X) / 2;
    int board_array_y = current_position.Y - GBOARD_ORIGIN_Y;

    for (y = 0; y < 2; y++)
    {
        for (x = 0; x < 2; x++)
        {
            SetCurrentCursorPos(current_position.X + (x * 2), current_position.Y + y);
            if (main_character[y][x] == 2)                          // 메인 캐릭터에 적용    
            {
                printf("■");
                game_board[board_array_y + y][board_array_x + x] = PLAYER;
            }
            if (main_character[y][x] == 7)                          // 메인 캐릭터에 적용    
            {
                if (main_character_id == 0)
                    printf("▲");
                if (main_character_id == 1)
                    printf("◀");
                if (main_character_id == 2)
                    printf("▼");
                if (main_character_id == 3)
                    printf("▶");
                game_board[board_array_y + y][board_array_x + x] = PLAYER;
            }
        }
    }
    SetCurrentCursorPos(current_position.X, current_position.Y);
}

void ShiftUp()                                  // 상하좌우 움직임
{
    if (!MainCharacterDetectCollision(main_character_position.X, main_character_position.Y - 1, main_character[main_character_id]))
        return;
    DeleteBlock(main_character[main_character_id]);
    SetCurrentCursorPos(main_character_position.X, main_character_position.Y -= 1);
    main_character_id = 0;
    ShowBlock(main_character[main_character_id]);
}

void ShiftDown()
{
    if (!MainCharacterDetectCollision(main_character_position.X, main_character_position.Y + 1, main_character[main_character_id]))
        return;
    DeleteBlock(main_character[main_character_id]);
    SetCurrentCursorPos(main_character_position.X, main_character_position.Y += 1);
    main_character_id = 2;
    ShowBlock(main_character[main_character_id]);
}

void ShiftRight()
{
    if (!MainCharacterDetectCollision(main_character_position.X + 2, main_character_position.Y, main_character[main_character_id]))
        return;
    DeleteBlock(main_character[main_character_id]);
    SetCurrentCursorPos(main_character_position.X += 2, main_character_position.Y);
    main_character_id = 3;
    ShowBlock(main_character[main_character_id]);
}

void ShiftLeft()
{
    if (!MainCharacterDetectCollision(main_character_position.X - 2, main_character_position.Y, main_character[main_character_id]))
        return;
    DeleteBlock(main_character[main_character_id]);
    SetCurrentCursorPos(main_character_position.X -= 2, main_character_position.Y);
    main_character_id = 1;
    ShowBlock(main_character[main_character_id]);
}

void ShowShooting(int x, int y) {
    SetCurrentCursorPos(x, y);
    int board_array_x = (x - GBOARD_ORIGIN_X) / 2;
    int board_array_y = y - GBOARD_ORIGIN_Y;


    if (GunDirection == RIGHT || GunDirection == LEFT)
        printf("─");
    else
        printf("│");

    game_board[board_array_y][board_array_x] = GUN;


    SetCurrentCursorPos(x, y);
}

void DeleteShooting(int x, int y) {
    SetCurrentCursorPos(x, y);
    int board_array_x = (x - GBOARD_ORIGIN_X) / 2;
    int board_array_y = y - GBOARD_ORIGIN_Y;




    if (game_board[board_array_y][board_array_x] == GUN) {
        printf("  ");
        game_board[board_array_y][board_array_x] = 0;
    }


    SetCurrentCursorPos(x, y);

}

void ShootGun() {
    int x = main_character_position.X;
    int y = main_character_position.Y;
    switch (GunDirection) {
    case LEFT:
        while (1) {
            if (!GunDetectCollision(x - 2, y))
                break;
            x = x - 2;
            ShowShooting(x, y);
        }
        Sleep(50);
        x = main_character_position.X;
        y = main_character_position.Y;
        while (1) {
            if (!GunDetectCollision(x - 2, y))
                break;
            x = x - 2;
            SetCurrentCursorPos(x, y);
            DeleteShooting(x, y);
        }
        break;
    case UP:
        x = x + 2;
        while (1) {
            if (!GunDetectCollision(x, y - 1))
                break;
            y = y - 1;
            ShowShooting(x, y);
        }
        Sleep(50);
        x = main_character_position.X;
        y = main_character_position.Y;
        x = x + 2;
        while (1) {
            if (!GunDetectCollision(x, y - 1))
                break;
            y = y - 1;
            SetCurrentCursorPos(x, y);
            DeleteShooting(x, y);
        }
        break;
    case RIGHT:
        x = x + 2;
        y = y + 1;
        while (1) {
            if (!GunDetectCollision(x + 2, y))
                break;
            x = x + 2;
            ShowShooting(x, y);
        }
        Sleep(50);
        x = main_character_position.X;
        y = main_character_position.Y;
        x = x + 2;
        y = y + 1;
        while (1) {
            if (!GunDetectCollision(x + 2, y))
                break;
            x = x + 2;
            SetCurrentCursorPos(x, y);
            DeleteShooting(x, y);
        }
        break;
    case DOWN:
        y = y + 1;
        while (1) {
            if (!GunDetectCollision(x, y + 1))
                break;
            y = y + 1;
            ShowShooting(x, y);
        }
        Sleep(50);
        x = main_character_position.X;
        y = main_character_position.Y;
        y = y + 1;
        while (1) {
            if (!GunDetectCollision(x, y + 1))
                break;
            y = y + 1;
            SetCurrentCursorPos(x, y);
            DeleteShooting(x, y);
        }
        break;
    }

}

void ProcessKeyInput(int time)              // 방향키를 입력받아 움직이는 함수 적용 (time 기본값 30)
{
    int key_input;
    for (int i = 0; i < 20; i++)
    {
        if (_kbhit() != 0)
        {
            key_input = _getch();
            switch (key_input)
            {
            case LEFT:
                ShiftLeft();
                GunDirection = LEFT;
                break;
            case RIGHT:
                ShiftRight();
                GunDirection = RIGHT;
                break;
            case UP:
                ShiftUp();
                GunDirection = UP;
                break;
            case DOWN:
                ShiftDown();
                GunDirection = DOWN;
                break;

            case SPACE:
                end = clock();
                double time = (double)(end - start) / CLOCKS_PER_SEC;
                if (time > 1) {
                    start = clock();
                    ShootGun();
                }
                break;
            }
        }
        Sleep(time);
    }
}

void LifeDecrease()
{
    invincibility_flag = 1;
    life--;
    LifeSetting();
    for (int i = 0; i < 2; i++)
    {
        DeleteBlock(main_character[main_character_id]);
        ProcessKeyInput(1);
        ShowBlock(main_character[main_character_id]);
        ProcessKeyInput(1);
    }
    invincibility_flag = 0;
}

int MainCharacterDetectCollision(int position_x, int position_y, char main_character[2][2])
{
    int board_array_x = (position_x - GBOARD_ORIGIN_X) / 2;
    int board_array_y = position_y - GBOARD_ORIGIN_Y;
    for (int x = 0; x < 2; x++)
    {
        for (int y = 0; y < 2; y++)
        {
            if ((main_character[y][x] == PLAYER && game_board[board_array_y + y][board_array_x + x] == MAP_BOUNDARY) || (main_character[y][x] == PLAYER_RIGHT && game_board[board_array_y + y][board_array_x + x] == MAP_BOUNDARY))     // 메인 캐릭터와 맵이 충돌할 때
            {
                return 0;
            }
            if ((main_character[y][x] == PLAYER && game_board[board_array_y + y][board_array_x + x] == ZOMBIE) || (main_character[y][x] == PLAYER_RIGHT && game_board[board_array_y + y][board_array_x + x] == ZOMBIE))     // 메인 캐릭터와 좀비가 부딪혔을 때
            {
                if (invincibility_flag == 0)
                    LifeDecrease(PLAYER);
                return 0;
            }
            if ((main_character[y][x] == PLAYER && game_board[board_array_y + y][board_array_x + x] == ENERGY_WAVE) || (main_character[y][x] == PLAYER_RIGHT && game_board[board_array_y + y][board_array_x + x] == ENERGY_WAVE))  //메인 캐릭터와 좀비에너지파가 부딪혔을때
            {
                EnergyWave_Info* remove_energy_wave = FindEnergyWave(position_x + x * 2, position_y + y);
                if (remove_energy_wave != NULL)
                    RemoveEnergyWave(remove_energy_wave);
                LifeDecrease(PLAYER);
                return 0;
            }
            if ((main_character[y][x] == PLAYER && game_board[board_array_y + y][board_array_x + x] == ITEM) || (main_character[y][x] == PLAYER_RIGHT && game_board[board_array_y + y][board_array_x + x] == ITEM))         //메인 캐릭터와 아이템 충돌
            {
                ItemEffect();
            }// 아이템과 부딪히면 아이템 효과 발동
        }
    }
    return 1;
}

int GunDetectCollision(int position_x, int position_y) {

    int board_array_x = ((position_x - GBOARD_ORIGIN_X) / 2);
    int board_array_y = (position_y - GBOARD_ORIGIN_Y);

    if (game_board[board_array_y][board_array_x] == MAP_BOUNDARY)     // 메인 캐릭터와 맵이 충돌할 때
        return 0;
    if (game_board[board_array_y][board_array_x] == ZOMBIE)     // 메인 캐릭터와 좀비가 부딪혔을 때
        return 0;
    if (game_board[board_array_y][board_array_x] == ENERGY_WAVE) // 메인 캐릭터가 에너지파에 맞았을 때
        return 0;
    if (game_board[board_array_y][board_array_x] == ITEM)      // 메인 캐릭터가 아이템에 부딪쳤을 때
        return 0;

    return 1;
}