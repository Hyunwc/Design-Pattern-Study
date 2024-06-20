#pragma once
#include "BitMap.h"
#include "BitMapManager.h"
#include "Board.h"

#define XSTART 0
#define YSTART 0

class GameManager
{
private:
	static GameManager* instance;
	//테스트용
	BitMap* m_tile1;
	BitMap* m_tile2;
	vector<Board> m_boards;
	HWND m_hWnd;
	HDC m_hdc;

	GameManager(){}
public:
	~GameManager();
	static GameManager* Instance()
	{
		if (instance == nullptr) instance = new GameManager;
		return instance;
	}
	static void Release()
	{
		BitMapManager::Release();
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void Init(HWND hWnd);
	void Draw(HDC hdc);
};
