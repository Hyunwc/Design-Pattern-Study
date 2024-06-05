#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	//Main���� ���� ����
	m_hWnd = hWnd;
	first = nullptr;
	second = nullptr;
	timelimit = 60;
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

	SetTimer(m_hWnd, 2, 1000, NULL);
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
		char g_buf[256];
		char c_buf[256];
		sprintf_s(g_buf,  "%d : %d", 0, timelimit);
		sprintf_s(c_buf,  "finish : %d", finish_count);
		TextOutA(hdc, 350, 10, g_buf, strlen(g_buf));
		TextOutA(hdc, 700, 10, c_buf, strlen(c_buf));
		//ī�带 �׸��� ���� ���⼭ ����¦���� üũ�� �ϴ� �Լ��� ȣ���ؾ� �ҵ�
		break;
	}

	case GameEnd:
	{
		TextOut(hdc, 10, 10, TEXT("Game Over"), 9);
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
			m_state = GameEnd;
			return true;
		}
		break;
	}
	case GamePlay: //�������϶�
	{
		//üũ ���϶��� false��ȯ
		if (checking)
			return false;

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
					CardCheck();
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
	if (finish_count == m_cards.size() / 2)
	{
		m_state = MainMenu;
		system("pause");
		InvalidateRect(m_hWnd, NULL, TRUE);
		return;
	}
	//ùī��� ��°ī�� ���ؼ� ���� �ʴٸ� �Ѵ� �޸����κ���
	//������ �׳� ���ΰ� �����Ϳ� Ƚ�� �ʱ�ȭ�� 
	if (first->GetIndex() != second->GetIndex())
	{
		SetTimer(m_hWnd, 1, 2000, NULL);
	}
	//���� ����� ����. ���⼭ finish_count�� �÷�����
	else
	{
		finish_count++;
		rev_count = 0;
		checking = false;
	}
}

void GameManager::DestroyTimer()
{
	KillTimer(m_hWnd, 1);
	first->ChangeRear();
	second->ChangeRear();
	rev_count = 0;
	checking = false;

	if (finish_count == m_cards.size() / 2)
	{
		m_state = MainMenu;
	}

	InvalidateRect(m_hWnd, NULL, TRUE);
}

void GameManager::UpdateTimer()
{
	if (m_state == GamePlay)
	{
		timelimit--;
		if (timelimit <= 0)
		{
			m_state = GameEnd;
		}
		InvalidateRect(m_hWnd, NULL, TRUE);
	}
}

GameManager::~GameManager()
{

}