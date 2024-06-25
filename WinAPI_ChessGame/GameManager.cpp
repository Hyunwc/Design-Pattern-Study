#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	//m_hdc = hdc;
	int x = 0;
	int y = 0;
	//배열에 이미지 경로 넣는 작업
	BitMapManager::GetInstance()->Init(m_hWnd);
	m_tile1 = BitMapManager::GetInstance()->GetImage(IMAGE_TILE1);
	m_tile2 = BitMapManager::GetInstance()->GetImage(IMAGE_TILE2);
	
	//보드 초기화와 말 초기화
	InitBoard();
	InitPieces();
}


void GameManager::Draw(HDC hdc)
{
	int x = XSTART;
	int y = YSTART;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//타일의 그림이 연속되지 않게
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

	DrawPieces(hdc);
}

//타일의 영역 초기화
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
//말 초기화 부분
void GameManager::InitPieces()
{
	//Pawn 업캐스팅
	for (int i = 0; i < 8; i++)
	{
		//2행 흑색 폰, 7행 백색 폰
		m_pieces[1][i] = new Pawn(1, i);
		m_pieces[6][i] = new Pawn(6, i);
	}	
}

void GameManager::DrawPieces(HDC hdc)
{
	//말들을 그리는 부분
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_pieces[i][j] != nullptr)
			{
				m_pieces[i][j]->Draw(hdc);
			}
		}
	}
}

GameManager::~GameManager()
{
	DeleteDC(m_hdc);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete m_pieces[i][j];
		}
	}
}
