#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	
	m_hWnd = hWnd;
	HDC hdc = GetDC(m_hWnd);
	int x = 0;
	int y = 0;
	timer = 5;
	isEnd = false;

	//�迭�� �̹��� ��� �ִ� �۾�
	BitMapManager::GetInstance()->Init(hdc);
	m_tile1 = BitMapManager::GetInstance()->GetImage(IMAGE_TILE1);
    m_tile2 = BitMapManager::GetInstance()->GetImage(IMAGE_TILE2);
	m_turn = PIECE_COLOR_WHITE;
	m_state = Main;
	//(800 - 200) / 2 = 300
	startRect.left = (615 - 200) / 2;
	//(800 - 50) / 2 - 50 = 325
	startRect.top = (700 - 50) / 2 - 50;
	//300 + 200 = 500
	startRect.right = startRect.left + 200;
	//325 + 50 = 375
	startRect.bottom = startRect.top + 50;

	endRect.left = startRect.left;
	endRect.top = startRect.bottom + 50;
	endRect.right = startRect.right;
	endRect.bottom = endRect.top + 50;

	RECT clientRect;
	GetClientRect(m_hWnd, &clientRect);
	//������ �ƴ� ������ ����,����
	width = clientRect.right + 1;
	height = clientRect.bottom + 1;

	backDC = CreateCompatibleDC(hdc);
	backRect = { 0, 0, width, height };
	whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

	ReleaseDC(m_hWnd, hdc);

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
	
	m_promotionimage[0].push_back(BitMapManager::GetInstance()->GetImage(IMAGE_BLACK_ROOK));
	m_promotionimage[0].push_back(BitMapManager::GetInstance()->GetImage(IMAGE_BLACK_KNIGHT));
	m_promotionimage[0].push_back(BitMapManager::GetInstance()->GetImage(IMAGE_BLACK_BISHOP));
	m_promotionimage[0].push_back(BitMapManager::GetInstance()->GetImage(IMAGE_BLACK_QUEEN));

	m_promotionimage[1].push_back(BitMapManager::GetInstance()->GetImage(IMAGE_WHITE_ROOK));
	m_promotionimage[1].push_back(BitMapManager::GetInstance()->GetImage(IMAGE_WHITE_KNIGHT));
	m_promotionimage[1].push_back(BitMapManager::GetInstance()->GetImage(IMAGE_WHITE_BISHOP));
	m_promotionimage[1].push_back(BitMapManager::GetInstance()->GetImage(IMAGE_WHITE_QUEEN));
}

bool GameManager::CheckCollide(POINT point)
{
	switch (m_state)
	{
	case Main:
	{
		//���ӽ���
		if (PtInRect(&startRect, point))
		{
			m_state = GamePlay;
			return true;
		}
		//������ ����
		if (PtInRect(&endRect, point))
		{
			PostQuitMessage(0);
		}
		break;
	}
	case GamePlay:
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < m_pieces[i].size(); j++)
			{
				//������ null�� �ƴϸ� Ŭ���� �������� ���
				if (m_pieces[i][j] != nullptr && PtInRect(m_pieces[i][j]->GetRect(), point))
				{
					if (m_pieces[i][j]->GetColor() == m_turn)
					{
						//�ش� Ŭ������ ���Ž�� �۾� ����.
						m_select = m_pieces[i][j];
						return true;
					}

				}
			}
		}
		break;
	}
	case PawnPromotion:
	{
		int size = m_promotionimage[0].size();
		int color = 0;
		//�̹� ���� ��������� ������ �Ǿ��� ������ ȭ��Ʈ�� ���̰� ���̰� ȭ��Ʈ�� ���Ǿ�� �Ѵ�.
		switch (m_turn)
		{
		case PIECE_COLOR_BLACK:
			color = 1;
			break;
		case PIECE_COLOR_WHITE:
			color = 0;
			break;
		}
		for (int i = 0; i < size; i++)
		{
			if (PtInRect(m_promotionimage[color][i]->GetRect(promotionPos[i][0] * 75, promotionPos[i][1] * 75), point))
			{
				//m_promotionimage�� �̹���Ÿ�Ը� �������ָ� ���ε�..~~
				Promotion(newX, newY, m_promotionimage[color][i]->GetImage());
				m_state = GamePlay;
				return true;
			}
		}
		break;
	}
	default:
		break;
	}
	

	return false;
}


void GameManager::Draw(HDC hdc)
{
	//���⸸ �����ϸ��
	//backBitMap�� �Ź� ���� ������ �Ǿ����.
	
	HBITMAP backBitmap = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(backDC, backBitmap);
	 
	FillRect(backDC, &backRect, whiteBrush);
	

	switch (m_state)
	{
	case Main:
	{
		Rectangle(backDC, startRect.left, startRect.top, startRect.right, startRect.bottom);
		Rectangle(backDC, endRect.left, endRect.top, endRect.right, endRect.bottom);
		TextOut(backDC, 270, 290, TEXT("StartGame"), 9);
		TextOut(backDC, 270, 390, TEXT("EndGame"), 7);

		break;
	}
	case GamePlay:
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
					m_tile1->Draw(backDC, x, y);
				}
				else
				{
					m_tile2->Draw(backDC, x, y);
				}
				x += TILE_SIZE;
			}
			x = XSTART;
			y += TILE_SIZE;
		}

		PieceDraw(backDC);
		if (m_turn == PIECE_COLOR_WHITE)
			TextOutA(backDC, 270, 620, "WhiteTurn", 9);
		else
			TextOutA(backDC, 270, 620, "BlackTurn", 9);

		if (m_select != nullptr)
		{
			m_select->RouteDraw(backDC);
		}
		//BitBlt(hdc, 0, 0, clientRect.right + 1, clientRect.bottom + 1, backDC, 0, 0, SRCCOPY);
		break;
	}
	case PawnPromotion:
	{
		int size = m_promotionimage[0].size();
		int color = 0;
		//�̹� ���� ��������� ������ �Ǿ��� ������ ȭ��Ʈ�� ���̰� ���� ȭ��Ʈ�� ���Ǿ�� �Ѵ�.
		switch (m_turn)
		{
		case PIECE_COLOR_BLACK:
			color = 1;
			break;
		case PIECE_COLOR_WHITE:
			color = 0;
			break;
		}
		for (int i = 0; i < size; i++)
		{
			m_promotionimage[color][i]->Draw(backDC, promotionPos[i][0] * 75, promotionPos[i][1] * 75);
		}

		TextOut(backDC, 250, 400, TEXT("���� �����ϼ���."), 9);
		break;
	}
	case GameEnd:
	{
		char c_buf[256];
		sprintf_s(c_buf, "%d�� �ڿ� ���� �޴��� �̵��մϴ�.", timer);
		TextOutA(backDC, 200, 250, c_buf, strlen(c_buf));
		TextOut(backDC, 270, 350, winstr.c_str(), winstr.length());
		break;
	}
	default:
		break;
	}

	BitBlt(hdc, 0, 0, width, height, backDC, 0, 0, SRCCOPY);
	
	DeleteObject(backBitmap);
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
			//�̵� �� �� ü����
			TurnChange();
			return true;
		}
	}
	return false;
}

void GameManager::MovePiece(POINT point)
{
	//������ǥ x,y�� ����� ���� �� ��ǥ ����
	int oldX = m_select->GetPosX();
	int oldY = m_select->GetPosY();

	newX = point.x / 75;
	newY = point.y / 75;

	//���� ��ǥ�� ����� ���� NONE�� �ƴϸ鼭 
	//���� �ڱ�� ���� ������ �ƴ� ���
	if (m_colors[newY][newX] != PIECE_COLOR_NONE)
	{
		for (int i = 0; i < 2; i++)
		{
			for (auto iter = m_pieces[i].begin(); iter != m_pieces[i].end(); iter++)
			{
				if ((*iter)->GetPosX() == newX && (*iter)->GetPosY() == newY)
				{
					//ŷ�Ͻ� ��������
					if ((*iter)->GetImage() == IMAGE_BLACK_KING || (*iter)->GetImage() == IMAGE_WHITE_KING)
					{
						((*iter)->GetImage() == IMAGE_BLACK_KING) ? winstr = L"White Win!" : winstr = L"Black Win!";
						m_state = GameEnd;
						SetTimer(m_hWnd, 1, 1000, NULL);
						SetTimer(m_hWnd, 2, 5000, NULL);
						isEnd = true;
					}
					delete *iter;
				    m_pieces[i].erase(iter);
					break;
				}
			}
		}
		m_colors[newY][newX] = PIECE_COLOR_NONE;
	}

	//��ǥ �̵� 
	m_select->Init(newX, newY);
	//������ǥ���� None���� 
	m_colors[oldY][oldX] = PIECE_COLOR_NONE;
	//���ο���ǥ������ �� ��ü�� ������
	m_colors[newY][newX] = m_select->GetColor();
	//���θ�� �˻�
	if (!isEnd)
	{
		if (m_select->GetImage() == IMAGE_WHITE_PAWN && newY == 0 || m_select->GetImage() == IMAGE_BLACK_PAWN && newY == 7)
		{
			m_state = PawnPromotion;
		}
	}
	

	if ((m_select->GetImage() == IMAGE_WHITE_PAWN || m_select->GetImage() == IMAGE_BLACK_PAWN ) && m_select->GetFirstMove())
	{
		m_select->SetFirstMove();
	}
	m_select = nullptr;
}

void GameManager::TurnChange()
{
	//ȭ��Ʈ ���̸� ������ �ƴϸ� ȭ��Ʈ��
	m_turn = (m_turn == PIECE_COLOR_WHITE) ? PIECE_COLOR_BLACK : PIECE_COLOR_WHITE;
}

void GameManager::UpdateTimer()
{
	if (m_state == GameEnd)
	{
		timer--;
		if (timer <= 0)
		{
			m_state = Main;
			KillTimer(m_hWnd, 1);
			KillTimer(m_hWnd, 2);
		}
		InvalidateRect(m_hWnd, NULL, false);
	}
}

void GameManager::Promotion(int x, int y, IMAGE type)
{
	//���� ���� �������� �� ȣ��Ǵ� �Լ�
	//�켱 ���Ϳ� ����ִ� ���� �����͸� ����..
	//�׽�Ʈ�� ������ �غ���. ���� ��ü �����ؼ� ���Ϳ� ���� �� ���� ���� ������ �Ҵ�.
	PIECE_COLOR color = m_colors[y][x];

	//�� ����
	for (int i = 0; i < 2; i++)
	{
		for (auto iter = m_pieces[i].begin(); iter != m_pieces[i].end(); iter++)
		{
			if ((*iter)->GetPosX() == x && (*iter)->GetPosY() == y)
			{
				delete* iter;
				m_pieces[i].erase(iter);
				break;
			}
		}
	}

	Piece* newPiece;
	//���� �°�
	switch (type)
	{
	case IMAGE_BLACK_KNIGHT:
	case IMAGE_WHITE_KNIGHT:
		newPiece = new Knight(x, y, type, color);
		break;
	case IMAGE_BLACK_BISHOP:
	case IMAGE_WHITE_BISHOP:
		newPiece = new Bishop(x, y, type, color);
		break;
	case IMAGE_BLACK_ROOK:
	case IMAGE_WHITE_ROOK:
		newPiece = new Rook(x, y, type, color);
		break;
	case IMAGE_BLACK_QUEEN:
	case IMAGE_WHITE_QUEEN:
		newPiece = new Queen(x, y, type, color);
		break;
	}

	m_pieces[color == PIECE_COLOR_WHITE ? 0 : 1].push_back(newPiece);
	m_colors[y][x] = color;
}

void GameManager::Reset()
{
	for (int i = 0; i < 2; ++i)
	{
		m_pieces[i].clear();
		m_pieces[i].resize(16);

		m_promotionimage[i].clear();
	}	
	
	Init(m_hWnd);
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
	
	DeleteDC(backDC);
	DeleteObject(whiteBrush);
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < m_pieces[i].size(); ++j)
		{
			delete m_pieces[i][j];
		}
	}
}
