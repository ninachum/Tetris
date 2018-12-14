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

//! 난이도 설정의 기준점. 10일 경우 1000ms 당 블럭을 한 칸 내린다.
static int normalLevel = 10;

/**
  @brief Board, BlockHandler, Drawer를 이용하여 게임을 시작, 진행, 종료한다.
 */
class Game
{
private:
	// 생성자에 정의된 순서가 아닌, 선언된 순서대로 초기화 됨에 유의
	Drawer drawer;
	Board board;
	BlockHandler handler;
	int difficulty;	//!< 난이도를 나타내는 변수. 1 - 5의 범위를 가지며, 1 높아질 수록 블럭이 100ms 빨리 내려간다.
	
	//! 사용자가 스페이스를 누를 때까지 대기한다.
	void pressSpaceToContinue() const
	{
		while (true)
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				Sleep(500);
				break;
			}
	}

	//! 사용자의 조작을 읽어 블럭을 조작한다.
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

	//! 현재 블럭과 다음 블럭을 그리는 함수를 호출하는 함수.
	void drawHandlerContent() const
	{
		drawer.drawCurrentBlock(handler);
		drawer.drawNextBlock(handler);
	}

	//! 현재 블럭과 다음 블럭을 지우는 함수를 호출하는 함수.
	void eraseHandlerContent() const
	{
		drawer.eraseCurrentBlock(handler);
		drawer.eraseNextBlock(handler);
	}

public:

	//! 게임의 초기 설정(블럭, 진입 위치, 난이도, 난수 시드 초기화)을 진행한다.
	Game(int level) : board(), handler(board.entryCoord()), difficulty(level - 1)
	{
		std::srand(std::time(NULL));
	}

	//! 게임을 실행한다.
	void play()
	{
		drawer.drawTitleScreen(); 
		pressSpaceToContinue();
		drawer.drawGameFrame();
		drawer.drawBoard(board);
		drawHandlerContent();
		int countForAutoDown = 0;					// 100ms에 1 증가하는 카운트. 블럭 자동 내림에 사용
		int countLimit = normalLevel - difficulty;  // 난이도가 1에서 오를 수록 1000ms에서 100ms씩 감소하는 카운트 제한
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
	
	//! 왼쪽으로 움직일 수 있으면, 현 블럭을 옮기고 새로 그린다.
	void moveLeft()
	{
		if (!board.isLeftBlocked(handler))
		{
			eraseHandlerContent();
			handler.currPos.x -= 1;
			drawHandlerContent();
		}
	}

	//! 오른쪽으로 움직일 수 있으면, 현 블럭을 옮기고 새로 그린다.
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
	 * 아래로 움직일 수 있으면, 현 블럭을 옮기고 새로 그린다.
	 * 아니라면, 보드와 현 블럭, 그리고 다음 블럭을 화면에서 지우고, 새로 고쳐 다시 그린다.
	 * @return 아래로 움직였는 지 여부 
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

			// 게임 오버라면 보드, 현 블럭, 그리고 다음 블럭을 다시 그리는 과정은 생략한다.
			if (!board.isGameOver(handler))
			{
				drawer.drawBoard(board);
				drawHandlerContent();
			}
			return false;
		}
	}

	//! 현 블럭을 회전시킬 수 있으면 회전시킨다.
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