#include "GameManager.h"



void GameManager::Init()
{
	//비트맵 배열에 이미지 경로 넣는 작업부터 수행해야함.
	BitMapManager::GetInstance()->Init(hWnd);
	m_card.Init(IMAGE_CHICKEN, 100, 50);
	//초기 설정 후 메뉴호출
	Menu();
}

void GameManager::Menu()
{
	//배경 이미지와 화면 중앙에 2개의 사각형을 그려
	//좌클릭시 각 역할을 수행하게. Start는 GamePlay() Exit는 종료.

}

GameManager::~GameManager()
{
	
}