#include "Piece.h"

Piece::Piece(int x, int y, IMAGE index, PIECE_COLOR color) : m_ix(x), m_iy(y), m_color(color)
{
	m_pBitMap = BitMapManager::GetInstance()->GetImage(index);
	m_rBitMap = BitMapManager::GetInstance()->GetTestTile();
	Init(x, y);
}

void Piece::Init(int x, int y)
{
	//�ε����� ��ӹ��� Ŭ�������� ����
	//������ �����ִ� �͵� �״�� ����� ��.
	//m_imageIndex = Index;
	//m_pBitMap = BitMapManager::GetInstance()->GetImage(Index);
	
	m_ix = x;
	m_iy = y;
	//m_pos.m_ix = x;
	//m_pos.m_iy = y;
	m_rect.left = x * 75;
	m_rect.top = y * 75;
	m_rect.right = m_rect.left + 75;
	m_rect.bottom = m_rect.top + 75;
	//m_rect.right = m_rect.left + m_pBitMap->GetSize().cx;
	//m_rect.bottom = m_rect.top + m_pBitMap->GetSize().cy;
}

bool Piece::IsMoveable(RECT rect)
{
	return false;
}


//void Pawn::Init(int x, int y)
//{
//	m_pBitMap = BitMapManager::GetInstance()->GetImage(Index);
//	Piece::Init(x, y);
//}