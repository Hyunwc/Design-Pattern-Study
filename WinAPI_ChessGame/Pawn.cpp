#include "Pawn.h"

Pawn::Pawn(int x, int y) : Piece(x, y)
{
	Init(x, y);
}

void Pawn::Init(int x, int y)
{
	//2�࿡���� ��������
	//7�࿡���� ȭ��Ʈ������
	if( y / 75 == 1)
		m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_BLACK_PAWN);
	else
		m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_WHITE_PAWN);
	
	//���� ����.
	Piece::Init(x, y);
}

void Pawn::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}
