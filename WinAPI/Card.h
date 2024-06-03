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
	CARD m_eCardState; //ī���� ����
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
	void ChangeRear() { m_eCardState = CARD_REAR; }
	RECT* GetBitMapRect() { return &m_BitMapRect; } //���� ��ȯ
	
	IMAGE GetIndex() { return m_ImageIndex; }
	CARD GetState() { return m_eCardState; }
	~Card();
};

