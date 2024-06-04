#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	//Main���� ���� ����
	m_hWnd = hWnd;
	first = nullptr;
	second = nullptr;
	checking = false;
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
	//IMAGE_DOG���� �����ؼ� 10���� �̹����� �߰�.
	//�� �徿 �����ϴ� �� ���� �߰�.
	for (int i = 0; i < 10; i++)
	{
		//������ ���� ������ ������ ��ȯ
		images.push_back(static_cast<IMAGE>(i));
		images.push_back(static_cast<IMAGE>(i));
	}
	//�ε��� ����
	random_shuffle(images.begin(), images.end());

	int index = 0;
	// 5x4 ī�� ��ġ
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Card card;
			// ī�� ��ġ ���
			// (100,100) (210, 100) (320, 100) (430, 100) (540, 100)

			int x = xStart + j * (CARD_WIDTH + X_SPACING);
			int y = yStart + i * (CARD_HEIGHT + Y_SPACING);

			//ī���� �ε���, �׷��� x, y��ǥ
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
		//�� �ڿ� �Ķ���ʹ� ���ڿ��� ����
		TextOut(hdc, 350, 365, TEXT("StartGame"), 9);
		Rectangle(hdc, 300, 450, 500, 500);
		TextOut(hdc, 350, 465, TEXT("EndGame"), 7);
		break;
	}
	//���� �÷���
	case GamePlay:
	{
		//���Ϳ� ����� ī��� Draw() ȣ��
		for (auto& card : m_cards)
		{
			card.Draw(hdc);
		}

		//ī�带 �׸��� ���� ���⼭ ����¦���� üũ�� �ϴ� �Լ��� ȣ���ؾ� �ҵ�
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


//�Ű����� : Ŭ���� ���� x,y��ǥ�� �޾ƿ�
bool GameManager::CheckCollide(POINT point)
{
	//m_state�� ���¿� ���� 
	switch (m_state)
	{
	case MainMenu: //����
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
		break;
	}
	case GamePlay: //�������϶�
	{
		if (checking) return false; //ī�� üũ ���϶� false��ȯ
		
		for (auto& card : m_cards)
		{
			//Ŭ���� �޸� ī�� ����
			if (card.ColliderCheck(point))
			{
				rev_count++;
				//1�϶� 
				if (rev_count == 1)
				{
					first = &card;
				}
				//count�� 2�� �ɽ� second�� ���� �ְ� first�� second�� ���Ѵ�
				else if (rev_count == 2)
				{
					second = &card;
					checking = true;
					SetTimer(m_hWnd, 1, 2000, NULL);
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
	//InvalidateRect(m_hWnd, NULL, TRUE);
	//ùī��� ��°ī�� ���ؼ� ���� �ʴٸ� �Ѵ� �޸����κ���
	//������ �׳� ���ΰ� �����Ϳ� Ƚ�� �ʱ�ȭ�� 
	
	if (first->GetIndex() != second->GetIndex())
	{
		first->ChangeRear();
		second->ChangeRear();
	}	
	
	//first = nullptr;
	//second = nullptr;
	rev_count = 0;
}

void GameManager::HandleTimer()
{
	//üŷ�� Ʈ���϶�
	if (checking)
	{
		CardCheck(); //ī�� �˻�
		InvalidateRect(m_hWnd, NULL, TRUE);
		checking = false;
	}
}




GameManager::~GameManager()
{

}