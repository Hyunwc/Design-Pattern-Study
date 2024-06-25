#pragma once
#include "Mecro.h"
#include "BitMap.h"
#include "BitMapManager.h"

class Piece
{
protected:
	RECT m_rect; //말들의 영역
	int m_x;
	int m_y;
public:
	Piece(int x, int y);
	void SetPosition(int x, int y);
	RECT GetRect() { return m_rect; }
	virtual void Draw(HDC hdc) = 0;
	virtual ~Piece(){}
};
