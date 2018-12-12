#pragma once

#include "tetris_block.h"
#include <array>
#include <vector>
#include <utility>

using std::vector;



class Board
{
public:
	typedef std::array<std::array<bool, 10>, 25> boardType;

private:
	int width;
	int height;
	boardType board;
	Coord entryPoint;

	bool isBlocked(const Coord & dest)
	{
		return board[dest.y][dest.x] == true;	// 좌표와 배열 subscript 사이에는 반대 관계가 존재한다..
	}

	bool isBlocked(const Coord & currPos, const vector<Coord> & blockShape)
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

	Board(int wd, int ht) : width(wd), height(ht), entryPoint(width / 2, 1) {}

	const boardType & boardStatus() const
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

	bool isLeftBlocked(const Coord & currPos, const vector<Coord> & blockShape)
	{
		Coord temp(currPos.x - 1, currPos.y);
		return isBlocked(temp, blockShape);
	}

	bool isRightBlocked(const Coord & currPos, const vector<Coord> & blockShape)
	{
		Coord temp(currPos.x + 1, currPos.y);
		return isBlocked(temp, blockShape);
	}

	bool isDownBlocked(const Coord & currPos, const vector<Coord> & blockShape)
	{
		Coord temp(currPos.x, currPos.y + 1);
		return isBlocked(temp, blockShape);
	}

	bool isNotRotatable(const Coord & currPos, const vector<Coord> & nextBlockShape)
	{
		return isBlocked(currPos, nextBlockShape);
	}

	bool isGameOver(const vector<Coord> & blockShape)
	{
		return isBlocked(entryPoint, blockShape);
	}

	void updateBoard(const Coord & currPos, const vector<Coord> & blockShape)	// critical section - updating board
	{
		for (auto & blkInfo : blockShape)
			board[currPos.y + blkInfo.y][currPos.x + blkInfo.x] = true;	// 반대 관계에 유의

		std::vector<bool> lineChecker;
		int count;
		bool refreshFlag = false;
		for (int i = height - 1; i >= 0; --i)
		{
			count = 0;
			for (int j = 0; j < width; ++j)
			{
				if (board[i][j] == true)
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
			boardType newBoard{};
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