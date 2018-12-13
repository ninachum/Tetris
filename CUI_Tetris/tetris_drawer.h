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
		for (int i = 4; i < 7; ++i)
		{
			moveToCoord(22, i);
			std::cout << "▩";
			moveToCoord(32, i);
			std::cout << "▩";
		}
		moveToCoord(22, 7);
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

	void drawTitleScreen() const
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x7);

		moveToCoord(14, 10); // temporary
		std::cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
		moveToCoord(14, 11);
		std::cout << "□■■■■■□■■■■■□■■■■■□■■■■□□■■■■■□□■■■■□\n";
		moveToCoord(14, 12);
		std::cout << "□□□■□□□■□□□□□□□■□□□■□□□■□□□■□□□■□□□□□\n";
		moveToCoord(14, 13);
		std::cout << "□□□■□□□■■■■■□□□■□□□■■■■□□□□■□□□□■■■■□\n";
		moveToCoord(14, 14);
		std::cout << "□□□■□□□■□□□□□□□■□□□■■■□□□□□■□□□□□□□■□\n";
		moveToCoord(14, 15);
		std::cout << "□□□■□□□■■■■■□□□■□□□■□□■■□■■■■■□■■■■□□\n";
		moveToCoord(14, 16); 
		std::cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
		moveToCoord(30, 22);
		std::cout << "P R E S S  S P A C E  K E Y  T O  S T A R T...";

	}

	void drawGameOverScreen(const Board & bd) const
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x7);
		
		moveToCoord(boardDrawCoord.x, boardDrawCoord.y + 9);
		std::cout << "                    "; // 20 spaces
		moveToCoord(boardDrawCoord.x, boardDrawCoord.y + 10);
		std::cout << "  G A M E O V E R   ";
		moveToCoord(boardDrawCoord.x, boardDrawCoord.y + 11);
		std::cout << "                    ";
		moveToCoord(0, 0);
		Sleep(1000);
	}

	void drawGameFrame() const
	{
		system("cls");
		drawNextFrame();
		drawBoardFrame();
		drawInstruction();
	}

	void drawBoard(const Board & bd) const
	{
		const Board::BoardType & status = bd.boardStatus();
		int height = bd.getHeight();
		int width = bd.getWidth();
		for (int i = 0; i < height; ++i)
			for (int j = 0; j < width; ++j)
				if (status[i][j].occupied == true)	// false 시 else문을 통해 std::cout << "  "; 을 사용하면 간혹 게임이 매우 느려짐.
				{
					moveToCoord(boardDrawCoord.x + j * 2, boardDrawCoord.y + i);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(status[i][j].color));
					std::cout << "■";
				}
	}

	void eraseBoard(const Board & bd) const
	{
		const Board::BoardType & status = bd.boardStatus();
		int height = bd.getHeight();
		int width = bd.getWidth();
		for (int i = 0; i < height; ++i)
			for (int j = 0; j < width; ++j)
				if (status[i][j].occupied == true)	// false 시 else문을 통해 std::cout << "  "; 을 사용하면 간혹 게임이 매우 느려짐.
				{
					moveToCoord(boardDrawCoord.x + j * 2, boardDrawCoord.y + i);
					std::cout << "  ";
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



	void drawNextBlock(const BlockHandler & handle) const
	{
		Block::Color currentBlockColor = handle.nextBlk->getColor();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(currentBlockColor));
		for (auto & x : handle.nextBlk->getBlockInfo())
		{
			moveToCoord(26 + (x.x * 2), 5 + x.y);
			std::cout << "■";
		}
		moveToCoord(0, 0);
	}

	void eraseNextBlock(const BlockHandler & handle) const
	{
		for (auto & x : handle.nextBlk->getBlockInfo())
		{
			moveToCoord(26 + (x.x * 2), 5 + x.y);
			std::cout << "  ";
		}
		moveToCoord(0, 0);
	}


};