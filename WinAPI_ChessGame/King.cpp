#include "King.h"

King::King(int x, int y, IMAGE index, PIECE_COLOR color) : Piece(x, y, index, color)
{
	Init(x, y);
}

void King::Init(int x, int y)
{
	Piece::Init(x, y);
}

void King::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}

vector<RECT> King::RouteNav()
{
	vector<RECT> m_route;

	int moves[8][2] = {
		{ -1, -1 }, { -1, 0}, {-1, 1}, {0, -1},
		{ 0, 1}, {1, - 1}, {1, 0}, {1, 1}
	};

	for (int i = 0; i < 8; i++)
	{
		//���� ��ġ���� ���ϰ� ������ ����Ͽ� ����
		int newX = m_ix + moves[i][1];
		int newY = m_iy + moves[i][0];

		//������ ������ ����� �ʰ� �ϱ� ���� ����
		if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
		{
			RECT route = { newX * 75, newY * 75, (newX + 1) * 75, (newY + 1) * 75 };
			m_route.push_back(route);
		}
	}

	return m_route;
}

void King::RouteDraw(HDC hdc)
{
	for (RECT r : RouteNav())
	{
		m_rBitMap->TestDraw(hdc, r.left, r.top);
	}
}
