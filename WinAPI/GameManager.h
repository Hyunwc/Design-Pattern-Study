#pragma once
//#include "BitMap.h"
//#include "BitMapManager.h"
#include "Card.h"

enum GameState
{
	MainMenu,
	GamePlay,
	GameOver
};

class GameManager
{
private:
	Card m_card;
	HWND m_hWnd;
	GameState m_state;
	RECT testrect;
	static GameManager* instance;
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
	bool CheckCollide(POINT point);
	
};

