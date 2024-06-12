#pragma once
#include "BitMap.h"
#include "BitMapManager.h"


class GameManager
{
private:
	static GameManager* instance;
	HWND m_hWnd;
	HDC m_hdc;

	GameManager();
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

	void Init(HWND hWnd, HDC hdc);
};
