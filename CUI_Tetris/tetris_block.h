#pragma once

#include <vector>

using std::vector;


struct Coord
{
	int x;
	int y;
	Coord(int xpos, int ypos) : x(xpos), y(ypos) {}
	Coord operator+(const Coord & operand) const
	{
		return Coord(x + operand.x, y + operand.y);
	}
};

class Block
{
public:
	enum Mode { UPSIDE, LEFTSIDE, DOWNSIDE, RIGHTSIDE, VERTICAL, HORIZONTAL };
	virtual ~Block() {}
	virtual void rotate() = 0;
	virtual const Mode getMode() = 0;
	virtual const vector<Coord>& getBlockInfo() = 0;
	virtual const vector<Coord>& getNextBlockInfo() = 0;
};

class I : public Block
{
private:
	static const vector<Coord> blockInfoVertical;
	static const vector<Coord> blockInfoHorizontal;

public:
	Mode mode;

	I(): mode(VERTICAL) {}
	
	void rotate() override
	{
		mode == VERTICAL ? mode = HORIZONTAL : mode = VERTICAL;
	}

	const Mode getMode() override
	{
		return mode;
	}

	const vector<Coord>& getBlockInfo() override
	{
		switch (mode)
		{
		case VERTICAL:
			return blockInfoVertical;
		case HORIZONTAL:
			return blockInfoHorizontal;
		}
	}

	const vector<Coord>& getNextBlockInfo() override
	{
		switch (mode)
		{
		case VERTICAL:
			return blockInfoHorizontal;
		case HORIZONTAL:
			return blockInfoVertical;
		}
	}

};
const vector<Coord> I::blockInfoVertical = { { 0,0 }, { 0,1 }, { 0,2 }, { 0,3 } };
const vector<Coord> I::blockInfoHorizontal = { {-1, 0}, {0, 0}, {1, 0}, {2, 0} };


class J : public Block
{
private:
	static const vector<Coord> blockInfoUpside;
	static const vector<Coord> blockInfoLeftside;
	static const vector<Coord> blockInfoDownside;
	static const vector<Coord> blockInfoRightside;

public:
	Mode mode;

	J() : mode(UPSIDE) {}

	void rotate() override
	{
		switch (mode)
		{
		case UPSIDE:
			mode = LEFTSIDE;
			break;
		case LEFTSIDE:
			mode = DOWNSIDE;
			break;
		case DOWNSIDE:
			mode = RIGHTSIDE;
			break;
		case RIGHTSIDE:
			mode = UPSIDE;
			break;
		}
	}

	const Mode getMode() override
	{
		return mode;
	}

	const vector<Coord>& getBlockInfo() override
	{
		switch (mode)
		{
		case UPSIDE:
			return blockInfoUpside;
		case LEFTSIDE:
			return blockInfoLeftside;
		case DOWNSIDE:
			return blockInfoDownside;
		case RIGHTSIDE:
			return blockInfoRightside;
		}
	}

	const vector<Coord>& getNextBlockInfo() override
	{
		switch (mode)
		{
		case UPSIDE:
			return blockInfoLeftside;
		case LEFTSIDE:
			return blockInfoDownside;
		case DOWNSIDE:
			return blockInfoRightside;
		case RIGHTSIDE:
			return blockInfoUpside;
		}
	}
};

const vector<Coord> J::blockInfoUpside = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1} };
const vector<Coord> J::blockInfoLeftside = { {1, -1}, {1, 0}, {1, 1}, {0, 1} };
const vector<Coord> J::blockInfoDownside = { {-1, -1}, {0, -1}, {1, 0}, {1, -1} };
const vector<Coord> J::blockInfoRightside = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1} };


class L : public Block
{
private:
	static const vector<Coord> blockInfoUpside;
	static const vector<Coord> blockInfoLeftside;
	static const vector<Coord> blockInfoDownside;
	static const vector<Coord> blockInfoRightside;

public:
	Mode mode;

	L() : mode(UPSIDE) {}

	void rotate() override
	{
		switch (mode)
		{
		case UPSIDE:
			mode = LEFTSIDE;
			break;
		case LEFTSIDE:
			mode = DOWNSIDE;
			break;
		case DOWNSIDE:
			mode = RIGHTSIDE;
			break;
		case RIGHTSIDE:
			mode = UPSIDE;
			break;
		}
	}

	const Mode getMode() override
	{
		return mode;
	}

	const vector<Coord>& getBlockInfo() override
	{
		switch (mode)
		{
		case UPSIDE:
			return blockInfoUpside;
		case LEFTSIDE:
			return blockInfoLeftside;
		case DOWNSIDE:
			return blockInfoDownside;
		case RIGHTSIDE:
			return blockInfoRightside;
		}
	}

	const vector<Coord>& getNextBlockInfo() override
	{
		switch (mode)
		{
		case UPSIDE:
			return blockInfoLeftside;
		case LEFTSIDE:
			return blockInfoDownside;
		case DOWNSIDE:
			return blockInfoRightside;
		case RIGHTSIDE:
			return blockInfoUpside;
		}
	}
};

const vector<Coord> L::blockInfoUpside = { {-1, 1}, {0, 1}, {1, 0}, {1, 1} };
const vector<Coord> L::blockInfoLeftside = { {0, -1}, {1, -1}, {1, 0}, {1, 1} };
const vector<Coord> L::blockInfoDownside = { {-1, -1}, {-1, 0}, {0, -1}, {1, -1} };
const vector<Coord> L::blockInfoRightside = { {-1, -1}, {-1, 0}, {-1, 1}, {0, 1} };


class T : public Block
{
private:
	static const vector<Coord> blockInfoUpside;
	static const vector<Coord> blockInfoLeftside;
	static const vector<Coord> blockInfoDownside;
	static const vector<Coord> blockInfoRightside;

public:
	Mode mode;

	T() : mode(UPSIDE) {}

	void rotate() override
	{
		switch (mode)
		{
		case UPSIDE:
			mode = LEFTSIDE;
			break;
		case LEFTSIDE:
			mode = DOWNSIDE;
			break;
		case DOWNSIDE:
			mode = RIGHTSIDE;
			break;
		case RIGHTSIDE:
			mode = UPSIDE;
			break;
		}
	}

	const Mode getMode() override
	{
		return mode;
	}

	const vector<Coord>& getBlockInfo() override
	{
		switch (mode)
		{
		case UPSIDE:
			return blockInfoUpside;
		case LEFTSIDE:
			return blockInfoLeftside;
		case DOWNSIDE:
			return blockInfoDownside;
		case RIGHTSIDE:
			return blockInfoRightside;
		}
	}

	const vector<Coord>& getNextBlockInfo() override
	{
		switch (mode)
		{
		case UPSIDE:
			return blockInfoLeftside;
		case LEFTSIDE:
			return blockInfoDownside;
		case DOWNSIDE:
			return blockInfoRightside;
		case RIGHTSIDE:
			return blockInfoUpside;
		}
	}
};

const vector<Coord> T::blockInfoUpside = { {-1, 0}, {0, -1}, {0, 0}, {1, 0} };
const vector<Coord> T::blockInfoLeftside = { {-1, 0}, {0, -1}, {0, 0}, {0, 1} };
const vector<Coord> T::blockInfoDownside = { {-1, 0}, {0, 0}, {0, 1}, {1, 0} };
const vector<Coord> T::blockInfoRightside = { {0, -1}, {0, 0}, {0, 1}, {1, 0} };


class O : public Block
{
private:
	static const vector<Coord> blockInfo;

public:
	Mode mode;

	O() : mode(UPSIDE) {}

	void rotate() override
	{
		return;
	}

	const Mode getMode() override
	{
		return mode;
	}

	const vector<Coord>& getBlockInfo() override
	{
		return blockInfo;
	}

	const vector<Coord>& getNextBlockInfo() override
	{
		return blockInfo;
	}
};

const vector<Coord> O::blockInfo = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };


class S : public Block
{
private:
	static const vector<Coord> blockInfoHorizontal;
	static const vector<Coord> blockInfoVertical;

public:
	Mode mode;

	S() : mode(VERTICAL) {}

	void rotate() override
	{
		mode == VERTICAL ? mode = HORIZONTAL : mode = VERTICAL;
	}

	const Mode getMode() override
	{
		return mode;
	}

	const vector<Coord>& getBlockInfo() override
	{
		switch (mode)
		{
		case VERTICAL:
			return blockInfoVertical;
		case HORIZONTAL:
			return blockInfoHorizontal;
		}
	}

	const vector<Coord>& getNextBlockInfo() override
	{
		switch (mode)
		{
		case VERTICAL:
			return blockInfoHorizontal;
		case HORIZONTAL:
			return blockInfoVertical;
		}
	}
};

const vector<Coord> S::blockInfoHorizontal = { {-1, 0}, {0, 0}, {0, -1}, {1, -1} };
const vector<Coord> S::blockInfoVertical = { {0, -1}, {0, 0}, {1, 0}, {1, 1} };


class Z : public Block
{
private:
	static const vector<Coord> blockInfoHorizontal;
	static const vector<Coord> blockInfoVertical;

public:
	Mode mode;

	Z() : mode(VERTICAL) {}

	void rotate() override
	{
		mode == VERTICAL ? mode = HORIZONTAL : mode = VERTICAL;
	}

	const Mode getMode() override
	{
		return mode;
	}

	const vector<Coord>& getBlockInfo() override
	{
		switch (mode)
		{
		case VERTICAL:
			return blockInfoVertical;
		case HORIZONTAL:
			return blockInfoHorizontal;
		}
	}

	const vector<Coord>& getNextBlockInfo() override
	{
		switch (mode)
		{
		case VERTICAL:
			return blockInfoHorizontal;
		case HORIZONTAL:
			return blockInfoVertical;
		}
	}
};

const vector<Coord> Z::blockInfoHorizontal = { {-1, 0}, {0, 0}, {0, 1}, {1, 1} };
const vector<Coord> Z::blockInfoVertical = { {-1, 1}, {-1, 0}, {0, 0}, {0, -1} };


