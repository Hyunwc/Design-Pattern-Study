#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(int x, int y, IMAGE index);
	void Init(int x, int y) override;
	void Draw(HDC hdc) override;
};
