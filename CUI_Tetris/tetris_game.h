#pragma once

#include "tetris_block.h"
#include "tetris_board.h"
#include "tetris_blockhandler.h"
#include "tetris_drawer.h"
#include <conio.h>
#include <cstdlib>
#include <memory>
#include <ctime>
#include <iostream>
#include <windows.h>

static int normalLevel = 10;

class Game
{
private:	// 생성자에 정의된 순서가 아닌, 선언된 순서대로 초기화 됨에 유의
	Drawer drawer;
	Board board;
	BlockHandler handler;
	int difficulty;
	
	void pressSpaceToContinue() const
	{
		while (true)
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				Sleep(500);
				break;
			}
	}

	void readUserMove()
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
			rotate();
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			moveDown();
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			moveLeft();
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			moveRight();
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			while (moveDown())
				continue;
			drawer.drawCurrentBlock(handler);
			drawer.drawNextBlock(handler);
		}
		Sleep(100);
	}

	void drawHandlerContent() const
	{
		drawer.drawCurrentBlock(handler);
		drawer.drawNextBlock(handler);
	}

	void eraseHandlerContent() const
	{
		drawer.eraseCurrentBlock(handler);
		drawer.eraseNextBlock(handler);
	}

public:

	Game(int level) : board(), handler(board.entryCoord()), difficulty(level - 1)
	{
		std::srand(std::time(NULL));
	}

	void play()
	{
		drawer.drawTitleScreen(); // temp
		pressSpaceToContinue();
		drawer.drawGameFrame();
		drawer.drawBoard(board);
		drawHandlerContent();
		int countForAutoDown = 0;
		int countLimit = normalLevel - difficulty;
		while (true)
		{
			if (board.isGameOver(handler))
			{
				Sleep(75);
				drawer.drawGameOverScreen(board);
				break;
			}
			
			++countForAutoDown;
			if (countForAutoDown == countLimit)	// 1 second
			{
				moveDown();
				countForAutoDown = 0;
			}

			readUserMove();
		}
	}
	
	void moveLeft()
	{
		if (!board.isLeftBlocked(handler))
		{
			eraseHandlerContent();
			handler.currPos.x -= 1;
			drawHandlerContent();
		}
	}

	void moveRight()
	{
		if (!board.isRightBlocked(handler))
		{
			eraseHandlerContent();
			handler.currPos.x += 1;
			drawHandlerContent();
		}
	}

	bool moveDown()
	{
		if (!board.isDownBlocked(handler))
		{
			eraseHandlerContent();
			handler.currPos.y += 1;
			drawHandlerContent();
			return true;
		}
		else
		{
			drawer.eraseBoard(board);
			eraseHandlerContent();

			board.updateBoard(handler);	
			handler.resetHandler();

			if (!board.isGameOver(handler))
			{
				drawer.drawBoard(board);
				drawHandlerContent();
			}
			return false;
		}

	}

	void rotate()
	{
		if (!board.isNotRotatable(handler))
		{
			drawer.eraseCurrentBlock(handler);
			drawer.eraseNextBlock(handler);
			handler.blk->rotate();
			drawer.drawCurrentBlock(handler);
			drawer.drawNextBlock(handler);
		}
	}

};