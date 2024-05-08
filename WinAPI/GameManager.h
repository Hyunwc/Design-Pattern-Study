#pragma once
#include "BitMap.h"
#include "BitMapManager.h"
#include "Card.h"

class GameManager
{
private:
	static GameManager* instance;
	BitMap m_bitmap;
	Card m_card;
	
	GameManager(){}
public:
	~GameManager(){}
	static GameManager* Instance()
	{
		if (nullptr == instance) instance == new GameManager;
		return instance;
	}
	static void Release()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void Init(); //�ʱ�ȭ
	void Menu(); //���θ޴�
};

GameManager* GameManager::instance = nullptr;