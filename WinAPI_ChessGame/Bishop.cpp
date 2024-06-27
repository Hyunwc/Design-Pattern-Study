#include "Bishop.h"

Bishop::Bishop(int x, int y) : Piece(x, y)
{
	Init(x, y);
}

void Bishop::Init(int x, int y)
{
	if (y / 75 == 0)
		m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_BLACK_BISHOP);
	else
		m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_WHITE_BISHOP);

	Piece::Init(x, y);
}

void Bishop::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}
