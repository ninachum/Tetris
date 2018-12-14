#pragma once

#include <array>

/**
  @brief Board 내의 좌표와 Block 모양의 좌표 형식 정보 표현
  @details Board 내에서의 좌표를 (열, 행) 순서로 표현한다. Block 모양의 좌표 형식 정보를 (열, 행) 순서로 표현한다.
 */
struct Coord
{
	int x;
	int y;
	Coord() = delete;
	Coord(int xpos, int ypos) : x(xpos), y(ypos) {}
	Coord operator+(const Coord & operand) const
	{
		return Coord(x + operand.x, y + operand.y);
	}
};

/**
  @brief 모든 블럭의 Abstract Base Class.
 */
class Block
{
public:
	//! 블럭들의 회전 상태를 나타내는 enum type
	enum Mode { UPSIDE, LEFTSIDE, DOWNSIDE, RIGHTSIDE, VERTICAL, HORIZONTAL };	

	//! 블럭들이 가질 수 있는 색상을 나타내는 enum type
	enum Color																	
	{
		BLACK, BLUE, GREEN, TURQ, RED, PURPLE, YELLOW, WHITE, GRAY,
		PALEBLUE, PALEGREEN, PALETURQ, PALERED, PALEPURPLE, PALEYELLOW, BRIGHTWHITE
	};
	typedef std::array<Coord, 4> BlockShape;			//!< 블럭의 모양 정보를 좌표의 배열로 나타냄.

	virtual ~Block() {}									//!< 가상 파괴자
	virtual void rotate() = 0;							//!< 회전 상태를 다음 회전 상태로 변경 (한 번에 90도 회전)
	virtual const Color getColor() = 0;					//!< 블럭의 색상 정보를 리턴
	virtual const BlockShape& getBlockInfo() = 0;		//!< 블럭의 현재 회전 상태에 따른 모양 정보 리턴
	virtual const BlockShape& getNextBlockInfo() = 0;	//!< 회전을 1번 더 했을 경우의 모양 정보 리턴
};

/**
  @brief I 모양 블럭
 */
class I : public Block
{
private:
	Mode mode;										//!< 회전 상태(가로, 세로)
	static const Color color;						//!< 블럭의 색상
	static const BlockShape blockInfoVertical;		//!< 세로로 회전되어있을 경우의 모양 정보
	static const BlockShape blockInfoHorizontal;	//!< 가로로 회전되어있을 경우의 모양 정보

public:

	I(): mode(HORIZONTAL) {}
	
	void rotate() override
	{
		mode == VERTICAL ? mode = HORIZONTAL : mode = VERTICAL;
	}

	const Color getColor() override
	{
		return color;
	}

	const BlockShape& getBlockInfo() override
	{
		switch (mode)
		{
		case VERTICAL:
			return blockInfoVertical;
		case HORIZONTAL:
			return blockInfoHorizontal;
		}
	}

	const BlockShape& getNextBlockInfo() override
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
const Block::BlockShape I::blockInfoVertical { {{0, 0}, {0, 1 }, {0, 2 }, {0, 3}} };
const Block::BlockShape I::blockInfoHorizontal{ {{-1, 0}, {0, 0}, {1, 0}, {2, 0}} };
const Block::Color I::color = RED;

/**
  @brief J 모양 블럭
 */
class J : public Block
{
private:
	Mode mode;										//!< 회전 상태(가로, 세로)
	static const Color color;						//!< 블럭의 색상
	static const BlockShape blockInfoUpside;		//!< 위로 회전되어있을 경우의 모양 정보
	static const BlockShape blockInfoLeftside;		//!< 왼쪽으로 회전되어있을 경우의 모양 정보
	static const BlockShape blockInfoDownside;		//!< 아래로 회전되어있을 경우의 모양 정보
	static const BlockShape blockInfoRightside;		//!< 오른쪽으로 회전되어있을 경우의 모양 정보

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

	const BlockShape& getBlockInfo() override
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

	const BlockShape& getNextBlockInfo() override
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

const Block::BlockShape J::blockInfoUpside { {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}} };
const Block::BlockShape J::blockInfoLeftside { {{1, -1}, {1, 0}, {1, 1}, {0, 1}} };
const Block::BlockShape J::blockInfoDownside { {{-1, -1}, {0, -1}, {1, 0}, {1, -1}} };
const Block::BlockShape J::blockInfoRightside { {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}} };
const Block::Color J::color = YELLOW;

/**
  @brief L 모양 블럭
 */
class L : public Block
{
private:
	Mode mode;										//!< 회전 상태(가로, 세로)
	static const Color color;						//!< 블럭의 색상
	static const BlockShape blockInfoUpside;		//!< 위로 회전되어있을 경우의 모양 정보
	static const BlockShape blockInfoLeftside;		//!< 왼쪽으로 회전되어있을 경우의 모양 정보
	static const BlockShape blockInfoDownside;		//!< 아래로 회전되어있을 경우의 모양 정보
	static const BlockShape blockInfoRightside;		//!< 오른쪽으로 회전되어있을 경우의 모양 정보

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

	const BlockShape& getBlockInfo() override
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

	const BlockShape& getNextBlockInfo() override
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

const Block::BlockShape L::blockInfoUpside { {{-1, 1}, {0, 1}, {1, 0}, {1, 1}} };
const Block::BlockShape L::blockInfoLeftside { {{0, -1}, {1, -1}, {1, 0}, {1, 1}} };
const Block::BlockShape L::blockInfoDownside { {{-1, -1}, {-1, 0}, {0, -1}, {1, -1}} };
const Block::BlockShape L::blockInfoRightside { {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}} };
const Block::Color L::color = PURPLE;

/**
  @brief T 모양 블럭
 */
class T : public Block
{
private:
	Mode mode;										//!< 회전 상태(가로, 세로)
	static const Color color;						//!< 블럭의 색상
	static const BlockShape blockInfoUpside;		//!< 위로 회전되어있을 경우의 모양 정보
	static const BlockShape blockInfoLeftside;		//!< 왼쪽으로 회전되어있을 경우의 모양 정보
	static const BlockShape blockInfoDownside;		//!< 아래로 회전되어있을 경우의 모양 정보
	static const BlockShape blockInfoRightside;		//!< 오른쪽으로 회전되어있을 경우의 모양 정보

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

	const BlockShape& getBlockInfo() override
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

	const BlockShape& getNextBlockInfo() override
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

const Block::BlockShape T::blockInfoUpside { {{-1, 1}, {0, 0}, {0, 1}, {1, 1}} };	// modified for drawNextBlock()
const Block::BlockShape T::blockInfoLeftside { {{-1, 1}, {0, 0}, {0, 1}, {0, 2}} };
const Block::BlockShape T::blockInfoDownside { {{-1, 1}, {0, 1}, {0, 2}, {1, 1}} };
const Block::BlockShape T::blockInfoRightside { {{0, 0}, {0, 1}, {0, 2}, {1, 1}} };
const Block::Color T::color = GREEN;

/**
  @brief ㅁ(네모) 모양 블럭
 */
class O : public Block
{
private:
	Mode mode;										//!< 회전 상태(가로, 세로)
	static const Color color;						//!< 블럭의 색상
	static const BlockShape blockInfo;				//!< 블럭 모양 정보 (회전 불가이므로 하나만 존재)

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

	const BlockShape& getBlockInfo() override
	{
		return blockInfo;
	}

	const BlockShape& getNextBlockInfo() override
	{
		return blockInfo;
	}
};

const Block::BlockShape O::blockInfo { {{0, 0}, {0, 1}, {1, 0}, {1, 1}} };
const Block::Color O::color = BLUE;

/**
  @brief S 모양 블럭
 */
class S : public Block
{
private:
	Mode mode;										//!< 회전 상태(가로, 세로)
	static const Color color;						//!< 블럭의 색상
	static const BlockShape blockInfoVertical;		//!< 세로로 회전되어있을 경우의 모양 정보
	static const BlockShape blockInfoHorizontal;	//!< 가로로 회전되어있을 경우의 모양 정보

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

	const BlockShape& getBlockInfo() override
	{
		switch (mode)
		{
		case VERTICAL:
			return blockInfoVertical;
		case HORIZONTAL:
			return blockInfoHorizontal;
		}
	}

	const BlockShape& getNextBlockInfo() override
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

const Block::BlockShape S::blockInfoHorizontal { {{-1, 1}, {0, 1}, {0, 0}, {1, 0}} };
const Block::BlockShape S::blockInfoVertical { {{0, -1}, {0, 0}, {1, 0}, {1, 1}} };
const Block::Color S::color = TURQ;

/**
  @brief Z 모양 블럭
 */
class Z : public Block
{
private:
	Mode mode;										//!< 회전 상태(가로, 세로)
	static const Color color;						//!< 블럭의 색상
	static const BlockShape blockInfoVertical;		//!< 세로로 회전되어있을 경우의 모양 정보
	static const BlockShape blockInfoHorizontal;	//!< 가로로 회전되어있을 경우의 모양 정보

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

	const BlockShape& getBlockInfo() override
	{
		switch (mode)
		{
		case VERTICAL:
			return blockInfoVertical;
		case HORIZONTAL:
			return blockInfoHorizontal;
		}
	}

	const BlockShape& getNextBlockInfo() override
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

const Block::BlockShape Z::blockInfoHorizontal { {{-1, 0}, {0, 0}, {0, 1}, {1, 1}} };	// modified for drawNextBlock()
const Block::BlockShape Z::blockInfoVertical { {{-1, 1}, {-1, 0}, {0, 0}, {0, -1}} };
const Block::Color Z::color = GRAY;


