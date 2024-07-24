#include "Piece.h"

Piece::Piece(int x, int y, IMAGE index, PIECE_COLOR color) : m_ix(x), m_iy(y), m_color(color)
{
	m_pBitMap = BitMapManager::GetInstance()->GetImage(index);
	m_rBitMap = BitMapManager::GetInstance()->GetTestTile();
	m_imageIndex = index;
	Init(x, y);
}

void Piece::Init(int x, int y)
{
	//인덱스는 상속받은 클래스에서 설정
	//영역은 여기있는 것들 그대로 사용할 것.
	m_ix = x;
	m_iy = y;
	m_rect.left = x * 75;
	m_rect.top = y * 75;
	m_rect.right = m_rect.left + 75;
	m_rect.bottom = m_rect.top + 75;
}

bool Piece::IsMoveable(RECT rect)
{
	return false;
}

