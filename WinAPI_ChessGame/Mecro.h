#pragma once

#include <vector>
#include <time.h>
#include <Windows.h>
using namespace std;

enum PIECE_COLOR
{
	PIECE_COLOR_BLACK = 0,
	PIECE_COLOR_WHITE
};

struct Position
{
	int m_ix;
	int m_iy;
};

struct Size
{
	int m_iWidth;
	int m_iHeight;
};
