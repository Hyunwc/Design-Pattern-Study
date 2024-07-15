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
	//m_tile1 = BitMapManager::GetInstance()->GetImage(IMAGE_MOVETILE);
    m_tile2 = BitMapManager::GetInstance()->GetImage(IMAGE_TILE2);
	//m_tile2 = BitMapManager::GetInstance()->GetTestTile();
	//m_tile2 = BitMapManager::GetInstance()->GetImage(IMAGE_MOVETILE);
	//m_rBitMap = BitMapManager::GetInstance()->GetTestTile();
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
			m_colors[i][j] = PIECE_COLOR_NONE;
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
		Piece* p = new Pawn(i, 6, IMAGE_WHITE_PAWN, PIECE_COLOR_WHITE);
		m_pieces[0][i] = p;
		m_colors[6][i] = PIECE_COLOR_WHITE;
	}
	//��� ��
	for (int i = 0; i < 8; i++)
	{
		Piece* p = new Pawn(i, 1, IMAGE_BLACK_PAWN, PIECE_COLOR_BLACK);
		m_pieces[1][i] = p;
		m_colors[1][i] = PIECE_COLOR_BLACK;
	}

	
	//��� ��ũ
	m_pieces[0][8] = new Rook(0, 7, IMAGE_WHITE_ROOK, PIECE_COLOR_WHITE);
	m_pieces[0][9] = new Rook(7, 7, IMAGE_WHITE_ROOK, PIECE_COLOR_WHITE);
	m_colors[7][0] = PIECE_COLOR_WHITE;
	m_colors[7][7] = PIECE_COLOR_WHITE;

	//��� ��ũ
	m_pieces[1][8] = new Rook(0, 0, IMAGE_BLACK_ROOK, PIECE_COLOR_BLACK);
	m_pieces[1][9] = new Rook(7, 0, IMAGE_BLACK_ROOK, PIECE_COLOR_BLACK);
	m_colors[0][0] = PIECE_COLOR_BLACK;
	m_colors[0][7] = PIECE_COLOR_BLACK;
	//��� ����Ʈ
	m_pieces[0][10] = new Knight(1, 7, IMAGE_WHITE_KNIGHT, PIECE_COLOR_WHITE);
	m_pieces[0][11] = new Knight(6, 7, IMAGE_WHITE_KNIGHT, PIECE_COLOR_WHITE);
	m_colors[7][1] = PIECE_COLOR_WHITE;
	m_colors[7][6] = PIECE_COLOR_WHITE;
	//��� ����Ʈ
	m_pieces[1][10] = new Knight(1, 0, IMAGE_BLACK_KNIGHT, PIECE_COLOR_BLACK);
	m_pieces[1][11] = new Knight(6, 0, IMAGE_BLACK_KNIGHT, PIECE_COLOR_BLACK);
	m_colors[0][1] = PIECE_COLOR_BLACK;
	m_colors[0][6] = PIECE_COLOR_BLACK;
	//��� ���
	m_pieces[0][12] = new Bishop(2, 7, IMAGE_WHITE_BISHOP, PIECE_COLOR_WHITE);
	m_pieces[0][13] = new Bishop(5, 7, IMAGE_WHITE_BISHOP, PIECE_COLOR_WHITE);
	m_colors[7][2] = PIECE_COLOR_WHITE;
	m_colors[7][5] = PIECE_COLOR_WHITE;
	//��� ���
	m_pieces[1][12] = new Bishop(2, 0, IMAGE_BLACK_BISHOP, PIECE_COLOR_BLACK);
	m_pieces[1][13] = new Bishop(5, 0, IMAGE_BLACK_BISHOP, PIECE_COLOR_BLACK);
	m_colors[0][2] = PIECE_COLOR_BLACK;
	m_colors[0][5] = PIECE_COLOR_BLACK;
	//��� ���� ŷ
	m_pieces[0][14] = new Queen(3, 7, IMAGE_WHITE_QUEEN, PIECE_COLOR_WHITE);
	m_pieces[0][15] = new King(4, 7, IMAGE_WHITE_KING, PIECE_COLOR_WHITE);
	m_colors[7][3] = PIECE_COLOR_WHITE;
	m_colors[7][4] = PIECE_COLOR_WHITE;
	//��� ���� ŷ
	m_pieces[1][14] = new Queen(3, 0, IMAGE_BLACK_QUEEN, PIECE_COLOR_BLACK);
	m_pieces[1][15] = new King(4, 0, IMAGE_BLACK_KING, PIECE_COLOR_BLACK);
	m_colors[0][3] = PIECE_COLOR_BLACK;
	m_colors[0][4] = PIECE_COLOR_BLACK;
	
}

bool GameManager::CheckCollide(POINT point)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			//������ null�� �ƴϸ� Ŭ���� �������� ���
		
			if (m_pieces[i][j] != nullptr && PtInRect(m_pieces[i][j]->GetRect(), point))
			{
				//�ش� Ŭ������ ���Ž�� �۾� ����.
				m_select = m_pieces[i][j];
				m_select->RouteNav();
			
				return true;
			}
		}
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

	if (m_select != nullptr)
	{
		m_select->RouteDraw(hdc);
		//InvalidateRect(m_hWnd, NULL, TRUE);
	}
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

bool GameManager::CheckRoute(POINT point)
{
	if (m_select == nullptr)
		return false;

	for (RECT r : m_select->RouteNav())
	{
		if (PtInRect(&r, point))
		{
			MovePiece(point);
			return true;
		}
	}
	return false;
}

void GameManager::MovePiece(POINT point)
{
	////������ǥ x,y�� ����� ���� �� ��ǥ ����
	//int oldX = m_select->GetPosX();
	//int oldY = m_select->GetPosY();
	//int newX = point.x / 75;
	//int newY = point.y / 75;

	//m_select->Init(newX, newY);
	//m_colors[oldY][oldX] = PIECE_COLOR_NONE;
	//m_colors[newY][newX] = m_select->GetColor();
	//m_select = nullptr;
	
	//������ǥ x,y�� ����� ���� �� ��ǥ ����
	int oldX = m_select->GetPosX();
	int oldY = m_select->GetPosY();
	int newX = point.x / 75;
	int newY = point.y / 75;

	//���� ��ǥ�� ����� ���� NONE�� �ƴϸ鼭 
	//���� �ڱ�� ���� ������ �ƴ� ���
	if (m_colors[newY][newX] != PIECE_COLOR_NONE && m_colors[newY][newX] != m_select->GetColor())
	{
		
		//RemovePiece(newX, newY);
		//remove(m_pieces->begin(), m_pieces->end(), m_pieces[newY][newX]);
	}

	//��ǥ �̵� 
	m_select->Init(newX, newY);
	//������ǥ���� None���� 
	m_colors[oldY][oldX] = PIECE_COLOR_NONE;
	//���ο���ǥ������ �� ��ü�� ������
	m_colors[newY][newX] = m_select->GetColor();
	m_select = nullptr;
}

void GameManager::RemovePiece(int x, int y)
{

}

bool GameManager::KillPiece(POINT point)
{
	
	return false;
}

PIECE_COLOR GameManager::GetPieceColor(RECT rect)
{
	//�̵��� ����� ������ ���ٸ� �� ������ ���� ��ȯ
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j].left == rect.left && m_board[i][j].top == rect.top)
			{
				return m_colors[i][j];
			}
		}
	}
	//������ None��ȯ
	return PIECE_COLOR_NONE;
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
