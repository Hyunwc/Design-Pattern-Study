#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(int x, int y);
	void Init(int x, int y) override;
	void Draw(HDC hdc) override;
};
