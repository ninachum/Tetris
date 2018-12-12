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
	enum Color
	{
		BLACK, BLUE, GREEN, TURQ, RED, PURPLE, YELLOW, WHITE, GRAY,
		PALEBLUE, PALEGREEN, PALETURQ, PALERED, PALEPURPLE, PALEYELLOW, BRIGHTWHITE
	};
	virtual ~Block() {}
	virtual void rotate() = 0;
	virtual const Color getColor() = 0;
	virtual const vector<Coord>& getBlockInfo() = 0;
	virtual const vector<Coord>& getNextBlockInfo() = 0;
};

class I : public Block
{
private:
	Mode mode;
	static const Color color;
	static const vector<Coord> blockInfoVertical;
	static const vector<Coord> blockInfoHorizontal;

public:

	I(): mode(VERTICAL) {}
	
	void rotate() override
	{
		mode == VERTICAL ? mode = HORIZONTAL : mode = VERTICAL;
	}

	const Color getColor() override
	{
		return color;
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
const Block::Color I::color = RED;

class J : public Block
{
private:
	Mode mode;
	static const Color color;
	static const vector<Coord> blockInfoUpside;
	static const vector<Coord> blockInfoLeftside;
	static const vector<Coord> blockInfoDownside;
	static const vector<Coord> blockInfoRightside;

public:

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

	const Color getColor() override
	{
		return color;
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
const Block::Color J::color = YELLOW;


class L : public Block
{
private:
	Mode mode;
	static const Color color;
	static const vector<Coord> blockInfoUpside;
	static const vector<Coord> blockInfoLeftside;
	static const vector<Coord> blockInfoDownside;
	static const vector<Coord> blockInfoRightside;

public:

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

	const Color getColor() override
	{
		return color;
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
const Block::Color L::color = PURPLE;


class T : public Block
{
private:
	Mode mode;
	static const Color color;
	static const vector<Coord> blockInfoUpside;
	static const vector<Coord> blockInfoLeftside;
	static const vector<Coord> blockInfoDownside;
	static const vector<Coord> blockInfoRightside;

public:

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

	const Color getColor() override
	{
		return color;
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
const Block::Color T::color = GREEN;


class O : public Block
{
private:
	Mode mode;
	static const Color color;
	static const vector<Coord> blockInfo;

public:

	O() : mode(UPSIDE) {}

	void rotate() override
	{
		return;
	}

	const Color getColor() override
	{
		return color;
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
const Block::Color O::color = BLUE;


class S : public Block
{
private:
	Mode mode;
	static const Color color;
	static const vector<Coord> blockInfoHorizontal;
	static const vector<Coord> blockInfoVertical;

public:

	S() : mode(HORIZONTAL) {}

	void rotate() override
	{
		mode == VERTICAL ? mode = HORIZONTAL : mode = VERTICAL;
	}

	const Color getColor() override
	{
		return color;
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
const Block::Color S::color = TURQ;


class Z : public Block
{
private:
	Mode mode;
	static const Color color;
	static const vector<Coord> blockInfoHorizontal;
	static const vector<Coord> blockInfoVertical;

public:

	Z() : mode(HORIZONTAL) {}

	void rotate() override
	{
		mode == VERTICAL ? mode = HORIZONTAL : mode = VERTICAL;
	}

	const Color getColor() override
	{
		return color;
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
const Block::Color Z::color = GRAY;


