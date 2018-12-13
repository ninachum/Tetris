#include <iostream>
#include <cctype>
#include <windows.h>
#include "tetris_game.h"
#include <conio.h>

bool wantToPlay();
int setDifficulty();

int main()
{
	std::cout << "WELCOME TO TETRIS!\n";
	std::cout << "want to play ? (y/n) ";
	
	while (wantToPlay())
	{
		Game x(setDifficulty());
		x.play();
		system("cls");
		std::cout << "want to play again ? (y/n) ";
	}
	std::cout << '\n';
	system("pause");

	return 0;

}

bool wantToPlay()
{
	while (true)
	{
		if (GetAsyncKeyState('Y') & 0x8000)
		{
			Sleep(500);
			return true;
		}
		else if (GetAsyncKeyState('N') & 0x8000)
		{
			Sleep(500);
			return false;
		}
		else
			continue;
	}
}

int setDifficulty()
{
	std::cout << '\n' << "difficulty ? (1 - 5)";

	while (true)
	{
		if (GetAsyncKeyState('1') & 0x8000)
		{
			Sleep(500);
			return 1;
		}
		else if (GetAsyncKeyState('2') & 0x8000)
		{
			Sleep(500);
			return 2;
		}
		else if (GetAsyncKeyState('3') & 0x8000)
		{
			Sleep(500);
			return 3;
		}
		else if (GetAsyncKeyState('4') & 0x8000)
		{
			Sleep(500);
			return 4;
		}
		else if (GetAsyncKeyState('5') & 0x8000)
		{
			Sleep(500);
			return 5;
		}
	}
}