#pragma once

#include "tetris_block.h"
#include "tetris_blockhandler.h"
#include <array>
#include <vector>
#include <utility>

using std::vector;

class Board
{
public:
	struct cellInfo
	{
		bool occupied;
		Block::Color color;
		cellInfo() : occupied(false), color(Block::Color::WHITE) {}
	};
	typedef std::array<std::array<cellInfo, 10>, 25> BoardType;

private:
	int width;
	int height;
	BoardType board{};
	Coord entryPoint;

	bool isBlocked(const Coord & dest)
	{
		return board[dest.y][dest.x].occupied == true;	// 좌표와 배열 subscript 사이에는 반대 관계가 존재한다..
	}

	bool isBlocked(const Coord & currPos, const Block::BlockShape & blockShape)
	{
		for (auto & x : blockShape)
		{
			Coord temp = currPos + x;
			if (!isValid(temp) || isBlocked(temp))
				return true;
		}
		return false;
	}

	bool isValid(const Coord & dest)
	{
		return !(dest.x < 0 || dest.x >= width || dest.y < 0 || dest.y >= height);
	}

public:

	Board() = delete;

	Board(int wd, int ht) : width(wd), height(ht), entryPoint(width / 2, 1)
	{
		
	}

	const BoardType & boardStatus() const
	{
		return board;
	}

	int getWidth() const
	{
		return width;
	}

	int getHeight() const
	{
		return height;
	}
	
	bool isLeftBlocked(const BlockHandler & handler)
	{
		Coord temp(handler.currPos.x - 1, handler.currPos.y);
		return isBlocked(temp, handler.blk->getBlockInfo());
	}

	bool isRightBlocked(const BlockHandler & handler)
	{
		Coord temp(handler.currPos.x + 1, handler.currPos.y);
		return isBlocked(temp, handler.blk->getBlockInfo());
	}

	bool isDownBlocked(const BlockHandler & handler)
	{
		Coord temp(handler.currPos.x, handler.currPos.y + 1);
		return isBlocked(temp, handler.blk->getBlockInfo());
	}

	bool isNotRotatable(const BlockHandler & handler)
	{
		return isBlocked(handler.currPos, handler.blk->getNextBlockInfo());
	}

	bool isGameOver(const BlockHandler & handler)
	{
		return isBlocked(entryPoint, handler.blk->getBlockInfo());
	}

	void updateBoard(const BlockHandler & handler)	// critical section - updating board
	{
		Block::Color currentBlockColor = handler.blk->getColor();
		for (auto & blkInfo : handler.blk->getBlockInfo())
		{
			board[handler.currPos.y + blkInfo.y][handler.currPos.x + blkInfo.x].occupied = true;	// 반대 관계에 유의
			board[handler.currPos.y + blkInfo.y][handler.currPos.x + blkInfo.x].color = currentBlockColor;
		}

		std::vector<bool> lineChecker;
		int count;
		bool refreshFlag = false;
		for (int i = height - 1; i >= 0; --i)
		{
			count = 0;
			for (int j = 0; j < width; ++j)
			{
				if (board[i][j].occupied == true)
					++count;
				else
					break;
			}

			// push false if line is full, else push true;
			if (count == width)
			{
				lineChecker.push_back(false);
				refreshFlag = true;
			}
			else
				lineChecker.push_back(true);
		}

		if (refreshFlag == true)
		{
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

	const Coord entryCoord()
	{
		return entryPoint;
	}

};