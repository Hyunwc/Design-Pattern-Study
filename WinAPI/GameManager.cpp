#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	//Main에서 보낼 예정
	m_hWnd = hWnd;
	//비트맵 배열에 이미지 경로 넣는 작업.
	BitMapManager::GetInstance()->Init(m_hWnd);
	m_state = MainMenu;
	//테스트용 렉트 영역(나중에 수정 할 예정)
	startRect.left = 300;
	startRect.top = 350;
	startRect.right = 500;
	startRect.bottom = 400;

	endRect.left = 300;
	endRect.top = 450;
	endRect.right = 500;
	endRect.bottom = 500;

	// 카드 간격과 크기 정의
	const int CARD_WIDTH = 100;
	const int CARD_HEIGHT = 150;
	const int X_SPACING = 10;
	const int Y_SPACING = 10;

	// 첫 번째 카드의 위치
	int xStart = 100;
	int yStart = 100;

	// 이미지 배열
	vector<IMAGE> images;
	for (int i = 0; i < 10; i++)
	{
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
		//left, top, right, bottom
		Rectangle(hdc, 300, 350, 500, 400);
		//맨 뒤에 파라미터는 문자열의 길이
		TextOut(hdc, 350, 365, TEXT("StartGame"), 9);
		Rectangle(hdc, 300, 450, 500, 500);
		TextOut(hdc, 350, 465, TEXT("EndGame"), 7);
		break;
	}
	//게임 플레이
	case GamePlay:
	{
		//벡터에 저장된 카드들 호출
		for (auto& card : m_cards)
		{
			card.Draw(hdc);
		}
		break;
	}
	
	case GameOver:
	{
		TextOut(hdc, 350, 365, TEXT("Game Over"), 9);
		break;
	}
	
	default:
		break;
	}

}

//매개변수 : 클릭한 곳의 x,y좌표를 받아옴
bool GameManager::CheckCollide(POINT point)
{
	//메인메뉴
	if (m_state == MainMenu)
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
			m_state = GameOver;
			return true;
		}
	}
	//게임중 일때
	else if (m_state == GamePlay)
	{
		//체크할 사각형의 영역(카드의 영역)과, 대상의 위치.
		//조건과 일치할시 카드의 상태를 바꿔야함.
		if (PtInRect(m_cards[0].GetBitMapRect(), point))
		{
			m_cards[0].SetState();
			return true;
		}
	}
	
	return false;
}

GameManager::~GameManager()
{
	
}