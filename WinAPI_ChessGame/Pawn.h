#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(int x, int y);
	void Init(int x, int y) override;
	void Draw(HDC hdc) override;
};
