#pragma once

#include <cstdlib>
#include <memory>
#include <utility>
#include "tetris_block.h"

class BlockHandler
{
private:
	void generateRandomBlock()
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

	void setCoordToEntry()
	{
		currPos = entryCoord;
	}

public:
	Coord currPos;
	std::unique_ptr<Block> blk;
	std::unique_ptr<Block> nextBlk;
	Coord entryCoord;

	BlockHandler(Coord entry) : blk(nullptr), nextBlk(nullptr), entryCoord(entry), currPos(entry) 
	{
		//resetHandler();
		generateRandomBlock();
		setCoordToEntry();
		blk = std::move(nextBlk);
		generateRandomBlock();
	}

	void resetHandler()
	{
		blk = std::move(nextBlk);
		generateRandomBlock();
		setCoordToEntry();
	}
};
