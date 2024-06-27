#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	int x = 0;
	int y = 0;
	//배열에 이미지 경로 넣는 작업
	BitMapManager::GetInstance()->Init(m_hWnd);
	m_tile1 = BitMapManager::GetInstance()->GetImage(IMAGE_TILE1);
	m_tile2 = BitMapManager::GetInstance()->GetImage(IMAGE_TILE2);

	InitBoard();
	InitPiece();
}

//타일의 영역을 설정 해주기 위함
void GameManager::InitBoard()
{
	int x = XSTART;
	int y = YSTART;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//left 왼쪽 위 모서리 x
			//top 왼쪽 위 모서리 y
			//right 오른쪽 아래 모서리 x
			//bottom 오른쪽 아래 모서리 y
			m_board[i][j].left = x;
			m_board[i][j].top = y;
			m_board[i][j].right = x + TILE_SIZE;
			m_board[i][j].bottom = y + TILE_SIZE;
			x += TILE_SIZE;
		}
		x = XSTART;
		y += TILE_SIZE;
	}
}

void GameManager::InitPiece()
{
	//백색 폰
	for (int i = 0; i < 8; i++)
	{
		Piece* p = new Pawn(i * 75, 450);
		m_pieces[0][i] = p;
	}
	//흑색 폰
	for (int i = 0; i < 8; i++)
	{
		Piece* p = new Pawn(i * 75, 75);
		m_pieces[1][i] = p;
	}
	//백색 루크
	m_pieces[0][8] = new Rook(0, 525);
	m_pieces[0][9] = new Rook(525, 525);
	//흑색 루크
	m_pieces[1][8] = new Rook(0, 0);
	m_pieces[1][9] = new Rook(525, 0);
	//백색 나이트
	m_pieces[0][10] = new Knight(75, 525);
	m_pieces[0][11] = new Knight(450, 525);
	//흑색 나이트
	m_pieces[1][10] = new Knight(75, 0);
	m_pieces[1][11] = new Knight(450, 0);
	//백색 비숍
	m_pieces[0][12] = new Bishop(150, 525);
	m_pieces[0][13] = new Bishop(375, 525);
	//흑색 비숍
	m_pieces[1][12] = new Bishop(150, 0);
	m_pieces[1][13] = new Bishop(375, 0);
	//백색 퀸과 킹
	m_pieces[0][14] = new Queen(225, 525);
	m_pieces[0][15] = new King(300, 525);
	//흑색 퀸과 킹
	m_pieces[1][14] = new Queen(225, 0);
	m_pieces[1][15] = new King(300, 0);
}


void GameManager::Draw(HDC hdc)
{
	int x = XSTART;
	int y = YSTART;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//타일이 연속되지 않게 그리기 위함.
			if ((i + j) % 2 == 0)
			{
				m_tile1->Draw(hdc, x, y);
			}
			else
			{
				m_tile2->Draw(hdc, x, y);
			}
			x += TILE_SIZE;
		}
		x = XSTART;
		y += TILE_SIZE;
	}

	PieceDraw(hdc);
}

void GameManager::PieceDraw(HDC hdc)
{
	for (auto& p : m_pieces[0])
	{
		if (p != nullptr)
			p->Draw(hdc);
	}

	for (auto& p : m_pieces[1])
	{
		if (p != nullptr)
			p->Draw(hdc);
	}
}

GameManager::~GameManager()
{
	DeleteDC(m_hdc);
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			delete m_pieces[i][j];
		}
	}
}
