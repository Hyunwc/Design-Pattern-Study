#include "GameManager.h"



void GameManager::Init()
{
	//��Ʈ�� �迭�� �̹��� ��� �ִ� �۾����� �����ؾ���.
	BitMapManager::GetInstance()->Init(hWnd);
	m_card.Init(IMAGE_CHICKEN, 100, 50);
	//�ʱ� ���� �� �޴�ȣ��
	Menu();
}

void GameManager::Menu()
{
	//��� �̹����� ȭ�� �߾ӿ� 2���� �簢���� �׷�
	//��Ŭ���� �� ������ �����ϰ�. Start�� GamePlay() Exit�� ����.

}

GameManager::~GameManager()
{
	
}