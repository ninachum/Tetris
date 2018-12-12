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
	//BlockHandler nextHandler;
	bool playing;

public:

	Game() : board(10, 25), handler(board.entryCoord()), /*nextHandler(drawer.nextEntryPoint()),*/ playing(true)
	{
		std::srand(std::time(NULL));
	}

	void play()
	{
		drawer.drawgGameFrame();
		drawer.drawBoard(board);
		drawer.drawHandler(handler);
		int countForAutoDown = 0;
		while (playing)
		{
			if (board.isGameOver(handler))
			{
				playing = false;
				Sleep(75);
				drawer.drawGameover(board);
				break;
			}
			
			++countForAutoDown;
			if (countForAutoDown == 10)	// 1 second
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
			}
			Sleep(100);
		}
	}
	
	void moveLeft()
	{
		if (!board.isLeftBlocked(handler))
		{
			drawer.eraseHandler(handler);
			handler.currPos.x -= 1;
			drawer.drawHandler(handler);
		}
	}

	void moveRight()
	{
		if (!board.isRightBlocked(handler))
		{
			drawer.eraseHandler(handler);
			handler.currPos.x += 1;
			drawer.drawHandler(handler);
		}
	}

	bool moveDown()
	{
		if (!board.isDownBlocked(handler))
		{
			drawer.eraseHandler(handler);
			handler.currPos.y += 1;
			drawer.drawHandler(handler);
			return true;
		}
		else
		{
			drawer.eraseBoard(board);
			drawer.eraseHandler(handler);
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
			}
			return false;
		}

	}

	void rotate()
	{
		if (!board.isNotRotatable(handler))
		{
			drawer.eraseHandler(handler);
			handler.blk->rotate();
			drawer.drawHandler(handler);
		}
	}

};