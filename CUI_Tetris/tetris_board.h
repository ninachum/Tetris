#pragma once

#include "tetris_block.h"
#include "tetris_blockhandler.h"
#include <array>
#include <utility>
#include <vector>

/**
  @brief ���� ��ġ�� ���� ��.
 */
class Board
{
public:
	/**
	  @brief ���� �� �� ���� ���� ����(ä���� �ֳ� ����, ä�� ���� ����) ����.
	*/
	struct cellInfo
	{
		bool occupied;
		Block::Color color;
		cellInfo() : occupied(false), color(Block::Color::WHITE) {}
	};
	typedef std::array<std::array<cellInfo, 10>, 25> BoardType;		//!< 25 * 10�� cellInfo 2���� �迭�� ���带 ��Ÿ��

private:
	const int width;				//!< ������ �ʺ�(25)
	const int height;				//!< ������ ����(10)
	BoardType board{};				//!< ����(cellInfo 2���� �迭)
	const Coord entryPoint;			//!< ���� �� ���� ���� ���� - width�� height ������ ����Ǿ�� �Ѵ�

	//! ��ǥ�� �ش��ϴ� �ڸ��� �̹� ���� �ִ����� ����
	bool isBlocked(const Coord & dest) const
	{
		// ��ǥ�� �迭 subscript ���̿��� �ݴ� ���谡 �����Կ� ����
		return board[dest.y][dest.x].occupied == true;	
	}

	bool isValid(const Coord & dest) const
	{
		return !(dest.x < 0 || dest.x >= width || dest.y < 0 || dest.y >= height);
	}

	//! �ش��ϴ� �ڸ��� �����ִ����� ����
	/**
	  @brief �� ��ġ�� ���� ȸ�� ���¸� �о�, ���� �ڸ��� �ٸ� ���� �����ִ����� ����
	  @param currPos : ���� ��ǥ
	  @param blockShape : ���� ȸ�� ���¿� ���� �� ���
	 */
	bool isBlocked(const Coord & currPos, const Block::BlockShape & blockShape) const
	{
		for (auto & x : blockShape)
		{
			Coord temp = currPos + x;
			// �¿� ���� �߿�(���� ���� �� array out of bound ���� �߻�)
			if (!isValid(temp) || isBlocked(temp))
				return true;
		}
		return false;
	}

	

public:

	//! 25 * 10 ���带 �����ϰ�, ���� ������ �����Ѵ�.
	Board() : width(10), height(25), entryPoint(width / 2, 1)
	{
		
	}

	//! ������ ���� ���¸� �����Ѵ�
	const BoardType & boardStatus() const
	{
		return board;
	}

	//! ������ �ʺ� �����Ѵ�
	int getWidth() const
	{
		return width;
	}

	//! ������ ���̸� �����Ѵ�
	int getHeight() const
	{
		return height;
	}
	
	//! ���� ���� ������ ���� �ִ� ���� ����
	bool isLeftBlocked(const BlockHandler & handler) const
	{
		Coord temp(handler.currPos.x - 1, handler.currPos.y); // �� ��ġ�� �������� 1ĭ �ű� �ӽ� ��ġ ����
		return isBlocked(temp, handler.blk->getBlockInfo());  // �ӽ� ��ġ�� ���� �ִ����� ����
	}

	//! ���� ���� �������� ���� �ִ� ���� ����
	bool isRightBlocked(const BlockHandler & handler) const
	{
		Coord temp(handler.currPos.x + 1, handler.currPos.y);
		return isBlocked(temp, handler.blk->getBlockInfo());
	}

	//! ���� ���� �Ʒ��� ���� �ִ� ���� ����
	bool isDownBlocked(const BlockHandler & handler) const
	{
		Coord temp(handler.currPos.x, handler.currPos.y + 1);
		return isBlocked(temp, handler.blk->getBlockInfo());
	}

	//! ���� ���� ȸ�� �Ұ��������� ����
	bool isNotRotatable(const BlockHandler & handler) const
	{
		return isBlocked(handler.currPos, handler.blk->getNextBlockInfo()); // ���� ���� ȸ������ ��� ���������� ����
	}

	//! ���� ���� ���忡 ���� ���������� ����
	bool isGameOver(const BlockHandler & handler) const
	{
		return isBlocked(entryPoint, handler.blk->getBlockInfo());
	}

	//! ���� ���� �������� ��, �̸� ���忡 ����Ѵ�. ���� ��á�ٸ� ���带 ���� ��ģ��.
	void updateBoard(const BlockHandler & handler)
	{
		// ���� ���� ������ ���忡 �ݿ��Ѵ�.
		Block::Color currentBlockColor = handler.blk->getColor();
		for (auto & blkInfo : handler.blk->getBlockInfo())
		{
			// ��ǥ�� �迭 subscript ���̿��� �ݴ� ���谡 �����Կ� ����
			board[handler.currPos.y + blkInfo.y][handler.currPos.x + blkInfo.x].occupied = true;
			board[handler.currPos.y + blkInfo.y][handler.currPos.x + blkInfo.x].color = currentBlockColor;
		}

		// ���� ���� �ִ��� �˻��Ѵ�.
		std::vector<bool> lineChecker;
		int count;
		bool refreshFlag = false;
		// ������ ���������� �Ʒ��� ���� ���� �˻��Ѵ�.
		for (int i = height - 1; i >= 0; --i)
		{
			count = 0;
			// �̹� ���� �� �ڸ��� ����.
			for (int j = 0; j < width; ++j)
			{
				if (board[i][j].occupied == true)
					++count;
				else
					break;
			}

			// ���� ��á�ٸ� false, �ݴ��� true�� push�Ѵ�.
			if (count == width)
			{
				lineChecker.push_back(false);
				refreshFlag = true;
			}
			else
				lineChecker.push_back(true);
		}

		// ���� ���� ���� �ϳ��� �ִٸ�, ���带 ���� ��ģ��.
		if (refreshFlag == true)
		{
			// �� ���带 �����Ͽ� ���� ����κ��� ������ �޵�, �� �� ���� ��ŵ�Ѵ�.
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

	//! ���� ������ �����Ѵ�
	Coord entryCoord() const
	{
		return entryPoint;
	}

};