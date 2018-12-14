#pragma once

#include "tetris_block.h"
#include "tetris_blockhandler.h"
#include <array>
#include <utility>
#include <vector>

/**
  @brief 블럭이 배치될 보드 판.
 */
class Board
{
public:
	/**
	  @brief 보드 내 각 셀에 대한 정보(채워져 있나 여부, 채운 블럭의 색상) 저장.
	*/
	struct cellInfo
	{
		bool occupied;
		Block::Color color;
		cellInfo() : occupied(false), color(Block::Color::WHITE) {}
	};
	typedef std::array<std::array<cellInfo, 10>, 25> BoardType;		//!< 25 * 10의 cellInfo 2차원 배열로 보드를 나타냄

private:
	const int width;				//!< 보드의 너비(25)
	const int height;				//!< 보드의 높이(10)
	BoardType board{};				//!< 보드(cellInfo 2차원 배열)
	const Coord entryPoint;			//!< 보드 내 블럭의 진입 지점 - width와 height 다음에 선언되어야 한다

	//! 좌표에 해당하는 자리에 이미 블럭이 있는지를 리턴
	bool isBlocked(const Coord & dest) const
	{
		// 좌표와 배열 subscript 사이에는 반대 관계가 존재함에 유의
		return board[dest.y][dest.x].occupied == true;	
	}

	bool isValid(const Coord & dest) const
	{
		return !(dest.x < 0 || dest.x >= width || dest.y < 0 || dest.y >= height);
	}

	//! 해당하는 자리가 막혀있는지를 리턴
	/**
	  @brief 현 위치와 현재 회전 상태를 읽어, 블럭의 자리에 다른 블럭이 막혀있는지를 리턴
	  @param currPos : 현재 좌표
	  @param blockShape : 현재 회전 상태에 따른 블럭 모양
	 */
	bool isBlocked(const Coord & currPos, const Block::BlockShape & blockShape) const
	{
		for (auto & x : blockShape)
		{
			Coord temp = currPos + x;
			// 좌우 순서 중요(순서 변경 시 array out of bound 예외 발생)
			if (!isValid(temp) || isBlocked(temp))
				return true;
		}
		return false;
	}

	

public:

	//! 25 * 10 보드를 생성하고, 진입 지점을 설정한다.
	Board() : width(10), height(25), entryPoint(width / 2, 1)
	{
		
	}

	//! 보드의 현재 상태를 리턴한다
	const BoardType & boardStatus() const
	{
		return board;
	}

	//! 보드의 너비를 리턴한다
	int getWidth() const
	{
		return width;
	}

	//! 보드의 높이를 리턴한다
	int getHeight() const
	{
		return height;
	}
	
	//! 현재 블럭의 왼쪽이 막혀 있는 지를 리턴
	bool isLeftBlocked(const BlockHandler & handler) const
	{
		Coord temp(handler.currPos.x - 1, handler.currPos.y); // 현 위치를 왼쪽으로 1칸 옮긴 임시 위치 생성
		return isBlocked(temp, handler.blk->getBlockInfo());  // 임시 위치가 막혀 있는지를 리턴
	}

	//! 현재 블럭의 오른쪽이 막혀 있는 지를 리턴
	bool isRightBlocked(const BlockHandler & handler) const
	{
		Coord temp(handler.currPos.x + 1, handler.currPos.y);
		return isBlocked(temp, handler.blk->getBlockInfo());
	}

	//! 현재 블럭의 아래가 막혀 있는 지를 리턴
	bool isDownBlocked(const BlockHandler & handler) const
	{
		Coord temp(handler.currPos.x, handler.currPos.y + 1);
		return isBlocked(temp, handler.blk->getBlockInfo());
	}

	//! 현재 블럭이 회전 불가능한지를 리턴
	bool isNotRotatable(const BlockHandler & handler) const
	{
		return isBlocked(handler.currPos, handler.blk->getNextBlockInfo()); // 현재 블럭을 회전했을 경우 막히는지를 리턴
	}

	//! 현재 블럭이 보드에 진입 가능한지를 리턴
	bool isGameOver(const BlockHandler & handler) const
	{
		return isBlocked(entryPoint, handler.blk->getBlockInfo());
	}

	//! 블럭이 끝에 도달했을 때, 이를 보드에 기록한다. 줄이 꽉찼다면 보드를 새로 고친다.
	void updateBoard(const BlockHandler & handler)
	{
		// 현재 블럭의 정보를 보드에 반영한다.
		Block::Color currentBlockColor = handler.blk->getColor();
		for (auto & blkInfo : handler.blk->getBlockInfo())
		{
			// 좌표와 배열 subscript 사이에는 반대 관계가 존재함에 유의
			board[handler.currPos.y + blkInfo.y][handler.currPos.x + blkInfo.x].occupied = true;
			board[handler.currPos.y + blkInfo.y][handler.currPos.x + blkInfo.x].color = currentBlockColor;
		}

		// 꽉찬 줄이 있는지 검사한다.
		std::vector<bool> lineChecker;
		int count;
		bool refreshFlag = false;
		// 보드의 위에서부터 아래로 꽉찬 줄을 검사한다.
		for (int i = height - 1; i >= 0; --i)
		{
			count = 0;
			// 이번 줄의 찬 자리를 센다.
			for (int j = 0; j < width; ++j)
			{
				if (board[i][j].occupied == true)
					++count;
				else
					break;
			}

			// 줄이 꽉찼다면 false, 반대라면 true를 push한다.
			if (count == width)
			{
				lineChecker.push_back(false);
				refreshFlag = true;
			}
			else
				lineChecker.push_back(true);
		}

		// 만약 꽉찬 줄이 하나라도 있다면, 보드를 새로 고친다.
		if (refreshFlag == true)
		{
			// 새 보드를 생성하여 기존 보드로부터 정보를 받되, 꽉 찬 줄은 스킵한다.
			BoardType newBoard {};
			int j = lineChecker.size() - 1;
			for (int i = lineChecker.size() - 1; i >= 0; --i)
				if (lineChecker[lineChecker.size() - 1 - i] == true)
				{
					for (int k = 0; k < width; ++k)
						newBoard[j][k] = board[i][k];
					--j;
				}
			board = newBoard;
		}
}

	//! 진입 지점을 리턴한다
	Coord entryCoord() const
	{
		return entryPoint;
	}

};