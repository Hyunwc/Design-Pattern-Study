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
		//게임매니저에서 비트맵 매니저 관리하니 게임매니저에서 비트맵 매니저 해제
		BitMapManager::Release();
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void Init(HWND hWnd); //초기화
	void Draw(HDC hdc); 
	bool CheckCollide(POINT point);
	
};

