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
		//벡터에 저장된 카드들 Draw() 호출
		for (auto& card : m_cards)
		{
			card.Draw(hdc);
		}

		//카드를 그리고 나서 여기서 같은짝인지 체크를 하는 함수를 호출해야 할듯
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

//충돌 체크가 되어 들어오게되는 함수
void GameManager::CardCheck(CARD first, CARD second)
{

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
		//조건과 일치할시 카드의 상태를 바꿔야함
		for (auto& card : m_cards)
		{
			if (PtInRect(card.GetBitMapRect(), point))
			{
				//해당 영역의 상태가 End면 false 반환
				if (card.GetState() == CARD_END)
					return false;

				//뒤집기 카운트 1일시 첫번째 enum값 받아오고
				//State에 false를 보낸다.false일시 앞 뒤 뒤집기만.
				if (rev_count == 1)
				{
					firstEnum = card.GetIndex();
					card.SetState(false);
					return true;
				}
				else if (rev_count == 2)
				{
					secondEnum = card.GetIndex();
					//처음과 두번째의 enum값이 같으면 true를 보내주어 end상태로 만든다.
					if (firstEnum == secondEnum)
						card.SetState(true);
					else
						card.SetState(false);

					rev_count = 0;
					return true;
				}
			}
		}
		
	}
	
	return false;
}

GameManager::~GameManager()
{
	
}