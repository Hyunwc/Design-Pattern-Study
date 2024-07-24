#include "BitMap.h"



BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc, char* FileName, IMAGE type)
{
	MemDC = CreateCompatibleDC(hdc); //���� �����
	m_BitMap = (HBITMAP)LoadImageA(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	SelectObject(MemDC, m_BitMap);
	BITMAP BitMap_Info;
	GetObject(m_BitMap, sizeof(BitMap_Info), &BitMap_Info);
	m_Size.cx = BitMap_Info.bmWidth;
	m_Size.cy = BitMap_Info.bmHeight;
	m_image = type;
}

void BitMap::Draw(HDC hdc, int x, int y)
{
	TransparentBlt(hdc, x, y, 75, 75, MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
}

void BitMap::AlphaDraw(HDC hdc, int x, int y)
{
	BLENDFUNCTION bf;
	ZeroMemory(&bf, sizeof(bf));
	bf.SourceConstantAlpha = 100;
	AlphaBlend(hdc, x, y, 75, 75, MemDC, 0, 0, m_Size.cx, m_Size.cy, bf);
	//StretchBlt(hdc, x, y, 75, 75, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
}

BitMap::~BitMap()
{
	DeleteObject(m_BitMap);
	DeleteDC(MemDC);
}
