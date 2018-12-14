#pragma once

#include "tetris_board.h"
#include "tetris_blockhandler.h"
#include <array>
#include <iostream>
#include <Windows.h>

static const Coord boardDrawCoord { 38, 4 };		//!< 보드를 그릴 때, 기준 좌표
static const Coord boardFrameDrawCoord{ 36, 3 };	//!< 보드 프레임을 그릴 때, 기준 좌표
static const Coord nextFrameDrawCoord { 22, 2 };	//!< 다음 블럭을 나타낼 자리에 프레임을 그릴 때, 기준 좌표
static const Coord instructionDrawCoord{ 64, 23 };	//!< 게임 플레이 방법을 그릴 때, 기준 좌표
static const Coord titleScreenDrawCoord{ 14, 10 };	//!< 타이틀 화면을 그릴 때, 기준 좌표

/**
  @brief 화면에 게임을 출력하는 클래스
 */
class Drawer
{
private:
	//! 해당 좌표로 커서를 이동시킴
	void moveToCoord(int x, int y) const
	{
		COORD cursor;
		cursor.X = x;
		cursor.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
	}

	//! 다음 블럭을 나타낼 자리에 프레임을 그림
	void drawNextFrame() const
	{
		moveToCoord(nextFrameDrawCoord.x, nextFrameDrawCoord.y);
		std::cout << " N  E  X  T";
		moveToCoord(nextFrameDrawCoord.x, nextFrameDrawCoord.y + 1);
		for (int i = 0; i < 6; ++i)
			std::cout << "▩";
		for (int i = nextFrameDrawCoord.y + 2; i < nextFrameDrawCoord.y + 5; ++i)
		{
			moveToCoord(nextFrameDrawCoord.x, i);
			std::cout << "▩";
			moveToCoord(nextFrameDrawCoord.x + 10, i);
			std::cout << "▩";
		}
		moveToCoord(nextFrameDrawCoord.x, nextFrameDrawCoord.y + 5);
		for (int i = 0; i < 6; ++i)
			std::cout << "▩";
	}

	//! 보드 프레임을 그림
	void drawBoardFrame() const
	{
		moveToCoord(boardFrameDrawCoord.x, boardFrameDrawCoord.y);
		for (int i = 0; i < 12; ++i)
			std::cout << "▩";
		for (int i = boardFrameDrawCoord.y + 1; i < boardFrameDrawCoord.y + 26; ++i)
		{
			moveToCoord(boardFrameDrawCoord.x, i);
			std::cout << "▩";
			moveToCoord(boardFrameDrawCoord.x + 22, i);
			std::cout << "▩";
		}
		moveToCoord(boardFrameDrawCoord.x, boardFrameDrawCoord.y + 26);
		for (int i = 0; i < 12; ++i)
			std::cout << "▩";
	}

	//! 게임 플레이 방법을 그림
	void drawInstruction() const
	{
		moveToCoord(instructionDrawCoord.x, instructionDrawCoord.y);
		std::cout << "  HOW TO PLAY";
		moveToCoord(instructionDrawCoord.x, instructionDrawCoord.y + 1);
		std::cout << "  ▲ to rotate";
		moveToCoord(instructionDrawCoord.x, instructionDrawCoord.y + 2);
		std::cout << "◀▼▶ to move";
		moveToCoord(instructionDrawCoord.x, instructionDrawCoord.y + 3);
		std::cout << " SPACE to drop";
	}

public:

	Drawer() {}

	//! 타이틀 화면을 그림
	void drawTitleScreen() const
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x7);

		moveToCoord(titleScreenDrawCoord.x, titleScreenDrawCoord.y); // temporary
		std::cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
		moveToCoord(titleScreenDrawCoord.x, titleScreenDrawCoord.y + 1);
		std::cout << "□■■■■■□■■■■■□■■■■■□■■■■□□■■■■■□□■■■■□\n";
		moveToCoord(titleScreenDrawCoord.x, titleScreenDrawCoord.y + 2);
		std::cout << "□□□■□□□■□□□□□□□■□□□■□□□■□□□■□□□■□□□□□\n";
		moveToCoord(titleScreenDrawCoord.x, titleScreenDrawCoord.y + 3);
		std::cout << "□□□■□□□■■■■■□□□■□□□■■■■□□□□■□□□□■■■■□\n";
		moveToCoord(titleScreenDrawCoord.x, titleScreenDrawCoord.y + 4);
		std::cout << "□□□■□□□■□□□□□□□■□□□■■■□□□□□■□□□□□□□■□\n";
		moveToCoord(titleScreenDrawCoord.x, titleScreenDrawCoord.y + 5);
		std::cout << "□□□■□□□■■■■■□□□■□□□■□□■■□■■■■■□■■■■□□\n";
		moveToCoord(titleScreenDrawCoord.x, titleScreenDrawCoord.y + 6);
		std::cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
		moveToCoord(titleScreenDrawCoord.x + 16, titleScreenDrawCoord.y + 12);
		std::cout << "P R E S S  S P A C E  K E Y  T O  S T A R T...";

	}

	//! 게임오버 화면을 그림
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

	//! 게임 플레이에 필요한 프레임들을 그림
	void drawGameFrame() const
	{
		system("cls");
		drawNextFrame();
		drawBoardFrame();
		drawInstruction();
	}

	//! 보드를 그림
	void drawBoard(const Board & bd) const
	{
		const Board::BoardType & status = bd.boardStatus();
		for (int i = 0; i < 25; ++i)
			for (int j = 0; j < 10; ++j)
				if (status[i][j].occupied == true)	// false 시 else문을 통해 std::cout << "  "; 을 사용하면 간혹 게임이 매우 느려짐.
				{
					moveToCoord(boardDrawCoord.x + j * 2, boardDrawCoord.y + i);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(status[i][j].color));
					std::cout << "■";
				}
	}

	//! 보드를 지움
	void eraseBoard(const Board & bd) const
	{
		const Board::BoardType & status = bd.boardStatus();
		for (int i = 0; i < 25; ++i)
			for (int j = 0; j < 10; ++j)
				if (status[i][j].occupied == true)	// false 시 else문을 통해 std::cout << "  "; 을 사용하면 간혹 게임이 매우 느려짐.
				{
					moveToCoord(boardDrawCoord.x + j * 2, boardDrawCoord.y + i);
					std::cout << "  ";
				}
	}

	//! 현재 블럭을 그림
	void drawCurrentBlock(const BlockHandler & handle) const
	{
		Block::Color currentBlockColor = handle.blk->getColor();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(currentBlockColor));
		for (auto & cellInfo : handle.blk->getBlockInfo())
		{
			Coord temp = handle.currPos + cellInfo;
			moveToCoord(boardDrawCoord.x + temp.x * 2, boardDrawCoord.y + temp.y);
			std::cout << "■";
		}
	}

	//! 현재 블럭을 지움
	void eraseCurrentBlock(const BlockHandler & handle) const
	{
		for (auto & cellInfo : handle.blk->getBlockInfo())
		{
			Coord temp = handle.currPos + cellInfo;
			moveToCoord(boardDrawCoord.x + temp.x * 2, boardDrawCoord.y + temp.y);
			std::cout << "  ";
		}
	}

	//! 다음 블럭을 그림
	void drawNextBlock(const BlockHandler & handle) const
	{
		Block::Color currentBlockColor = handle.nextBlk->getColor();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(currentBlockColor));
		for (auto & cellInfo : handle.nextBlk->getBlockInfo())
		{
			moveToCoord(nextFrameDrawCoord.x + 4 + (cellInfo.x * 2), nextFrameDrawCoord.y + 3 + cellInfo.y);
			std::cout << "■";
		}
		moveToCoord(0, 0);	// 게임 플레이시 커서가 화면 구석에서 깜빡거리도록 좌표를 구석으로 이동시킴
	}

	//! 다음 블럭을 지움
	void eraseNextBlock(const BlockHandler & handle) const
	{
		for (auto & cellInfo : handle.nextBlk->getBlockInfo())
		{
			moveToCoord(nextFrameDrawCoord.x + 4 + (cellInfo.x * 2), nextFrameDrawCoord.y + 3 + cellInfo.y);
			std::cout << "  ";
		}
		moveToCoord(0, 0);
	}


};