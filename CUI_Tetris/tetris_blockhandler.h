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
			blk = std::make_unique<I>();
			break;
		case 1:
			blk = std::make_unique<J>();
			break;
		case 2:
			blk = std::make_unique<L>();
			break;
		case 3:
			blk = std::make_unique<T>();
			break;
		case 4:
			blk = std::make_unique<O>();
			break;
		case 5:
			blk = std::make_unique<S>();
			break;
		case 6:
			blk = std::make_unique<Z>();
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
	Coord entryCoord;

	BlockHandler(Coord entry) : blk(nullptr), entryCoord(entry), currPos(entry) 
	{
		resetHandler(); 
	}

	void transferBlockFrom(BlockHandler & other)
	{
		blk = std::move(other.blk);
		setCoordToEntry();
	}

	void resetHandler()
	{
		generateRandomBlock();
		setCoordToEntry();
	}
};
