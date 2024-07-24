#pragma once
#include <Windows.h>
#pragma comment(lib, "msimg32.lib")
using namespace std;
enum IMAGE
{
	IMAGE_START,

	IMAGE_BLACK_PAWN = 0,
	IMAGE_BLACK_KNIGHT,
	IMAGE_BLACK_BISHOP,
	IMAGE_BLACK_ROOK,
	IMAGE_BLACK_QUEEN,
	IMAGE_BLACK_KING,

	IMAGE_WHITE_PAWN,
	IMAGE_WHITE_KNIGHT,
	IMAGE_WHITE_BISHOP,
	IMAGE_WHITE_ROOK,
	IMAGE_WHITE_QUEEN,
	IMAGE_WHITE_KING,

	IMAGE_TILE1,
	IMAGE_TILE2,
	IMAGE_MOVETILE,
	IMAGE_END
};

class BitMap
{
private:
	HDC MemDC;
	HBITMAP m_BitMap;
	SIZE m_Size;
	IMAGE m_image;
public:
	void Init(HDC hdc, char* FileName, IMAGE type);
	void Draw(HDC hdc, int x, int y);
	void AlphaDraw(HDC hdc, int x, int y);

	inline SIZE GetSize()
	{
		return m_Size;
	}

	RECT* GetRect(int x, int y)
	{
		RECT rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + 75;
		rect.bottom = y + 75;
		return &rect;
	}
	IMAGE GetImage() { return m_image; }
	BitMap();
	~BitMap();
};
