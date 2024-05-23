#pragma once
#include"BitMap.h"
#include"BitMapManager.h"
enum CARD
{
	CARD_FRONT,
	CARD_REAR,
	CARD_END
};

class Card
{
private:
	CARD m_eCardState; //카드의 상태
	BitMap* m_pBitMap[CARD_END];
	int m_ix;
	int m_iy;
	RECT m_BitMapRect;
	IMAGE m_ImageIndex;
public:
	Card();
	void Init(IMAGE Index, int x, int y);
	void Draw(HDC hdc);
	bool ColliderCheck(POINT point);
	RECT* GetBitMapRect() { return &m_BitMapRect; } //영역 반환
	IMAGE GetIndex() { return m_ImageIndex; }
	CARD GetState() { return m_eCardState; }
	void SetState(bool success); //상태 변경
	
	~Card();
};

