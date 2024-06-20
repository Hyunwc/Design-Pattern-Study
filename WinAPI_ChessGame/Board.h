#pragma once
#include "BitMap.h"
#include "BitMapManager.h"

class Board
{
private:
	int m_ix;
	int m_iy;
	RECT m_BitMapRect;
	BitMap* m_pBitMap;
public:
	Board();
	void Init(int x, int y);
	void Draw(HDC hdc);
	~Board();
};
