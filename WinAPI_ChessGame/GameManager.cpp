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
	m_rBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_MOVETILE);
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
		Piece* p = new Pawn(i, 6, IMAGE_WHITE_PAWN);
		m_pieces[0][i] = p;
	}
	//��� ��
	for (int i = 0; i < 8; i++)
	{
		Piece* p = new Pawn(i, 1, IMAGE_BLACK_PAWN);
		m_pieces[1][i] = p;
	}

	
	//��� ��ũ
	m_pieces[0][8] = new Rook(0, 7, IMAGE_WHITE_ROOK);
	m_pieces[0][9] = new Rook(7, 7, IMAGE_WHITE_ROOK);
	//��� ��ũ
	m_pieces[1][8] = new Rook(0, 0, IMAGE_BLACK_ROOK);
	m_pieces[1][9] = new Rook(7, 0, IMAGE_BLACK_ROOK);
	//��� ����Ʈ
	m_pieces[0][10] = new Knight(1, 7, IMAGE_WHITE_KNIGHT);
	m_pieces[0][11] = new Knight(6, 7, IMAGE_WHITE_KNIGHT);
	//��� ����Ʈ
	m_pieces[1][10] = new Knight(1, 0, IMAGE_BLACK_KNIGHT);
	m_pieces[1][11] = new Knight(6, 0, IMAGE_BLACK_KNIGHT);
	//��� ���
	m_pieces[0][12] = new Bishop(2, 7, IMAGE_WHITE_BISHOP);
	m_pieces[0][13] = new Bishop(5, 7, IMAGE_WHITE_BISHOP);
	//��� ���
	m_pieces[1][12] = new Bishop(2, 0, IMAGE_BLACK_BISHOP);
	m_pieces[1][13] = new Bishop(5, 0, IMAGE_BLACK_BISHOP);
	//��� ���� ŷ
	m_pieces[0][14] = new Queen(3, 7, IMAGE_WHITE_QUEEN);
	m_pieces[0][15] = new King(4, 7, IMAGE_WHITE_KING);
	//��� ���� ŷ
	m_pieces[1][14] = new Queen(3, 0, IMAGE_BLACK_QUEEN);
	m_pieces[1][15] = new King(4, 0, IMAGE_BLACK_KING);
	
}

bool GameManager::CheckCollide(POINT point)
{
	/*for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 16; j++)(
		{
			if (m_pieces[i][j] != nullptr && PtInRect(&m_pieces[i][j]->GetRect(), point))
			{
				return true;
			}
		}
	}*/

	//1.�� �Ǵ��� �׽�Ʈ����->�ϴ� ȭ�� ������ ��
	//SetPosition�̿��Ͽ� ��ǥ �̵���Ű��.
	if (PtInRect(m_pieces[1][1]->GetRect(), point))
	{
		return true;
	}

	return false;
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

void GameManager::RouteDraw(HDC hdc)
{
	
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
