#include "Board.h"

Board::Board()
{
}

void Board::Init(int x, int y)
{
	m_ix = x;
	m_iy = y;
	m_BitMapRect.left = x;
	m_BitMapRect.top = y;
	m_BitMapRect.right = m_BitMapRect.left + 100;
	m_BitMapRect.bottom = m_BitMapRect.top + 100;
}

void Board::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_ix, m_iy);
}

Board::~Board()
{
}
