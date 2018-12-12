#pragma once

#include "tetris_board.h"
#include "tetris_blockhandler.h"
#include <array>
#include <iostream>
#include <Windows.h>
#include "tetris_blockhandler.h"

class DebugDrawer
{

private:
	void moveToCoord(int x, int y) const
	{
		COORD cursor;
		cursor.X = x;
		cursor.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
	}

public:

	void debugDrawBoard(const Board & bd) const
	{
		system("cls");
		const Board::boardType & status = bd.boardStatus();
		int height = bd.getHeight();
		int width = bd.getWidth();
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (status[i][j] == true)	// false 시 else문을 통해 std::cout << "  "; 을 사용하면 간혹 게임이 매우 느려짐.
				{
					moveToCoord(j * 2, i);
					std::cout << "■";
				}
			}
		}

	}

	void debugDrawHandler(const BlockHandler & handle) const
	{

		for (auto & x : handle.blk->getBlockInfo())
		{
			Coord temp = handle.currPos + x;
			moveToCoord(temp.x * 2, temp.y);
			std::cout << "■";
		}
	}

	void debugDrawEraseHandler(const BlockHandler & handle) const
	{

		for (auto & x : handle.blk->getBlockInfo())
		{
			Coord temp = handle.currPos + x;
			moveToCoord(temp.x * 2, temp.y);
			std::cout << "  ";
		}
	}

	void debugDrawGameover(const Board & bd, const BlockHandler & handle) const
	{
		system("cls");
		moveToCoord(0, 0);
		std::cout << "Game Over!" << '\n';
	}
};