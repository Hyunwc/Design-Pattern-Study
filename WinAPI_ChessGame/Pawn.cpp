#include "Pawn.h"

Pawn::Pawn(int x, int y, IMAGE index) : Piece(x, y, index)
{
	firstMove = true;
	Init(x, y);
}

void Pawn::Init(int x, int y)
{
	Piece::Init(x, y);
}

bool Pawn::RouteNav()
{
	RECT test = m_rect;

	test.top -= 75;
	test.bottom -= 75;
	m_route.push_back(test);
	return true;
	//앞에 장애물이 있든 말든 무시. 일단 백으로 테스트. 
}


void Pawn::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}

void Pawn::RouteDraw(HDC hdc)
{
	for (RECT r : m_route)
	{
		m_rBitMap->Draw(hdc, r.left, r.top);
	}
}


