/*
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "cursor_function.h"
#include "main_character.h"
#include "block_function.h"
#include "normal_zombie.h"
#include "remove.h"


int main()
{
	RemoveCursor();
	COORD current_pos = { 65, 20 };
	SetCurrentCursorPos(current_pos.X, current_pos.Y);
	ShowBlock(main_character);
	MakeNormalZombie();
	MakeNormalZombie();
	MakeNormalZombie();
	MakeNormalZombie();
	MakeNormalZombie();
	MakeNormalZombie();

	while (1)
	{
		ShowNormalZombie();
		ProcessKeyInput();
		DeleteNormalZombie();
		MoveNormalZombie();
	}

	return 0;
}
*/