#pragma once

#include <cstdlib>
#include <memory>
#include <utility>
#include "tetris_block.h"

/**
  @brief Block�� �����Ͽ� Board ������ �����̵��� �ϴ� Ŭ���� 
  @details 
  �� Block�� �����Ѵ�. ���� �� ������ ��ġ�� Block�� ���� ������ �����ϰ� �ִ�.
  �׸���, ���� Block�� Board �� ��ġ�� ���� ������ ���� ������ ������ �ִ�.
 */
class BlockHandler
{
private:
	void generateRandomBlock()		//!< ���� �� ����
	{
		switch (std::rand() % 7)
		{
		case 0:
			nextBlk = std::make_unique<I>();
			break;
		case 1:
			nextBlk = std::make_unique<J>();
			break;
		case 2:
			nextBlk = std::make_unique<L>();
			break;
		case 3:
			nextBlk = std::make_unique<T>();
			break;
		case 4:
			nextBlk = std::make_unique<O>();
			break;
		case 5:
			nextBlk = std::make_unique<S>();
			break;
		case 6:
			nextBlk = std::make_unique<Z>();
			break;
		}
	}

	void setCoordToEntry()			//!< Block�� ��ġ�� Board �� ���� �������� ����
	{
		currPos = entryCoord;
	}

public:
	Coord currPos;					//!< Block�� Board �� ���� ��ġ
	std::unique_ptr<Block> blk;		//!< ���� ��
	std::unique_ptr<Block> nextBlk; //!< ������ ��ġ�� ��
	Coord entryCoord;				//!< Board �� �ʱ� ���� ��ġ

	/**
	@brief �� �ʱ� ����
	@details
	Board �� �ʱ� ���� ��ġ�� �����ϰ�, ���� Block�� ������ ��ġ�� Block�� �����Ѵ�.
	���� ���� Block�� ��ġ�� �ʱ� ��ġ�� �����Ѵ�.
	@param Coord entry : Board �� �ʱ� ���� ��ġ
	*/
	BlockHandler(Coord entry)
		: blk(nullptr), nextBlk(nullptr), entryCoord(entry), currPos(entry) 
	{
		generateRandomBlock();		// ���� ���� ���� ���� �� ����
		setCoordToEntry();			// ���� ���� �ʱ� ��ġ ����
		blk = std::move(nextBlk);	// ������ ���� ���� ���� ���� �ΰ�
		generateRandomBlock();		// ���� ���� ���� �� ����
	}

	void resetHandler()				//!< �� �� ������ �ʱ� ������ ���� �Լ�
	{
		blk = std::move(nextBlk);	
		generateRandomBlock();
		setCoordToEntry();
	}
};
