#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	//m_hdc = hdc;
	int x = 0;
	int y = 0;
	//�迭�� �̹��� ��� �ִ� �۾�
	BitMapManager::GetInstance()->Init(m_hWnd);
	m_tile1 = BitMapManager::GetInstance()->GetImage(IMAGE_TILE1);
	m_tile2 = BitMapManager::GetInstance()->GetImage(IMAGE_TILE2);
	
	//���� �ʱ�ȭ�� �� �ʱ�ȭ
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
			//Ÿ���� �׸��� ���ӵ��� �ʰ�
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

//Ÿ���� ���� �ʱ�ȭ
void GameManager::InitBoard()
{
	int x = XSTART;
	int y = YSTART;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//left ���� �� �𼭸� x
			//top ���� �� �𼭸� y
			//right ������ �Ʒ� �𼭸� x
			//bottom ������ �Ʒ� �𼭸� y
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
//�� �ʱ�ȭ �κ�
void GameManager::InitPieces()
{
	//Pawn ��ĳ����
	for (int i = 0; i < 8; i++)
	{
		//2�� ��� ��, 7�� ��� ��
		m_pieces[1][i] = new Pawn(1, i);
		m_pieces[6][i] = new Pawn(6, i);
	}	
}

void GameManager::DrawPieces(HDC hdc)
{
	//������ �׸��� �κ�
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
