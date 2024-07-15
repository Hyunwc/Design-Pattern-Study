#pragma once
#include "Mecro.h"
#include "BitMap.h"
#include "BitMapManager.h"
//#include "GameManager.h"



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
	PIECE_COLOR m_color;
	//vector<RECT> m_route;
public:
	Piece(int x, int y, IMAGE index, PIECE_COLOR color);
	virtual void Init(int x, int y);

	RECT* GetRect() { return &m_rect; }
	Position GetPos() { return m_pos; }
	PIECE_COLOR GetColor() { return m_color; }
	int GetPosX() { return m_ix; }
	int GetPosY() { return m_iy; }
	//vector<RECT> GetRoute() { return m_route; }
	virtual vector<RECT> RouteNav() = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void RouteDraw(HDC hdc){}
	virtual bool IsMoveable(RECT rect);
	virtual bool IsEnemy(RECT rect) { return false; }
	virtual ~Piece() {}
};