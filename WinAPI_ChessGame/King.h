#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King(int x, int y, IMAGE index);
	void Init(int x, int y) override;
	void Draw(HDC hdc) override;
};