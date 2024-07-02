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
	BitMap* m_rBitMap;
	Position m_pos;
	int m_ix;
	int m_iy;
	RECT m_rect;
	IMAGE m_imageIndex;
	vector<RECT> m_route;
public:
	Piece(int x, int y, IMAGE index);
	virtual void Init(int x, int y);

	RECT* GetRect() { return &m_rect; }
	Position GetPos() { return m_pos; }
	int GetPosX() { return m_ix; }
	int GetPosY() { return m_iy; }
	vector<RECT> GetRoute() { return m_route; }
	virtual bool RouteNav(){}
	//virtual void Move() = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void RouteDraw(HDC hdc){}
	virtual ~Piece() {}
};