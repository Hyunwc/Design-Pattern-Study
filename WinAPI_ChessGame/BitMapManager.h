#pragma once
#include "BitMap.h"
#include <vector>

enum IMAGE
{
	IMAGE_START,
	IMAGE_BLACK_PAWN = 0,
	IMAGE_BLACK_KNIGHT,
	IMAGE_BLACK_BISHOP,
	IMAGE_BLACK_ROOK,
	IMAGE_BLACK_QUEEN,
	IMAGE_BLACK_KING,
	IMAGE_WHITE_PAWN,
	IMAGE_WHITE_KNIGHT,
	IMAGE_WHITE_BISHOP,
	IMAGE_WHITE_ROOK,
	IMAGE_WHITE_QUEEN,
	IMAGE_WHITE_KING,
	IMAGE_TILE1,
	IMAGE_TILE2,
	IMAGE_MOVETILE,
	IMAGE_END
};

//enum BLACK
//{
//	BLACK_START,
//	BLACK_PAWN = 0,
//	BLACK_KNIGHT,
//	BLACK_BISHOP,
//	BLACK_ROOK,
//	BLACK_QUEEN,
//	BLACK_KING,
//	BLACK_END
//};

class BitMapManager
{
private:
	BitMap* m_parrBitMap;
	static BitMapManager* m_hThis;
	BitMapManager();
public:
	static BitMapManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new BitMapManager;
		return m_hThis;
	}
	static void Release()
	{
		if (m_hThis)
		{
			delete m_hThis;
			m_hThis = nullptr;
		}
	}
	BitMap* GetImage(IMAGE index)
	{
		return &m_parrBitMap[index];
	}

	void Init(HWND hWnd);
	~BitMapManager();
};
