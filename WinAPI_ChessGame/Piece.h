#pragma once
#include "Mecro.h"
#include "BitMap.h"
#include "BitMapManager.h"
enum PIECE_COLOR
{
	PIECE_COLOR_BLACK = 0,
	PIECE_COLOR_WHITE
};

class Piece
{
protected:
	BitMap* m_pBitMap;
	int m_ix;
	int m_iy;
	RECT m_rect;
	IMAGE m_imageIndex;
public:
	Piece(int x, int y, IMAGE index);
	virtual void Init(int x, int y);

	virtual void SetImage(PIECE_COLOR color);
	RECT* GetRect() { return &m_rect; }
	int GetPosX() { return m_ix; }
	int GetPosY() { return m_iy; }
	//virtual void Move() = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual ~Piece() {}
};