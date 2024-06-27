#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	int x = 0;
	int y = 0;
	//�迭�� �̹��� ��� �ִ� �۾�
	BitMapManager::GetInstance()->Init(m_hWnd);
	m_tile1 = BitMapManager::GetInstance()->GetImage(IMAGE_TILE1);
	m_tile2 = BitMapManager::GetInstance()->GetImage(IMAGE_TILE2);

	InitBoard();
	InitPiece();
}

//Ÿ���� ������ ���� ���ֱ� ����
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

void GameManager::InitPiece()
{
	//��� ��
	for (int i = 0; i < 8; i++)
	{
		Piece* p = new Pawn(i * 75, 450);
		m_pieces[0][i] = p;
	}
	//��� ��
	for (int i = 0; i < 8; i++)
	{
		Piece* p = new Pawn(i * 75, 75);
		m_pieces[1][i] = p;
	}
	//��� ��ũ
	m_pieces[0][8] = new Rook(0, 525);
	m_pieces[0][9] = new Rook(525, 525);
	//��� ��ũ
	m_pieces[1][8] = new Rook(0, 0);
	m_pieces[1][9] = new Rook(525, 0);
	//��� ����Ʈ
	m_pieces[0][10] = new Knight(75, 525);
	m_pieces[0][11] = new Knight(450, 525);
	//��� ����Ʈ
	m_pieces[1][10] = new Knight(75, 0);
	m_pieces[1][11] = new Knight(450, 0);
	//��� ���
	m_pieces[0][12] = new Bishop(150, 525);
	m_pieces[0][13] = new Bishop(375, 525);
	//��� ���
	m_pieces[1][12] = new Bishop(150, 0);
	m_pieces[1][13] = new Bishop(375, 0);
	//��� ���� ŷ
	m_pieces[0][14] = new Queen(225, 525);
	m_pieces[0][15] = new King(300, 525);
	//��� ���� ŷ
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
			//Ÿ���� ���ӵ��� �ʰ� �׸��� ����.
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
