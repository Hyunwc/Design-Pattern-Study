#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	//Main���� ���� ����
	m_hWnd = hWnd;
	//��Ʈ�� �迭�� �̹��� ��� �ִ� �۾�.
	BitMapManager::GetInstance()->Init(m_hWnd);
	m_state = MainMenu;
	//�׽�Ʈ�� ��Ʈ ����(���߿� ���� �� ����)
	testrect.left = 300;
	testrect.top = 350;
	testrect.right = 500;
	testrect.bottom = 400;
}

void GameManager::Draw(HDC hdc)
{

	// Rectangle�Լ� �̿�(hdc, left, top, right, bottom���� 4���� �Ű�����)
	// left �簢�� ���� x right �簢�� ������ x 

	// ���� ���� ���¿� ���� �ٸ� �׷����� ���
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
	//üũ�� �簢���� ������ x,y(����� ��ġ)�� �Ű�������.
	if (PtInRect(&testrect, point))
	{
		return true;
	}
	return false;
}




GameManager::~GameManager()
{
	
}