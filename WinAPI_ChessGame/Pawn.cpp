#include "Pawn.h"

Pawn::Pawn(int x, int y, IMAGE index) : Piece(x, y, index)
{
	firstMove = false;
	Init(x, y);
}

void Pawn::Init(int x, int y)
{
	Piece::Init(x, y);
}

void Pawn::SetImage(PIECE_COLOR color)
{
	if(color == PIECE_COLOR_BLACK)
		m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_BLACK_PAWN);
	else
		m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_WHITE_PAWN);
}

void Pawn::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}


