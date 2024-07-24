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

vector<RECT> Rook::RouteNav()
{
	vector<RECT> m_route;
	//����
	for (int i = m_iy - 1; i >= 0; i--)
	{
		RECT route = { m_ix * 75, i * 75, (m_ix + 1) * 75, (i + 1) * 75 };
		//������ �������̸� break
		if (!IsMoveable(route)) break;
		m_route.push_back(route);
		if (IsEnemy(route)) break;
	}
	for (int i = m_iy + 1; i < 8; i++)
	{
		RECT route = { m_ix * 75, i * 75, (m_ix + 1) * 75, (i + 1) * 75 };
		if (!IsMoveable(route)) break;
		m_route.push_back(route);
		if (IsEnemy(route)) break;
	}
	//����
	for (int i = m_ix - 1; i >= 0; i--)
	{
		RECT route = { i * 75, m_iy * 75, (i + 1) * 75, (m_iy + 1) * 75 };
		if (!IsMoveable(route)) break;
		m_route.push_back(route);
		if (IsEnemy(route)) break;
	}
	for (int i = m_ix + 1; i < 8; i++)
	{
		RECT route = { i * 75, m_iy * 75, (i + 1) * 75, (m_iy + 1) * 75 };
		if (!IsMoveable(route)) break;
		m_route.push_back(route);
		if (IsEnemy(route)) break;
	}
	
	return m_route;
}

void Rook::RouteDraw(HDC hdc)
{
	for (RECT r : RouteNav())
	{
		m_rBitMap->AlphaDraw(hdc, r.left, r.top);
	}
}

bool Rook::IsMoveable(RECT rect)
{
	//�̵��� ������ None �Ǵ� �ڱ� ���� �ƴϸ� 
	PIECE_COLOR color = GameManager::Instance()->GetPieceColor(rect);
	return (color == PIECE_COLOR_NONE || color != m_color);
}


bool Rook::IsEnemy(RECT rect)
{
	//�̵��� ������ �����̶�� true
	PIECE_COLOR color = GameManager::Instance()->GetPieceColor(rect);
	return (color != m_color && color != PIECE_COLOR_NONE);
}
