#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(int x, int y, IMAGE index);
	void Init(int x, int y) override;
	void Draw(HDC hdc) override;
};