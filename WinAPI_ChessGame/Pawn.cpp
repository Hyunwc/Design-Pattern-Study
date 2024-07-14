#include "Pawn.h"
#include "GameManager.h"

Pawn::Pawn(int x, int y, IMAGE index, PIECE_COLOR color) : Piece(x, y, index, color)
{
	firstMove = true;
	Init(x, y);
}

void Pawn::Init(int x, int y)
{
	//m_route.clear();
	Piece::Init(x, y);
}

vector<RECT> Pawn::RouteNav()
{
	//�����̳ʿ� ����� ���� ���� ���� �� ���� ����ؼ� push
	vector<RECT> m_route;
	RECT route = m_rect;

	//��ĭ �̵�
	route.top -= 75;
	route.bottom -= 75;
	if(IsMoveable(route)) m_route.push_back(route);
	//�տ� ��ֹ��� �ֵ� ���� ����. �ϴ� ������ �׽�Ʈ.
	//
	if (firstMove)
	{
		route.top -= 75;
		route.bottom -= 75;
		if (IsMoveable(route)) m_route.push_back(route);
	}

	//���� �밢�� ��ġ�� ���� �ִٸ� �밢������ �̵� �����ϰ� ���� �ؾ���.
	//���� �밢���� ������ �밢��
	int leftDiagonalX = m_ix - 1; 
	int rightDiagonalX = m_ix + 1;
	int diagonalY = m_iy - 1;

	if (leftDiagonalX >= 0 && leftDiagonalX < 8 && diagonalY >= 0 && diagonalY < 8)
	{
		RECT l_diagonal = { leftDiagonalX * 75, diagonalY * 75, (leftDiagonalX + 1) * 75, (diagonalY + 1) * 75 };
		if (IsMoveable(route)) m_route.push_back(l_diagonal);
	}
	if (rightDiagonalX >= 0 && rightDiagonalX < 8 && diagonalY >= 0 && diagonalY < 8)
	{
		RECT r_diagonal = { rightDiagonalX * 75, diagonalY * 75, (rightDiagonalX + 1) * 75, (diagonalY + 1) * 75 };
		if (IsMoveable(route)) m_route.push_back(r_diagonal);
	}

	if (firstMove)
	{
		firstMove = false;
	}

	return m_route;
}


void Pawn::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_rect.left, m_rect.top);
}

void Pawn::RouteDraw(HDC hdc)
{
	for (RECT r : RouteNav())
	{
		m_rBitMap->TestDraw(hdc, r.left, r.top);
	}
}

bool Pawn::IsMoveable(RECT rect)
{
	PIECE_COLOR color = GameManager::Instance()->GetPieceColor(rect);
	return (color == PIECE_COLOR_NONE);
}


