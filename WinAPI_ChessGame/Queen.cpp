#include "Queen.h"

Queen::Queen(int x, int y, IMAGE index, PIECE_COLOR color) : Piece(x, y, index, color)
{
	Init(x, y);
}

void Queen::Init(int x, int y)
{
	Piece::Init(x, y);
}

void Queen::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}

vector<RECT> Queen::RouteNav()
{
	vector<RECT> m_route;

	int moves[4][2] = {
		{ -1, -1}, { -1, 1}, {1, -1}, {1, 1}
	};

	for (int i = m_iy - 1; i >= 0; i--)
	{
		RECT route = { m_ix * 75, i * 75, (m_ix + 1) * 75, (i + 1) * 75 };
		if (!IsMoveable(route)) break;
		m_route.push_back(route);
	}
	for (int i = m_iy + 1; i < 8; i++)
	{
		RECT route = { m_ix * 75, i * 75, (m_ix + 1) * 75, (i + 1) * 75 };
		if (!IsMoveable(route)) break;
		m_route.push_back(route);
	}
	//수평
	for (int i = m_ix - 1; i >= 0; i--)
	{
		RECT route = { i * 75, m_iy * 75, (i + 1) * 75, (m_iy + 1) * 75 };
		if (!IsMoveable(route)) break;
		m_route.push_back(route);
	}
	for (int i = m_ix + 1; i < 8; i++)
	{
		RECT route = { i * 75, m_iy * 75, (i + 1) * 75, (m_iy + 1) * 75 };
		if (!IsMoveable(route)) break;
		m_route.push_back(route);
	}

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
				if (IsMoveable(route))
					m_route.push_back(route);
				else
					break;
			}
			else
			{
				break;
			}
		}
	}

	return m_route;
}

void Queen::RouteDraw(HDC hdc)
{
	for (RECT r : RouteNav())
	{
		m_rBitMap->TestDraw(hdc, r.left, r.top);
	}
}

bool Queen::IsMoveable(RECT rect)
{
	PIECE_COLOR color = GameManager::Instance()->GetPieceColor(rect);
	return (color == PIECE_COLOR_NONE || color != m_color);
}
