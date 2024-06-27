#include "Queen.h"

Queen::Queen(int x, int y) : Piece(x, y)
{
	Init(x, y);
}

void Queen::Init(int x, int y)
{
	if (y / 75 == 0)
		m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_BLACK_QUEEN);
	else
		m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_WHITE_QUEEN);

	Piece::Init(x, y);
}

void Queen::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}
