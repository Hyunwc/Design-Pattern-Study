#include "King.h"

King::King(int x, int y, IMAGE index) : Piece(x, y, index)
{
	Init(x, y);
}

void King::Init(int x, int y)
{
	Piece::Init(x, y);
}

void King::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}
