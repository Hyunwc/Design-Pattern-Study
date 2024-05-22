#include "BitMap.h"



BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc,char* FileName)
{
	MemDC = CreateCompatibleDC(hdc); //���� �����.
	//���� ���ҽ�, �̹������, ��Ʈ��, �����̹���ũ��, �÷���
	m_BitMap = (HBITMAP)LoadImageA(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	//�׿� ��ũ�� ���.
	SelectObject(MemDC, m_BitMap);
	BITMAP BitMap_Info;
	//�ش������Ʈ�� �ڵ��� �Ѱ��ְ� ������ �޾ƿ� ���⼱ ��Ʈ����
	GetObject(m_BitMap, sizeof(BitMap_Info), &BitMap_Info);
	m_Size.cx = BitMap_Info.bmWidth;
	m_Size.cy = BitMap_Info.bmHeight;
}
void BitMap::Draw(HDC hdc, int x, int y)
{
	//ũ�� ������ ������ �̹���.
	//ȭ��� ��ǥ, ȭ��� �׷����� �ʺ� ����, ���� �̹��� xy��ǥ, 
	StretchBlt(hdc, x, y, m_Size.cx / 2, m_Size.cy / 2, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
}

BitMap::~BitMap()
{
	DeleteObject(m_BitMap);
	DeleteDC(MemDC);
}
