#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
	m_parrBitMap = new BitMap[IMAGE_END];
	m_tile = new BitMap;
}

void BitMapManager::Init(HWND hWnd)
{
	char buf[256];
	HDC hdc = GetDC(hWnd);
	for (int i = IMAGE_START; i < IMAGE_END; i++)
	{
		sprintf_s(buf, "RES//block0%d.bmp", i);
		m_parrBitMap[i].Init(hdc, buf, static_cast<IMAGE>(i));
	}

	sprintf_s(buf, "RES//MoveableTileMask.bmp");
	m_tile->Init(hdc, buf, IMAGE_MOVETILE);

	ReleaseDC(hWnd, hdc);
}

BitMapManager::~BitMapManager()
{
	delete[] m_parrBitMap;
	delete m_tile;
}
