#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	//Main���� ���� ����
	m_hWnd = hWnd;
	//��Ʈ�� �迭�� �̹��� ��� �ִ� �۾�.
	BitMapManager::GetInstance()->Init(m_hWnd);
	//m_card.Init(IMAGE_CHICKEN, 100, 50);
	
	//�ʱ� ���� �� �޴�ȣ��
	//Menu();
}




GameManager::~GameManager()
{
	
}