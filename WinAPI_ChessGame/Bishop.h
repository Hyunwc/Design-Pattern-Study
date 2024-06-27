#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(int x, int y);
	void Init(int x, int y) override;
	void Draw(HDC hdc) override;
};
