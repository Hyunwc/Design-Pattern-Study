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
	startRect.left = 300;
	startRect.top = 350;
	startRect.right = 500;
	startRect.bottom = 400;

	endRect.left = 300;
	endRect.top = 450;
	endRect.right = 500;
	endRect.bottom = 500;

	// ī�� ���ݰ� ũ�� ����
	const int CARD_WIDTH = 100;
	const int CARD_HEIGHT = 150;
	const int X_SPACING = 10;
	const int Y_SPACING = 10;

	// ù ��° ī���� ��ġ
	int xStart = 100;
	int yStart = 100;

	// �̹��� �迭
	vector<IMAGE> images;
	for (int i = 0; i < 10; i++)
	{
		images.push_back(static_cast<IMAGE>(i));
		images.push_back(static_cast<IMAGE>(i));
	}
	random_shuffle(images.begin(), images.end());

	int index = 0;
	// 4x5 ī�� ��ġ
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Card card;
			// ī�� ��ġ ���
			int x = xStart + j * (CARD_WIDTH + X_SPACING);
			int y = yStart + i * (CARD_HEIGHT + Y_SPACING);
			card.Init(images[index], x, y);
			m_cards.push_back(card);
			
			index++;
		}
	}
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
		TextOut(hdc, 350, 365, TEXT("StartGame"), 10);
		Rectangle(hdc, 300, 450, 500, 500);
		TextOut(hdc, 350, 465, TEXT("EndGame"), 8);
		break;
	}
	//���� �÷���
	case GamePlay:
	{
		//���Ϳ� ����� ī��� ȣ��
		for (auto& card : m_cards)
		{
			card.Draw(hdc);
		}
		break;
	}
	
	case GameOver:
	{
		TextOut(hdc, 350, 365, TEXT("Game OVer"), 9);
		break;
	}
	
	default:
		break;
	}

}

bool GameManager::CheckCollide(POINT point)
{
	if (m_state == MainMenu)
	{
		//üũ�� �簢���� ������ x,y(����� ��ġ)�� �Ű�������. (startRect����)
		if (PtInRect(&startRect, point))
		{
			//���� �÷��� ���·� ����
			m_state = GamePlay;
			
			return true;
		}
		else if (PtInRect(&endRect, point))
		{
			m_state = GameOver;
			return true;
		}
	}
	else if (m_state == GamePlay)
	{
		
	}
	
	return false;
}

GameManager::~GameManager()
{
	
}