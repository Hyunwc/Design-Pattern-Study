#pragma once
#include "Mecro.h"
#include "BitMap.h"
#include "BitMapManager.h"
//#include "GameManager.h"



class Piece
{
protected:
	BitMap* m_pBitMap;
	BitMap* m_rBitMap; //∑Á∆Æ
	int m_ix;
	int m_iy;
	RECT m_rect;
	IMAGE m_imageIndex;
	PIECE_COLOR m_color;
public:
	Piece(int x, int y, IMAGE index, PIECE_COLOR color);
	virtual void Init(int x, int y);

	RECT* GetRect() { return &m_rect; }
	PIECE_COLOR GetColor() { return m_color; }
	IMAGE GetImage() { return m_imageIndex; }
	int GetPosX() { return m_ix; }
	int GetPosY() { return m_iy; }
	virtual vector<RECT> RouteNav() = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void RouteDraw(HDC hdc){}
	virtual bool GetFirstMove() { return false; }
	virtual void SetFirstMove() { }
	virtual bool IsMoveable(RECT rect);
	virtual bool IsEnemy(RECT rect) { return false; }
	virtual ~Piece() {}
};