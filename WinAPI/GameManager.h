#pragma once
//#include "BitMap.h"
//#include "BitMapManager.h"
#include "Card.h"

class GameManager
{
private:
	Card m_card;
	HWND m_hWnd;
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
	
};

