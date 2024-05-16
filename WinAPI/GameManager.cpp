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
	testrect.left = 300;
	testrect.top = 350;
	testrect.right = 500;
	testrect.bottom = 400;
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
		Rectangle(hdc, 300, 450, 500, 500);
	}
	case GamePlay:
	{

	}
	case GameOver:
	{

	}
	default:
		break;
	}

}

bool GameManager::CheckCollide(POINT point)
{
	//체크할 사각형의 영역과 x,y(대상의 위치)를 매개변수로.
	if (PtInRect(&testrect, point))
	{
		return true;
	}
	return false;
}




GameManager::~GameManager()
{
	
}