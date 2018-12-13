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

class Game
{
private:	// 생성자에 정의된 순서가 아닌, 선언된 순서대로 초기화 됨에 유의
	Drawer drawer;
	Board board;
	BlockHandler handler;
	int difficulty;

public:

	Game(int level) : board(10, 25), handler(board.entryCoord()), difficulty(level)
	{
		std::srand(std::time(NULL));
	}

	void play()
	{
		drawer.drawTitleScreen(); // temp
		while (true)
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				Sleep(500);
				break;
			}

		drawer.drawGameFrame();
		drawer.drawBoard(board);
		drawer.drawHandler(handler);
		drawer.drawNextBlock(handler);
		int countForAutoDown = 0;
		int countLimit = 11 - difficulty;
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
				drawer.drawHandler(handler);
				drawer.drawNextBlock(handler);
			}
			Sleep(100);
		}
	}
	
	void moveLeft()
	{
		if (!board.isLeftBlocked(handler))
		{
			drawer.eraseHandler(handler);
			drawer.eraseNextBlock(handler);
			handler.currPos.x -= 1;
			drawer.drawHandler(handler);
			drawer.drawNextBlock(handler);
		}
	}

	void moveRight()
	{
		if (!board.isRightBlocked(handler))
		{
			drawer.eraseHandler(handler);
			drawer.eraseNextBlock(handler);
			handler.currPos.x += 1;
			drawer.drawHandler(handler);
			drawer.drawNextBlock(handler);
		}
	}

	bool moveDown()
	{
		if (!board.isDownBlocked(handler))
		{
			drawer.eraseHandler(handler);
			drawer.eraseNextBlock(handler);
			handler.currPos.y += 1;
			drawer.drawHandler(handler);
			drawer.drawNextBlock(handler);
			return true;
		}
		else
		{
			drawer.eraseBoard(board);
			drawer.eraseHandler(handler);
			drawer.eraseNextBlock(handler);
			board.updateBoard(handler);	// write the block to current board.

			//handler.transferBlockFrom(nextHandler);			// and initialize a new block.!!!
			//drawer.eraseHandler(nextHandler);
			//nextHandler.resetHandler();
			//drawer.drawHandler(nextHandler);
			handler.resetHandler();
			if (!board.isGameOver(handler))
			{
				drawer.drawBoard(board);
				drawer.drawHandler(handler);
				drawer.drawNextBlock(handler);
			}
			return false;
		}

	}

	void rotate()
	{
		if (!board.isNotRotatable(handler))
		{
			drawer.eraseHandler(handler);
			drawer.eraseNextBlock(handler);
			handler.blk->rotate();
			drawer.drawHandler(handler);
			drawer.drawNextBlock(handler);
		}
	}

};