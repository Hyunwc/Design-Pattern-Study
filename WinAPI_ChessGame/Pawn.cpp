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
	//Ŭ���� �� ���� ����ؼ� push
	m_route.clear();
	RECT route = m_rect;

	//��ĭ �̵�
	route.top -= 75;
	route.bottom -= 75;
	m_route.push_back(route);
	//�տ� ��ֹ��� �ֵ� ���� ����. �ϴ� ������ �׽�Ʈ.
	//
	if (firstMove)
	{
		route.top -= 75;
		route.bottom -= 75;
		m_route.push_back(route);
	}

	//���� �밢�� ��ġ�� ���� �ִٸ� �밢������ �̵� �����ϰ� ���� �ؾ���.
	//���� �밢���� ������ �밢��
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


