
/**
 * A CUI-Based Tetris Game.
 */


#include <iostream>
#include <cctype>
#include <windows.h>
#include "tetris_game.h"
#include <conio.h>

bool wantToPlay();
int setDifficulty();

/**
  @brief 사용자에게 게임 실행 여부를 묻고, 실행할 경우 난이도를 설정한다. 아니라면 프로그램을 종료한다.
  @param 없음.
  @return 프로그램 실행 결과 코드 (보통 0)
 */
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

/**
  @brief 키보드에서 Y 또는 N을 입력받아 게임 실행 여부를 결정
  @param 없음
  @return 프로그램 실행 결과
 */
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

/**
  @brief 게임을 실행하기로 한 경우, 1에서 5 사이의 숫자 버튼을 키보드에서 입력받아 난이도를 결정
  @param 없음
  @return 1부터 5까지의 정수
 */
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