#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	//Main에서 보낼 예정
	m_hWnd = hWnd;
	//비트맵 배열에 이미지 경로 넣는 작업.
	BitMapManager::GetInstance()->Init(m_hWnd);
	//m_card.Init(IMAGE_CHICKEN, 100, 50);
	
	//초기 설정 후 메뉴호출
	//Menu();
}




GameManager::~GameManager()
{
	
}