#include "Knight.h"

Knight::Knight(int x, int y, IMAGE index, PIECE_COLOR color) : Piece(x, y, index, color)
{
	Init(x, y);
}

void Knight::Init(int x, int y)
{
	Piece::Init(x, y);
}

void Knight::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}

vector<RECT> Knight::RouteNav()
{
	vector<RECT> m_route;
	
	int moves[8][2] = {
		{ -1, -2 }, { -1, 2}, {1, -2}, {1, 2},
		{ -2, -1}, {-2, 1}, {2, -1}, {2, 1}
	};
	
	for (int i = 0; i < 8; i++)
	{
		//현재 위치에서 더하고 뺀값을 계산하여 저장
		int newX = m_ix + moves[i][1];
		int newY = m_iy + moves[i][0];

		if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
		{
			RECT route = { newX * 75, newY * 75, (newX + 1) * 75, (newY + 1) * 75 };
			if (IsMoveable(route)) m_route.push_back(route);
		}
	}
	
	return m_route;
}

void Knight::RouteDraw(HDC hdc)
{
	for (RECT r : RouteNav())
	{
		m_rBitMap->AlphaDraw(hdc, r.left, r.top);
	}
}

bool Knight::IsMoveable(RECT rect)
{
	//이동할 영역이 None이면서 자기 영역이 아닐때
	PIECE_COLOR color = GameManager::Instance()->GetPieceColor(rect);
	return (color == PIECE_COLOR_NONE || color != m_color);
}

void Knight::Test(RECT temp, int w, int h)
{
	//현재 말이 위치한 영역으로 초기화.
	RECT test = temp;

	test.left = w * 75;
	test.top = h * 75;
	test.right = test.left + 75;
	test.bottom = test.top + 75;

	//m_route.push_back(test);
	
}
