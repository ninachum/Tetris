#include <iostream>
#include <cctype>
#include "tetris_game.h"


bool wantToPlay();

int main()
{

	std::cout << "WELCOME TO TETRIS!\n";
	std::cout << "want to play ? (y/n) ";
	
	if (wantToPlay())
	{
		system("cls");
		Game x;
		x.play();
	}
	system("pause");

	return 0;

}

bool wantToPlay()
{
	char selection;
	while (std::cin.get(selection))
	{
		switch (std::tolower(selection))
		{
		case 'y':
			return true;
		case 'n':
			return false;
		default:
			std::cout << "please enter y or n only.\n";
			std::cout << "want to play ? (y/n) ";
			while (std::cin.get() != '\n')
				continue;
		}
	}
	return false;
}
