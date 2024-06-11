#pragma once
#include "BitMap.h"
#include "BitMapManager.h"
#include "Card.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <Windows.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define CARD_WIDTH 100
#define CARD_HEIGHT 150
#define SPACING 10

enum GameState
{
	MainMenu,
	GamePlay,
	GameEnd
};

class GameManager
{
private:
	vector<Card> m_cards; //ī�带 ���� ����
	HWND m_hWnd; //�ڵ�
	GameState m_state; //���� ���� ����
	RECT startRect, endRect; //���ζ� ����� �簢�� ������
	BitMap* m_background;
	static GameManager* instance;
	//��� �׽�Ʈ������ ����� ������ 
	Card* first;
	Card* second;
	int rev_count = 0;
	int finish_count = 0;
	int timelimit = 60;
	bool checking; //ī�� üũ���� �� Ŭ���� ���� �ʰ� �ϱ� ���� ����
	bool isWin; 
	GameManager() {}
public:
	~GameManager();
	static GameManager* Instance()
	{
		if (instance == nullptr) instance = new GameManager;
		return instance;
	}
	static void Release()
	{
		//���ӸŴ������� ��Ʈ�� �Ŵ��� �����ϴ� ���ӸŴ������� ��Ʈ�� �Ŵ��� ����
		BitMapManager::Release();
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void Init(HWND hWnd); //�ʱ�ȭ
	void Draw(HDC hdc);
	int GetRevCount() { return rev_count; }
	void SetState(GameState state) { m_state = state; }
	bool CheckCollide(POINT point);
	void CardCheck();
	void DestroyTimer();
	void UpdateTimer();
	void ResetData(); //��� ������ �ʱ� ���·�
};

