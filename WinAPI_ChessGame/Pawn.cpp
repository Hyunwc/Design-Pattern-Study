#include "Pawn.h"

Pawn::Pawn(int x, int y) : Piece(x, y)
{
}

void Pawn::Draw(HDC hdc)
{
	BitMap* pawnImage = BitMapManager::GetInstance()->GetImage(IMAGE_BLACK_PAWN);
	pawnImage->Draw(hdc, m_rect.left, m_rect.top);
}
