#pragma once

#include <array>

/**
  @brief Board ���� ��ǥ�� Block ����� ��ǥ ���� ���� ǥ��
  @details Board �������� ��ǥ�� (��, ��) ������ ǥ���Ѵ�. Block ����� ��ǥ ���� ������ (��, ��) ������ ǥ���Ѵ�.
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
  @brief ��� ���� Abstract Base Class.
 */
class Block
{
public:
	//! ������ ȸ�� ���¸� ��Ÿ���� enum type
	enum Mode { UPSIDE, LEFTSIDE, DOWNSIDE, RIGHTSIDE, VERTICAL, HORIZONTAL };	

	//! ������ ���� �� �ִ� ������ ��Ÿ���� enum type
	enum Color																	
	{
		BLACK, BLUE, GREEN, TURQ, RED, PURPLE, YELLOW, WHITE, GRAY,
		PALEBLUE, PALEGREEN, PALETURQ, PALERED, PALEPURPLE, PALEYELLOW, BRIGHTWHITE
	};
	typedef std::array<Coord, 4> BlockShape;			//!< ���� ��� ������ ��ǥ�� �迭�� ��Ÿ��.

	virtual ~Block() {}									//!< ���� �ı���
	virtual void rotate() = 0;							//!< ȸ�� ���¸� ���� ȸ�� ���·� ���� (�� ���� 90�� ȸ��)
	virtual const Color getColor() = 0;					//!< ���� ���� ������ ����
	virtual const BlockShape& getBlockInfo() = 0;		//!< ���� ���� ȸ�� ���¿� ���� ��� ���� ����
	virtual const BlockShape& getNextBlockInfo() = 0;	//!< ȸ���� 1�� �� ���� ����� ��� ���� ����
};

/**
  @brief I ��� ��
 */
class I : public Block
{
private:
	Mode mode;										//!< ȸ�� ����(����, ����)
	static const Color color;						//!< ���� ����
	static const BlockShape blockInfoVertical;		//!< ���η� ȸ���Ǿ����� ����� ��� ����
	static const BlockShape blockInfoHorizontal;	//!< ���η� ȸ���Ǿ����� ����� ��� ����

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
  @brief J ��� ��
 */
class J : public Block
{
private:
	Mode mode;										//!< ȸ�� ����(����, ����)
	static const Color color;						//!< ���� ����
	static const BlockShape blockInfoUpside;		//!< ���� ȸ���Ǿ����� ����� ��� ����
	static const BlockShape blockInfoLeftside;		//!< �������� ȸ���Ǿ����� ����� ��� ����
	static const BlockShape blockInfoDownside;		//!< �Ʒ��� ȸ���Ǿ����� ����� ��� ����
	static const BlockShape blockInfoRightside;		//!< ���������� ȸ���Ǿ����� ����� ��� ����

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
  @brief L ��� ��
 */
class L : public Block
{
private:
	Mode mode;										//!< ȸ�� ����(����, ����)
	static const Color color;						//!< ���� ����
	static const BlockShape blockInfoUpside;		//!< ���� ȸ���Ǿ����� ����� ��� ����
	static const BlockShape blockInfoLeftside;		//!< �������� ȸ���Ǿ����� ����� ��� ����
	static const BlockShape blockInfoDownside;		//!< �Ʒ��� ȸ���Ǿ����� ����� ��� ����
	static const BlockShape blockInfoRightside;		//!< ���������� ȸ���Ǿ����� ����� ��� ����

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
  @brief T ��� ��
 */
class T : public Block
{
private:
	Mode mode;										//!< ȸ�� ����(����, ����)
	static const Color color;						//!< ���� ����
	static const BlockShape blockInfoUpside;		//!< ���� ȸ���Ǿ����� ����� ��� ����
	static const BlockShape blockInfoLeftside;		//!< �������� ȸ���Ǿ����� ����� ��� ����
	static const BlockShape blockInfoDownside;		//!< �Ʒ��� ȸ���Ǿ����� ����� ��� ����
	static const BlockShape blockInfoRightside;		//!< ���������� ȸ���Ǿ����� ����� ��� ����

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
  @brief ��(�׸�) ��� ��
 */
class O : public Block
{
private:
	Mode mode;										//!< ȸ�� ����(����, ����)
	static const Color color;						//!< ���� ����
	static const BlockShape blockInfo;				//!< �� ��� ���� (ȸ�� �Ұ��̹Ƿ� �ϳ��� ����)

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
  @brief S ��� ��
 */
class S : public Block
{
private:
	Mode mode;										//!< ȸ�� ����(����, ����)
	static const Color color;						//!< ���� ����
	static const BlockShape blockInfoVertical;		//!< ���η� ȸ���Ǿ����� ����� ��� ����
	static const BlockShape blockInfoHorizontal;	//!< ���η� ȸ���Ǿ����� ����� ��� ����

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
  @brief Z ��� ��
 */
class Z : public Block
{
private:
	Mode mode;										//!< ȸ�� ����(����, ����)
	static const Color color;						//!< ���� ����
	static const BlockShape blockInfoVertical;		//!< ���η� ȸ���Ǿ����� ����� ��� ����
	static const BlockShape blockInfoHorizontal;	//!< ���η� ȸ���Ǿ����� ����� ��� ����

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


