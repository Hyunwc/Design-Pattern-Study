#pragma once
#include "Mecro.h"
#include "BitMap.h"
#include "BitMapManager.h"

class Piece
{
protected:
	BitMap* m_pBitMap;
	int m_ix;
	int m_iy;
	RECT m_rect;
	IMAGE m_imageIndex;
public:
	Piece(int x, int y);
	virtual void Init(int x, int y);
	RECT GetRect() { return m_rect; }
	//virtual void Move() = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual ~Piece() {}
};