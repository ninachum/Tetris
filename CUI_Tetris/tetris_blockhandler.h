#pragma once

#include <cstdlib>
#include <memory>
#include <utility>
#include "tetris_block.h"

/**
  @brief Block을 생성하여 Board 내에서 움직이도록 하는 클래스 
  @details 
  새 Block을 생성한다. 또한 그 다음에 배치될 Block에 대한 정보를 저장하고 있다.
  그리고, 현재 Block의 Board 내 위치와 진입 지점에 대한 정보를 가지고 있다.
 */
class BlockHandler
{
private:
	void generateRandomBlock()		//!< 랜덤 블럭 생성
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

	void setCoordToEntry()			//!< Block의 위치를 Board 내 진입 지점으로 설정
	{
		currPos = entryCoord;
	}

public:
	Coord currPos;					//!< Block의 Board 내 현재 위치
	std::unique_ptr<Block> blk;		//!< 현재 블럭
	std::unique_ptr<Block> nextBlk; //!< 다음에 배치될 블럭
	Coord entryCoord;				//!< Board 내 초기 진입 위치

	/**
	@brief 블럭 초기 설정
	@details
	Board 내 초기 진입 위치를 저장하고, 현재 Block과 다음에 배치될 Block을 저장한다.
	이후 현재 Block의 위치를 초기 위치로 설정한다.
	@param Coord entry : Board 내 초기 진입 위치
	*/
	BlockHandler(Coord entry)
		: blk(nullptr), nextBlk(nullptr), entryCoord(entry), currPos(entry) 
	{
		generateRandomBlock();		// 현재 블럭을 위해 랜덤 블럭 생성
		setCoordToEntry();			// 현재 블럭의 초기 위치 설정
		blk = std::move(nextBlk);	// 생성한 랜덤 블럭을 현재 블럭에 인계
		generateRandomBlock();		// 다음 블럭을 위한 블럭 생성
	}

	void resetHandler()				//!< 새 블럭 생성과 초기 설정을 위한 함수
	{
		blk = std::move(nextBlk);	
		generateRandomBlock();
		setCoordToEntry();
	}
};
