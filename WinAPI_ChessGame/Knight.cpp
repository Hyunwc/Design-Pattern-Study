#include "Knight.h"

Knight::Knight(int x, int y) : Piece(x, y)
{
	Init(x, y);
}

void Knight::Init(int x, int y)
{
	if (y / 75 == 0)
		m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_BLACK_KNIGHT);
	else
		m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_WHITE_KNIGHT);

	Piece::Init(x, y);
}

void Knight::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}
