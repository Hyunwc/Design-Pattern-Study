#pragma once
#include"BitMap.h"
#include<vector>

enum IMAGE
{
	IMAGE_START,
	IMAGE_BLCAKMAGICIAN = 0,
	IMAGE_BLUEEYES,
	IMAGE_EXODIA,
	IMAGE_SHININGFLAREWINGMAN,
	IMAGE_E_HERO_NEOS,
	IMAGE_OBELISK,
	IMAGE_OSIRIS,
	IMAGE_RA,
	IMAGE_REDEYES,
	IMAGE_STARDUST,
	IMAGE_BLACK,
	IMAGE_BACKGROUND,

	IMAGE_END,
};

class BitMapManager
{
private:
	BitMap* m_parrBitMap;
	//�̱��� 
	static BitMapManager* m_hThis;
	BitMapManager();
public:
	static BitMapManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new BitMapManager;
		return m_hThis;
	}
	static void Release()
	{
		if (m_hThis)
		{
			delete m_hThis;
			m_hThis = nullptr;
		}
	}
	//�̹��� �ε��� ��ȯ
	BitMap* GetImage(IMAGE index)
	{
		return &m_parrBitMap[index];
	}

	BitMap* GetTest()
	{
		return &m_parrBitMap[IMAGE_END];
	}

	
	void Init(HWND hWnd);
	~BitMapManager();
};

