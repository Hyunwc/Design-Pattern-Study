#pragma once
#include "BitMap.h"
#include <vector>



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
	BitMap* m_tile;
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
	BitMap* GetTestTile()
	{
		return m_tile;
	}

	void Init(HDC hdc);
	~BitMapManager();
};
