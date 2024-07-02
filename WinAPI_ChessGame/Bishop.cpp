#include "Bishop.h"

Bishop::Bishop(int x, int y, IMAGE index) : Piece(x, y, index)
{
	Init(x, y);
}

void Bishop::Init(int x, int y)
{

	Piece::Init(x, y);
}

void Bishop::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}
