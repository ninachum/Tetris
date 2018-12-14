#pragma once

#include "tetris_board.h"
#include "tetris_blockhandler.h"
#include "tetris_drawer.h"
#include <conio.h>
#include <cstdlib>
#include <memory>
#include <ctime>
#include <iostream>
#include <windows.h>

//! ���̵� ������ ������. 10�� ��� 1000ms �� ���� �� ĭ ������.
static int normalLevel = 10;

/**
  @brief Board, BlockHandler, Drawer�� �̿��Ͽ� ������ ����, ����, �����Ѵ�.
 */
class Game
{
private:
	// �����ڿ� ���ǵ� ������ �ƴ�, ����� ������� �ʱ�ȭ �ʿ� ����
	Drawer drawer;
	Board board;
	BlockHandler handler;
	int difficulty;	//!< ���̵��� ��Ÿ���� ����. 1 - 5�� ������ ������, 1 ������ ���� ���� 100ms ���� ��������.
	
	//! ����ڰ� �����̽��� ���� ������ ����Ѵ�.
	void pressSpaceToContinue() const
	{
		while (true)
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				Sleep(500);
				break;
			}
	}

	//! ������� ������ �о� ���� �����Ѵ�.
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
			drawHandlerContent();
		}
		Sleep(100);
	}

	//! ���� ���� ���� ���� �׸��� �Լ��� ȣ���ϴ� �Լ�.
	void drawHandlerContent() const
	{
		drawer.drawCurrentBlock(handler);
		drawer.drawNextBlock(handler);
	}

	//! ���� ���� ���� ���� ����� �Լ��� ȣ���ϴ� �Լ�.
	void eraseHandlerContent() const
	{
		drawer.eraseCurrentBlock(handler);
		drawer.eraseNextBlock(handler);
	}

public:

	//! ������ �ʱ� ����(��, ���� ��ġ, ���̵�, ���� �õ� �ʱ�ȭ)�� �����Ѵ�.
	Game(int level) : board(), handler(board.entryCoord()), difficulty(level - 1)
	{
		std::srand(std::time(NULL));
	}

	//! ������ �����Ѵ�.
	void play()
	{
		drawer.drawTitleScreen(); 
		pressSpaceToContinue();
		drawer.drawGameFrame();
		drawer.drawBoard(board);
		drawHandlerContent();
		int countForAutoDown = 0;					// 100ms�� 1 �����ϴ� ī��Ʈ. �� �ڵ� ������ ���
		int countLimit = normalLevel - difficulty;  // ���̵��� 1���� ���� ���� 1000ms���� 100ms�� �����ϴ� ī��Ʈ ����
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
	
	//! �������� ������ �� ������, �� ���� �ű�� ���� �׸���.
	void moveLeft()
	{
		if (!board.isLeftBlocked(handler))
		{
			eraseHandlerContent();
			handler.currPos.x -= 1;
			drawHandlerContent();
		}
	}

	//! ���������� ������ �� ������, �� ���� �ű�� ���� �׸���.
	void moveRight()
	{
		if (!board.isRightBlocked(handler))
		{
			eraseHandlerContent();
			handler.currPos.x += 1;
			drawHandlerContent();
		}
	}

	/*!
	 * @details
	 * �Ʒ��� ������ �� ������, �� ���� �ű�� ���� �׸���.
	 * �ƴ϶��, ����� �� ��, �׸��� ���� ���� ȭ�鿡�� �����, ���� ���� �ٽ� �׸���.
	 * @return �Ʒ��� �������� �� ���� 
	 */
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

			// ���� ������� ����, �� ��, �׸��� ���� ���� �ٽ� �׸��� ������ �����Ѵ�.
			if (!board.isGameOver(handler))
			{
				drawer.drawBoard(board);
				drawHandlerContent();
			}
			return false;
		}
	}

	//! �� ���� ȸ����ų �� ������ ȸ����Ų��.
	void rotate()
	{
		if (!board.isNotRotatable(handler))
		{
			eraseHandlerContent();
			handler.blk->rotate();
			drawHandlerContent();
		}
	}
};