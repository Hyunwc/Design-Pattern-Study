#pragma once
//#include "BitMap.h"
//#include "BitMapManager.h"
#include "Card.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <Windows.h>

enum GameState
{
	MainMenu,
	GamePlay,
	GameOver
};

class GameManager
{
private:
	vector<Card> m_cards; //ī�带 ���� ����
	HWND m_hWnd; //�ڵ�
	GameState m_state; //���� ���� ����
	RECT startRect, endRect; //���ζ� ����� �簢�� ������
	static GameManager* instance;
	//��� �׽�Ʈ������ ����� ������ 
	Card* first;
	Card* second;
	int rev_count = 0;
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
	void PlusCheckCount() { rev_count++; }
	bool CheckCollide(POINT point);

};

