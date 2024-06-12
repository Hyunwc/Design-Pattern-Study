#include "GameManager.h"



void GameManager::Init(HWND hWnd, HDC hdc)
{
}

GameManager::~GameManager()
{
	DeleteDC(m_hdc);
}
