#pragma once

#include "tetris_block.h"
#include "tetris_board.h"
#include "tetris_blockhandler.h"
#include "debug_drawer.h"
#include <conio.h>
#include <cstdlib>
#include <memory>
#include <ctime>
#include <iostream>
#include <windows.h>

class Game
{
private:	// 생성자에 정의된 순서가 아닌, 선언된 순서대로 초기화 됨에 유의
	Board board;
	BlockHandler handler;
	DebugDrawer debugDrawer;
	bool playing;
	

public:

	Game() : board(10, 25), handler(board.entryCoord()), playing(true)
	{
		std::srand(std::time(NULL));
		handler.reset(); // initialize handler
	}

	void play()
	{
		debugDrawer.debugDrawBoard(board);
		debugDrawer.debugDrawHandler(handler);
		while (playing)
		{
			if (board.isGameOver(handler.blk->getBlockInfo()))
			{
				playing = false;
				Sleep(75);
				debugDrawer.debugDrawGameover(board, handler);
				break;
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
				debugDrawer.debugDrawHandler(handler);
			}
			Sleep(75);
		}
	}
	
	void moveLeft()
	{
		if (!board.isLeftBlocked(handler.currPos, handler.blk->getBlockInfo()))
		{
			debugDrawer.debugDrawEraseHandler(handler);
			handler.currPos.x -= 1;
			debugDrawer.debugDrawHandler(handler);
		}
	}

	void moveRight()
	{
		if (!board.isRightBlocked(handler.currPos, handler.blk->getBlockInfo()))
		{
			debugDrawer.debugDrawEraseHandler(handler);
			handler.currPos.x += 1;
			debugDrawer.debugDrawHandler(handler);
		}
	}

	bool moveDown()
	{
		if (!board.isDownBlocked(handler.currPos, handler.blk->getBlockInfo()))
		{
			debugDrawer.debugDrawEraseHandler(handler);
			handler.currPos.y += 1;
			debugDrawer.debugDrawHandler(handler);
			return true;
		}
		else
		{
			board.updateBoard(handler.currPos, handler.blk->getBlockInfo());	// write the block to current board.
			handler.reset();													// and initialize a new block.
			if (!board.isGameOver(handler.blk->getBlockInfo()))
				debugDrawer.debugDrawBoard(board);
			return false;
		}

	}

	void rotate()
	{
		if (!board.isNotRotatable(handler.currPos, handler.blk->getNextBlockInfo()))
		{
			debugDrawer.debugDrawEraseHandler(handler);
			handler.blk->rotate();
			debugDrawer.debugDrawHandler(handler);
		}
	}

};