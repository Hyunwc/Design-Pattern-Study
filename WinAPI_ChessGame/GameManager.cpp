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
			m_colors[i][j] = PIECE_COLOR_NONE;
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
		Piece* p = new Pawn(i, 6, IMAGE_WHITE_PAWN, PIECE_COLOR_WHITE);
		m_pieces[0][i] = p;
		m_colors[6][i] = PIECE_COLOR_WHITE;
	}
	//흑색 폰
	for (int i = 0; i < 8; i++)
	{
		Piece* p = new Pawn(i, 1, IMAGE_BLACK_PAWN, PIECE_COLOR_BLACK);
		m_pieces[1][i] = p;
		m_colors[1][i] = PIECE_COLOR_BLACK;
	}

	
	//백색 루크
	m_pieces[0][8] = new Rook(0, 7, IMAGE_WHITE_ROOK, PIECE_COLOR_WHITE);
	m_pieces[0][9] = new Rook(7, 7, IMAGE_WHITE_ROOK, PIECE_COLOR_WHITE);
	m_colors[7][0] = PIECE_COLOR_WHITE;
	m_colors[7][7] = PIECE_COLOR_WHITE;

	//흑색 루크
	m_pieces[1][8] = new Rook(0, 0, IMAGE_BLACK_ROOK, PIECE_COLOR_BLACK);
	m_pieces[1][9] = new Rook(7, 0, IMAGE_BLACK_ROOK, PIECE_COLOR_BLACK);
	m_colors[0][0] = PIECE_COLOR_BLACK;
	m_colors[0][7] = PIECE_COLOR_BLACK;
	//백색 나이트
	m_pieces[0][10] = new Knight(1, 7, IMAGE_WHITE_KNIGHT, PIECE_COLOR_WHITE);
	m_pieces[0][11] = new Knight(6, 7, IMAGE_WHITE_KNIGHT, PIECE_COLOR_WHITE);
	m_colors[7][1] = PIECE_COLOR_WHITE;
	m_colors[7][6] = PIECE_COLOR_WHITE;
	//흑색 나이트
	m_pieces[1][10] = new Knight(1, 0, IMAGE_BLACK_KNIGHT, PIECE_COLOR_BLACK);
	m_pieces[1][11] = new Knight(6, 0, IMAGE_BLACK_KNIGHT, PIECE_COLOR_BLACK);
	m_colors[0][1] = PIECE_COLOR_BLACK;
	m_colors[0][6] = PIECE_COLOR_BLACK;
	//백색 비숍
	m_pieces[0][12] = new Bishop(2, 7, IMAGE_WHITE_BISHOP, PIECE_COLOR_WHITE);
	m_pieces[0][13] = new Bishop(5, 7, IMAGE_WHITE_BISHOP, PIECE_COLOR_WHITE);
	m_colors[7][2] = PIECE_COLOR_WHITE;
	m_colors[7][5] = PIECE_COLOR_WHITE;
	//흑색 비숍
	m_pieces[1][12] = new Bishop(2, 0, IMAGE_BLACK_BISHOP, PIECE_COLOR_BLACK);
	m_pieces[1][13] = new Bishop(5, 0, IMAGE_BLACK_BISHOP, PIECE_COLOR_BLACK);
	m_colors[0][2] = PIECE_COLOR_BLACK;
	m_colors[0][5] = PIECE_COLOR_BLACK;
	//백색 퀸과 킹
	m_pieces[0][14] = new Queen(3, 7, IMAGE_WHITE_QUEEN, PIECE_COLOR_WHITE);
	m_pieces[0][15] = new King(4, 7, IMAGE_WHITE_KING, PIECE_COLOR_WHITE);
	m_colors[7][3] = PIECE_COLOR_WHITE;
	m_colors[7][4] = PIECE_COLOR_WHITE;
	//흑색 퀸과 킹
	m_pieces[1][14] = new Queen(3, 0, IMAGE_BLACK_QUEEN, PIECE_COLOR_BLACK);
	m_pieces[1][15] = new King(4, 0, IMAGE_BLACK_KING, PIECE_COLOR_BLACK);
	m_colors[0][3] = PIECE_COLOR_BLACK;
	m_colors[0][4] = PIECE_COLOR_BLACK;
	
}

bool GameManager::CheckCollide(POINT point)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < m_pieces[i].size(); j++)
		{
			//영역이 null이 아니며 클릭에 성공했을 경우
		
			if (m_pieces[i][j] != nullptr && PtInRect(m_pieces[i][j]->GetRect(), point))
			{
				if (m_pieces[i][j]->GetColor() == m_turn)
				{
					//해당 클래스의 경로탐색 작업 실행.
					m_select = m_pieces[i][j];
					m_select->RouteNav();

					return true;
				}
				
			}
		}
	}

	return false;
}


void GameManager::Draw(HDC hdc)
{
	switch (m_state)
	{
	case Main:
	{
		break;
	}
	case GamePlay:
	{
		break;
	}
	case GameEnd:
	{
		break;
	}
	default:
		break;
	}
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
	if (m_turn == PIECE_COLOR_WHITE)
		TextOutA(hdc, 250, 620, "WhiteTurn", 9);
	else
		TextOutA(hdc, 250, 620, "BlackTurn", 9);

	char w_buf[256];
	char b_buf[256];
	sprintf_s(w_buf, "white : %d", m_pieces[0].size());
	sprintf_s(b_buf, "black : %d", m_pieces[1].size());
	TextOutA(hdc, 10, 620, w_buf, strlen(w_buf));
	TextOutA(hdc, 10, 640, b_buf, strlen(b_buf));

	//게임이 끝날시 승자의 Text출력
	if (isOver)
	{
		TextOut(hdc, 250, 620, winstr.c_str(), winstr.length());
	}

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
			//이동 후 턴 체인지
			TurnChange();
			return true;
		}
	}
	return false;
}

void GameManager::MovePiece(POINT point)
{
	//이전좌표 x,y는 현재로 저장 후 좌표 변경
	int oldX = m_select->GetPosX();
	int oldY = m_select->GetPosY();
	int newX = point.x / 75;
	int newY = point.y / 75;

	//다음 좌표에 저장된 색이 NONE이 아니면서 
	//현재 자기와 같은 색깔이 아닐 경우
	if (m_colors[newY][newX] != PIECE_COLOR_NONE)
	{
		for (int i = 0; i < 2; i++)
		{
			for (auto iter = m_pieces[i].begin(); iter != m_pieces[i].end(); iter++)
			{
				if ((*iter)->GetPosX() == newX && (*iter)->GetPosY() == newY)
				{
					//킹일시 게임종료
					if ((*iter)->GetImage() == IMAGE_BLACK_KING || (*iter)->GetImage() == IMAGE_WHITE_KING)
					{
						((*iter)->GetImage() == IMAGE_BLACK_KING) ? winstr = L"White Win!" : winstr = L"Black Win!";
						isOver = true;
					}
					delete *iter;
				    m_pieces[i].erase(iter);
					break;
				}

			}
			
		}
		m_colors[newY][newX] = PIECE_COLOR_NONE;
	}

	//좌표 이동 
	m_select->Init(newX, newY);
	//이전좌표공간 None으로 
	m_colors[oldY][oldX] = PIECE_COLOR_NONE;
	//새로운좌표공간은 그 객체의 색으로
	m_colors[newY][newX] = m_select->GetColor();
	//프로모션 검사
	if (m_select->GetImage() == IMAGE_WHITE_PAWN && newY == 0 || m_select->GetImage() == IMAGE_BLACK_PAWN && newY == 7)
	{
		//프로모션 수행!
		MessageBoxA(m_hWnd, "Promotion!", "Promotion!", MB_OK);
		//프로모션에 newY와newX의 좌표를 넘겨줘야함
		Promotion(newX, newY);
	}
	m_select = nullptr;
}

void GameManager::RemovePiece(int x, int y)
{

}

bool GameManager::KillPiece(POINT point)
{
	
	return false;
}

void GameManager::TurnChange()
{
	//화이트 턴이면 블랙으로 아니면 화이트로
	m_turn = (m_turn == PIECE_COLOR_WHITE) ? PIECE_COLOR_BLACK : PIECE_COLOR_WHITE;
}

void GameManager::Promotion(int x, int y)
{
	//폰이 끝에 도달했을 때 호출되는 함수
	//우선 벡터에 들어있는 폰의 데이터를 삭제..
	//테스트로 퀸으로 해보자. 퀸의 객체 생성해서 벡터에 삽입 후 이전 폰의 영역에 할당.
	PIECE_COLOR color = m_colors[y][x];

	//폰 삭제
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
	if (color == PIECE_COLOR_WHITE)
	{
		newPiece = new Queen(x, y, IMAGE_WHITE_QUEEN, PIECE_COLOR_WHITE);
	}
	else
	{
		newPiece = new Queen(x, y, IMAGE_BLACK_QUEEN, PIECE_COLOR_BLACK);
	}

	m_pieces[color == PIECE_COLOR_WHITE ? 0 : 1].push_back(newPiece);
	m_colors[y][x] = color;
}

PIECE_COLOR GameManager::GetPieceColor(RECT rect)
{
	//이동할 경로의 영역과 같다면 그 영역의 색깔 반환
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
	//없으면 None반환
	return PIECE_COLOR_NONE;
}


GameManager::~GameManager()
{
	DeleteDC(m_hdc);
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < m_pieces[i].size(); ++j)
		{
			delete m_pieces[i][j];
		}
	}
}
