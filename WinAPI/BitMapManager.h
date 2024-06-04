#pragma once
#include"BitMap.h"
#include<vector>

enum IMAGE
{
	IMAGE_START,
	IMAGE_DOG,
	IMAGE_TIGER,
	IMAGE_DUCK,
	IMAGE_ELEPHANT,
	IMAGE_COW,
	IMAGE_HORSE,
	IMAGE_CAT,
	IMAGE_MONKEY,
	IMAGE_FROG,
	IMAGE_CHICKEN,
	IMAGE_BLACK,
	IMAGE_END
};

class BitMapManager
{
private:
	BitMap* m_parrBitMap;
	//ΩÃ±€≈Ê 
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
	//¿ÃπÃ¡ˆ ¿Œµ¶Ω∫ π›»Ø
	BitMap* GetImage(IMAGE index)
	{
		return &m_parrBitMap[index];
	}
	
	void Init(HWND hWnd);
	~BitMapManager();
};

