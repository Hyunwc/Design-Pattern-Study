#include "Rook.h"

Rook::Rook(int x, int y, IMAGE index) : Piece(x, y, index)
{
	Init(x, y);
}

void Rook::Init(int x, int y)
{
	Piece::Init(x, y);
}

void Rook::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}
