#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include "Game.h"

using namespace std;


void main(int argc, char** argv)
{
	srand(time(NULL));
	int gameMode = NORMAL_MODE;
	
	try
	{
		gameMode = get_Game_Mode(argv, argc);
	}
	catch (const char* error)
	{
		cout << error;
		system("pause");
		exit(1);
	}
	
	Game newGame(gameMode);
	newGame.menu();
}
