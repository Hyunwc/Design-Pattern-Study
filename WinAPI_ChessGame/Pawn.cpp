#include "Pawn.h"

Pawn::Pawn(int x, int y, IMAGE index, PIECE_COLOR color) : Piece(x, y, index, color)
{
	firstMove = true;
	Init(x, y);
}

void Pawn::Init(int x, int y)
{
	m_route.clear();
	Piece::Init(x, y);
}

void Pawn::RouteNav()
{
	//클리어 후 영역 계산해서 push
	m_route.clear();
	RECT route = m_rect;

	//한칸 이동
	route.top -= 75;
	route.bottom -= 75;
	m_route.push_back(route);
	//앞에 장애물이 있든 말든 무시. 일단 백으로 테스트.
	//
	if (firstMove)
	{
		route.top -= 75;
		route.bottom -= 75;
		m_route.push_back(route);
	}

	//이제 대각선 위치에 적이 있다면 대각선으로 이동 가능하게 수정 해야함.
	//왼쪽 대각선과 오른쪽 대각선
	int leftDiagonalX = m_ix - 1; 
	int rightDiagonalX = m_ix + 1;
	int diagonalY = m_iy - 1;

	if (leftDiagonalX >= 0 && leftDiagonalX < 8 && diagonalY >= 0 && diagonalY < 8)
	{
		RECT l_diagonal = { leftDiagonalX * 75, diagonalY * 75, (leftDiagonalX + 1) * 75, (diagonalY + 1) * 75 };
		m_route.push_back(l_diagonal);
	}
	if (rightDiagonalX >= 0 && rightDiagonalX < 8 && diagonalY >= 0 && diagonalY < 8)
	{
		RECT r_diagonal = { rightDiagonalX * 75, diagonalY * 75, (rightDiagonalX + 1) * 75, (diagonalY + 1) * 75 };
		m_route.push_back(r_diagonal);
	}

	if (firstMove)
	{
		firstMove = false;
	}
}


void Pawn::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}

void Pawn::RouteDraw(HDC hdc)
{
	for (RECT r : m_route)
	{
		m_rBitMap->TestDraw(hdc, r.left, r.top);
	}
}


