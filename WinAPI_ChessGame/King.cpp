#include "King.h"

King::King(int x, int y) : Piece(x, y)
{
	Init(x, y);
}

void King::Init(int x, int y)
{
	if (y / 75 == 0)
		m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_BLACK_KING);
	else
		m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_WHITE_KING);

	Piece::Init(x, y);
}

void King::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}
