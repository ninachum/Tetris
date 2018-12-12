#pragma once

#include "tetris_board.h"
#include "tetris_blockhandler.h"
#include <array>
#include <iostream>
#include <Windows.h>

class Drawer
{
private:
	const Coord boardDrawCoord;

	void moveToCoord(int x, int y) const
	{
		COORD cursor;
		cursor.X = x;
		cursor.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
	}

	void drawNextFrame() const
	{
		moveToCoord(22, 2);
		std::cout << " N  E  X  T";
		moveToCoord(22, 3);
		for (int i = 0; i < 6; ++i)
			std::cout << "▩";
		for (int i = 4; i < 6; ++i)
		{
			moveToCoord(22, i);
			std::cout << "▩";
			moveToCoord(32, i);
			std::cout << "▩";
		}
		moveToCoord(22, 6);
		for (int i = 0; i < 6; ++i)
			std::cout << "▩";
	}

	void drawBoardFrame() const
	{
		moveToCoord(36, 3);
		for (int i = 0; i < 12; ++i)
			std::cout << "▩";
		for (int i = 4; i < 29; ++i)
		{
			moveToCoord(36, i);
			std::cout << "▩";
			moveToCoord(58, i);
			std::cout << "▩";
		}
		moveToCoord(36, 29);
		for (int i = 0; i < 12; ++i)
			std::cout << "▩";
	}

	void drawInstruction() const
	{
		moveToCoord(64, 23);
		std::cout << "  HOW TO PLAY";
		moveToCoord(64, 24);
		std::cout << "  ▲ to rotate";
		moveToCoord(64, 25);
		std::cout << "◀▼▶ to move";
		moveToCoord(64, 26);
		std::cout << " SPACE to drop";
	}

public:

	Drawer() : boardDrawCoord(38, 4) {}

	void drawgGameFrame() const
	{
		drawNextFrame();
		drawBoardFrame();
		drawInstruction();
	}

	void drawBoard(const Board & bd) const
	{
		const Board::boardType & status = bd.boardStatus();
		int height = bd.getHeight();
		int width = bd.getWidth();
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (status[i][j].occupied == true)	// false 시 else문을 통해 std::cout << "  "; 을 사용하면 간혹 게임이 매우 느려짐.
				{
					moveToCoord(boardDrawCoord.x + j * 2, boardDrawCoord.y + i);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(status[i][j].color));
					std::cout << "■";
				}
			}
		}
	}

	void eraseBoard(const Board & bd) const
	{
		const Board::boardType & status = bd.boardStatus();
		int height = bd.getHeight();
		int width = bd.getWidth();
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (status[i][j].occupied == true)	// false 시 else문을 통해 std::cout << "  "; 을 사용하면 간혹 게임이 매우 느려짐.
				{
					moveToCoord(boardDrawCoord.x + j * 2, boardDrawCoord.y + i);
					std::cout << "  ";
				}
			}
		}
	}

	void drawHandler(const BlockHandler & handle) const
	{
		Block::Color currentBlockColor = handle.blk->getColor();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(currentBlockColor));
		for (auto & x : handle.blk->getBlockInfo())
		{
			Coord temp = handle.currPos + x;
			moveToCoord(boardDrawCoord.x + temp.x * 2, boardDrawCoord.y + temp.y);
			std::cout << "■";
		}
	}

	void eraseHandler(const BlockHandler & handle) const
	{
		for (auto & x : handle.blk->getBlockInfo())
		{
			Coord temp = handle.currPos + x;
			moveToCoord(boardDrawCoord.x + temp.x * 2, boardDrawCoord.y + temp.y);
			std::cout << "  ";
		}
	}

	void drawGameover(const Board & bd) const
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x7);
		// temporary
		system("cls");
		moveToCoord(0, 0);
		std::cout << "Game Over!" << '\n';
	}

	Coord nextEntryPoint() const
	{
		return Coord(24, 4);
	}
};