#include "BitMap.h"



BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc,char* FileName)
{
	MemDC = CreateCompatibleDC(hdc); //붓을 만드는.
	//독립 리소스, 이미지경로, 비트맵, 원본이미지크기, 플래그
	m_BitMap = (HBITMAP)LoadImageA(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	//붓에 잉크를 찍는.
	SelectObject(MemDC, m_BitMap);
	BITMAP BitMap_Info;
	//해당오브젝트의 핸들을 넘겨주고 정보를 받아옴 여기선 비트맵을
	GetObject(m_BitMap, sizeof(BitMap_Info), &BitMap_Info);
	m_Size.cx = BitMap_Info.bmWidth;
	m_Size.cy = BitMap_Info.bmHeight;
}
void BitMap::Draw(HDC hdc, int x, int y)
{
	//크기 변경이 가능한 이미지.
	//화면상 좌표, 화면상에 그려지는 너비 높이, 원본 이미지 xy좌표, 
	//StretchBlt(hdc, x, y, m_Size.cx / 2, m_Size.cy / 2, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
	//테스트용
	StretchBlt(hdc, x, y, 100, 150, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
}

//x랑 y는 화면에 그려질 시작 좌표 
//배경화면 Draw할 함수
void BitMap::Draw(HDC hdc, int x, int y, int w, int h)
{
	//크기 변경이 가능한 이미지.
	//화면상 좌표, 화면상에 그려지는 너비 높이, 원본 이미지 xy좌표, 
	
	StretchBlt(hdc, x, y, w, h, MemDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
}


BitMap::~BitMap()
{
	DeleteObject(m_BitMap);
	DeleteDC(MemDC);
}
