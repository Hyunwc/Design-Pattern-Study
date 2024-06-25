#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(int x, int y);
	void Draw(HDC hdc) override;
};
