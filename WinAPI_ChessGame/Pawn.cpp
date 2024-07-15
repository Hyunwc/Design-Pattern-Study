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
	//컨테이너에 저장된 값을 전부 지운 후 영역 계산해서 push
	vector<RECT> m_route;
	RECT route = m_rect;

	//폰이 백색인지 흑색인지에 따라 방향 설정
	int direction = (m_color == PIECE_COLOR_WHITE) ? -1 : 1;

	//한칸 이동
	route.top += direction * 75;
	route.bottom += direction * 75;
	if (IsMoveable(route))
	{
		m_route.push_back(route);
	}
	
	//첫 이동시 두칸 전진 가능
	if (firstMove)
	{
		RECT twoStep = { route.left, route.top + direction * 75 , route.right, route.bottom + direction * 75 };
		if (IsMoveable(twoStep))
		{
			m_route.push_back(twoStep);
		}
	}

	//이제 대각선 위치에 적이 있다면 대각선으로 이동 가능하게 수정 해야함.
	//왼쪽 대각선과 오른쪽 대각선
	int leftDiagonalX = m_ix - 1; 
	int rightDiagonalX = m_ix + 1;
	int diagonalY = m_iy + direction;

	//왼쪽 대각선
	if (leftDiagonalX >= 0 && leftDiagonalX < 8 && diagonalY >= 0 && diagonalY < 8)
	{
		RECT l_diagonal = { leftDiagonalX * 75, diagonalY * 75, (leftDiagonalX + 1) * 75, (diagonalY + 1) * 75 };
		//컬러에 왼쪽 대각선 영역에 어떤 색깔이 들어있는지 삽입
		//PIECE_COLOR color = GameManager::Instance()->GetPieceColor(l_diagonal);
		//왼쪽 영역이 NONE이 아니면서 현재 자신의 색과 다르다면(적이라는 것) 삽입
		if (IsEnemy(l_diagonal))
		{
			m_route.push_back(l_diagonal);
		}
			
	}
	//오른쪽 대각선
	if (rightDiagonalX >= 0 && rightDiagonalX < 8 && diagonalY >= 0 && diagonalY < 8)
	{
		RECT r_diagonal = { rightDiagonalX * 75, diagonalY * 75, (rightDiagonalX + 1) * 75, (diagonalY + 1) * 75 };
		//PIECE_COLOR color = GameManager::Instance()->GetPieceColor(r_diagonal);
		if (IsEnemy(r_diagonal))
			m_route.push_back(r_diagonal);
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
	//매개변수 rect(말이 이동할 영역)의 컬러가 None이면 true
	PIECE_COLOR color = GameManager::Instance()->GetPieceColor(rect);
	return (color == PIECE_COLOR_NONE);
}

bool Pawn::IsEnemy(RECT rect)
{
	PIECE_COLOR color = GameManager::Instance()->GetPieceColor(rect);
	return (color != PIECE_COLOR_NONE && color != m_color);
}


