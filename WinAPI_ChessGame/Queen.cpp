#include "Queen.h"

Queen::Queen(int x, int y, IMAGE index) : Piece(x, y, index)
{
	Init(x, y);
}

void Queen::Init(int x, int y)
{

	Piece::Init(x, y);
}

void Queen::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}
