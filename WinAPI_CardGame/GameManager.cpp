#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

void GameManager::Init(HWND hWnd)
{
	//Main���� ���� ����
	m_hWnd = hWnd;
	first = nullptr;
	second = nullptr;
	timelimit = 60;
	finish_count = 0;
	isWin = false;
	m_cards.clear();
	//��Ʈ�� �迭�� �̹��� ��� �ִ� �۾�.
	BitMapManager::GetInstance()->Init(m_hWnd);
	m_background = BitMapManager::GetInstance()->GetImage(IMAGE_BACKGROUND);
	//m_bitmap = BitMapManager::GetInstance()->GetTest();
	m_state = MainMenu;

	int windowWidth = 800;
	int windowHeight = 800;
	int btnWidth = 200;
	int btnHeight = 50;
	

	//(800 - 200) / 2 = 300
	startRect.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	//(800 - 50) / 2 - 50 = 325
	startRect.top = (WINDOW_HEIGHT - BUTTON_HEIGHT) / 2 - 50;
	//300 + 200 = 500
	startRect.right = startRect.left + BUTTON_WIDTH;
	//325 + 50 = 375
	startRect.bottom = startRect.top + BUTTON_HEIGHT;

	endRect.left = startRect.left;
	endRect.top = startRect.bottom + BUTTON_HEIGHT;
	endRect.right = startRect.right;
	endRect.bottom = endRect.top + BUTTON_HEIGHT;

	// ī�� ���ݰ� ũ�� ����
	/*const int CARD_WIDTH = 100;
	const int CARD_HEIGHT = 150;
	const int X_SPACING = 10;
	const int Y_SPACING = 10;*/

	// ù ��° ī���� ��ġ
	int xStart = 120;
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

			int x = xStart + j * (CARD_WIDTH + SPACING);
			int y = yStart + i * (CARD_HEIGHT + SPACING);

			//ī���� �ε���, �׷��� x, y��ǥ
			card.Init(images[index], x, y);
			m_cards.push_back(card);
			index++;
		}

	}

	//���ѽð��� ���� Ÿ�̸�
	SetTimer(m_hWnd, 2, 1000, NULL);
}

void GameManager::Draw(HDC hdc)
{
	m_background->Draw(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	// Rectangle�Լ� �̿�(hdc, left, top, right, bottom���� 4���� �Ű�����)
	// left �簢�� ���� x right �簢�� ������ x 

	// ���� ���� ���¿� ���� �ٸ� �׷����� ���
	switch (m_state)
	{
	case MainMenu:
	{
		
		//BitMapManager::GetInstance()->GetBackground()->BackGroundDraw(hdc, 0, 0);
		//left, top, right, bottom
		Rectangle(hdc, startRect.left, startRect.top, startRect.right, startRect.bottom);
		//�� �ڿ� �Ķ���ʹ� ���ڿ��� ����
		TextOut(hdc, 370, 340, TEXT("StartGame"), 9);
		Rectangle(hdc, endRect.left, endRect.top, endRect.right, endRect.bottom);
		TextOut(hdc, 370, 440, TEXT("EndGame"), 7);
		break;
	}
	//���� �÷���
	case GamePlay:
	{
		HFONT font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0,
			HANGEUL_CHARSET, 0, 0, 0, 0, L"�ü�");
		HFONT oldfont = (HFONT)SelectObject(hdc, font);
		SetBkMode(hdc, TRANSPARENT);
		//���Ϳ� ����� ī��� Draw() ȣ��
		for (auto& card : m_cards)
		{
			card.Draw(hdc);
		}

		char g_buf[256];
		char c_buf[256];
		sprintf_s(g_buf,  "%d : %d", 0, timelimit);
		sprintf_s(c_buf,  "finish : %d / %d", finish_count, m_cards.size() / 2);
		TextOutA(hdc, 350, 20, g_buf, strlen(g_buf));
		TextOutA(hdc, 550, 20, c_buf, strlen(c_buf));

		//���ѽð��� 10�� �̸��� ��� ���������� ��µǰ� 
		if (timelimit < 10)
		{
			SetTextColor(hdc, RGB(255, 0, 0));
			TextOutA(hdc, 350, 20, g_buf, strlen(g_buf));
		}

		
		SelectObject(hdc, oldfont);
		DeleteObject(font);
		//ī�带 �׸��� ���� ���⼭ ����¦���� üũ�� �ϴ� �Լ��� ȣ���ؾ� �ҵ�
		break;
	}

	case GameEnd:
	{
		HFONT font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0,
			HANGEUL_CHARSET, 0, 0, 0, 0, L"�ü�");
		HFONT oldfont = (HFONT)SelectObject(hdc, font);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 170, 360, TEXT("5�� �ڿ� ���� �޴��� �̵��մϴ�."), 19);

		if (isWin)
			TextOut(hdc, 350, 400, TEXT("Win!"), 4);
		else
			TextOut(hdc, 350, 400, TEXT("Lose!"), 5);

		SelectObject(hdc, oldfont);
		DeleteObject(font);

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
			PostQuitMessage(0);
			//return true;
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

		if (finish_count == m_cards.size() / 2)
		{
			isWin = true;
			m_state = GameEnd;
			SetTimer(m_hWnd, 3, 5000, NULL);
		}
	}
}

void GameManager::DestroyTimer()
{
	//1�� Ÿ�̸� ���� �� ī��� �ٽ� �޸�����. count �ʱ�ȭ.
	KillTimer(m_hWnd, 1);
	first->ChangeRear();
	second->ChangeRear();
	rev_count = 0;
	checking = false;

	/*if (finish_count == m_cards.size() / 2)
	{
		m_state = MainMenu;
		Init(m_hWnd);
	}*/

	InvalidateRect(m_hWnd, NULL, TRUE);
}

void GameManager::UpdateTimer()
{
	//���� �÷��� ���̸鼭. ȣ��� ������ Ÿ�̸� ����.
	//Ÿ�̸Ӱ� 0�� �Ǹ� ��������.
	if (m_state == GamePlay)
	{
		timelimit--;
		if (timelimit <= 0)
		{
			m_state = GameEnd;
			//SetTimer(m_hWnd, 3, 2000, NULL);
			SetTimer(m_hWnd, 3, 5000, NULL);
		}
		InvalidateRect(m_hWnd, NULL, TRUE);
	}
}

void GameManager::ResetData()
{
}

GameManager::~GameManager()
{

}