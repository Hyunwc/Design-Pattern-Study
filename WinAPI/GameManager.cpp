#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	//Main에서 보낼 예정
	m_hWnd = hWnd;
	first = nullptr;
	second = nullptr;
	timelimit = 60;
	finish_count = 0;
	isWin = false;
	m_cards.clear();
	//비트맵 배열에 이미지 경로 넣는 작업.
	BitMapManager::GetInstance()->Init(m_hWnd);
	m_state = MainMenu;

	int windowWidth = 800;
	int windowHeight = 800;
	int btnWidth = 200;
	int btnHeight = 50;
	

	//(800 - 200) / 2 = 300
	startRect.left = (windowWidth - btnWidth) / 2;
	//(800 - 50) / 2 - 50 = 325
	startRect.top = (windowHeight - btnHeight) / 2 - 50;
	//300 + 200 = 500
	startRect.right = startRect.left + btnWidth;
	//325 + 50 = 375
	startRect.bottom = startRect.top + btnHeight;

	endRect.left = startRect.left;
	endRect.top = startRect.bottom + btnHeight;
	endRect.right = startRect.right;
	endRect.bottom = endRect.top + btnHeight;

	// 카드 간격과 크기 정의
	const int CARD_WIDTH = 100;
	const int CARD_HEIGHT = 150;
	const int X_SPACING = 10;
	const int Y_SPACING = 10;

	// 첫 번째 카드의 위치
	int xStart = 120;
	int yStart = 100;

	// 이미지 배열
	vector<IMAGE> images;
	//IMAGE_DOG부터 시작해서 10개의 이미지를 추가.
	//두 장씩 들어가야하니 두 번씩 추가.
	for (int i = 0; i < 10; i++)
	{
		//정수형 값을 열거형 값으로 변환
		images.push_back(static_cast<IMAGE>(i));
		images.push_back(static_cast<IMAGE>(i));
	}
	//인덱스 셔플
	random_shuffle(images.begin(), images.end());

	int index = 0;
	// 5x4 카드 배치
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Card card;
			// 카드 위치 계산
			// (100,100) (210, 100) (320, 100) (430, 100) (540, 100)

			int x = xStart + j * (CARD_WIDTH + X_SPACING);
			int y = yStart + i * (CARD_HEIGHT + Y_SPACING);

			//카드의 인덱스, 그려질 x, y좌표
			card.Init(images[index], x, y);
			m_cards.push_back(card);
			index++;
		}

	}

	//제한시간을 위한 타이머
	SetTimer(m_hWnd, 2, 1000, NULL);
}

void GameManager::Draw(HDC hdc)
{

	// Rectangle함수 이용(hdc, left, top, right, bottom까지 4개의 매개변수)
	// left 사각형 왼쪽 x right 사각형 오른쪽 x 

	// 현재 게임 상태에 따라 다른 그래픽이 출력
	switch (m_state)
	{
	case MainMenu:
	{
		//BitMapManager::GetInstance()->GetBackground()->BackGroundDraw(hdc, 0, 0);
		//left, top, right, bottom
		Rectangle(hdc, startRect.left, startRect.top, startRect.right, startRect.bottom);
		//맨 뒤에 파라미터는 문자열의 길이
		TextOut(hdc, 370, 340, TEXT("StartGame"), 9);
		Rectangle(hdc, endRect.left, endRect.top, endRect.right, endRect.bottom);
		TextOut(hdc, 370, 440, TEXT("EndGame"), 7);
		break;
	}
	//게임 플레이
	case GamePlay:
	{
		//벡터에 저장된 카드들 Draw() 호출
		for (auto& card : m_cards)
		{
			card.Draw(hdc);
		}
		char g_buf[256];
		char c_buf[256];
		sprintf_s(g_buf,  "%d : %d", 0, timelimit);
		sprintf_s(c_buf,  "finish : %d", finish_count);
		TextOutA(hdc, 350, 10, g_buf, strlen(g_buf));
		TextOutA(hdc, 700, 10, c_buf, strlen(c_buf));

		
		//카드를 그리고 나서 여기서 같은짝인지 체크를 하는 함수를 호출해야 할듯
		break;
	}

	case GameEnd:
	{
		if (isWin)
			TextOut(hdc, 370, 380, TEXT("Win!"), 4);
		else
			TextOut(hdc, 370, 380, TEXT("Lose!"), 5);
		break;
	}

	default:
		break;
	}

}


//매개변수 : 클릭한 곳의 x,y좌표를 받아옴
bool GameManager::CheckCollide(POINT point)
{
	//m_state의 상태에 따라 
	switch (m_state)
	{
	case MainMenu: //메인
	{
		//체크할 사각형의 영역과 x,y(대상의 위치)를 매개변수로. (startRect영역)
		if (PtInRect(&startRect, point))
		{
			//게임 플레이 상태로 변경
			
			m_state = GamePlay;
			return true;
		}
		else if (PtInRect(&endRect, point))
		{
			PostQuitMessage(0);
			//return true;
		}
		break;
	}
	case GamePlay: //게임중일때
	{
		//체크 중일때는 false반환
		if (checking)
			return false;

		for (auto& card : m_cards)
		{
			//클릭한 뒷면 카드 영역
			if (card.ColliderCheck(point))
			{
				rev_count++;
				//1일때 
				if (rev_count == 1)
				{
					first = &card;
				}
				//count가 2가 될시 second에 값을 넣고 first와 second를 비교한다
				else if (rev_count == 2)
				{
					second = &card;
					checking = true;
					CardCheck();
				}

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

void GameManager::CardCheck()
{
	//첫카드와 둘째카드 비교해서 같지 않다면 둘다 뒷면으로변경
	//같으면 그냥 냅두고 포인터와 횟수 초기화만 
	if (first->GetIndex() != second->GetIndex())
	{
		SetTimer(m_hWnd, 1, 2000, NULL);
	}
	//같은 경우의 로직. 여기서 finish_count를 늘려보자
	else
	{
		finish_count++;
		rev_count = 0;
		checking = false;

		//if (finish_count == m_cards.size() / 2)
		//{
		//	m_state = MainMenu;
		//	Init(m_hWnd);
		//	//InvalidateRect(m_hWnd, NULL, TRUE);
		//}

		if (finish_count == m_cards.size() / 2)
		{
			isWin = true;
			m_state = GameEnd;
			SetTimer(m_hWnd, 3, 5000, NULL);
			
			/*m_state = MainMenu;
			Init(m_hWnd);*/
			//InvalidateRect(m_hWnd, NULL, TRUE);
		}
	}
}

void GameManager::DestroyTimer()
{
	//1번 타이머 해제 후 카드들 다시 뒷면으로. count 초기화.
	KillTimer(m_hWnd, 1);
	first->ChangeRear();
	second->ChangeRear();
	rev_count = 0;
	checking = false;

	/*if (finish_count == m_cards.size() / 2)
	{
		m_state = MainMenu;
		Init(m_hWnd);
	}*/

	InvalidateRect(m_hWnd, NULL, TRUE);
}

void GameManager::UpdateTimer()
{
	//게임 플레이 중이면서. 호출될 때마다 타이머 감소.
	//타이머가 0가 되면 게임종료.
	if (m_state == GamePlay)
	{
		timelimit--;
		if (timelimit <= 0)
		{
			m_state = GameEnd;
			//SetTimer(m_hWnd, 3, 2000, NULL);
			SetTimer(m_hWnd, 3, 5000, NULL);
		}
		InvalidateRect(m_hWnd, NULL, TRUE);
	}
}

void GameManager::ResetData()
{
}

GameManager::~GameManager()
{

}