#include "Rook.h"

Rook::Rook(int x, int y, IMAGE index, PIECE_COLOR color) : Piece(x, y, index, color)
{
	Init(x, y);
}

void Rook::Init(int x, int y)
{
	Piece::Init(x, y);
}

void Rook::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}

void Rook::RouteNav()
{
	m_route.clear();
	//수직
	for (int i = 0; i < 8; i++)
	{
		if (i != m_iy)
		{
			RECT route = { m_ix * 75, i * 75, (m_ix + 1) * 75, (i + 1) * 75 };
			m_route.push_back(route);
		}
	}
	//수평
	for (int i = 0; i < 8; i++)
	{
		if (i != m_ix)
		{
			RECT route = { i * 75, m_iy * 75, (i + 1) * 75, (m_iy + 1) * 75 };
			m_route.push_back(route);
		}
	}
	
}

void Rook::RouteDraw(HDC hdc)
{
	for (RECT r : m_route)
	{
		m_rBitMap->TestDraw(hdc, r.left, r.top);
	}
}
