#include "Bishop.h"

Bishop::Bishop(int x, int y, IMAGE index, PIECE_COLOR color) : Piece(x, y, index, color)
{
	Init(x, y);
}

void Bishop::Init(int x, int y)
{

	Piece::Init(x, y);
}

void Bishop::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}

void Bishop::RouteNav()
{
	m_route.clear();
	
	int moves[4][2] = {
		{ -1, -1}, { -1, 1}, {1, -1}, {1, 1} 
	};

	for (int i = 0; i < 4; i++)
	{
		//현재 위치로 초기화
		int newX = m_ix;
		int newY = m_iy;

		while (true)
		{
			newX += moves[i][1];
			newY += moves[i][0];

			if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
			{
				RECT route = { newX * 75, newY * 75, (newX + 1) * 75, (newY + 1) * 75 };
				m_route.push_back(route);
			}
			else
			{
				break;
			}
		}
	}
}

void Bishop::RouteDraw(HDC hdc)
{

	for (RECT r : m_route)
	{
		m_rBitMap->TestDraw(hdc, r.left, r.top);
	}
}
