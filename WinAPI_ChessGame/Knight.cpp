#include "Knight.h"

Knight::Knight(int x, int y, IMAGE index) : Piece(x, y, index)
{
	Init(x, y);
}

void Knight::Init(int x, int y)
{

	Piece::Init(x, y);
}

void Knight::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}
