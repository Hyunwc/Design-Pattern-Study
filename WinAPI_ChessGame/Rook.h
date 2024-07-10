#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(int x, int y, IMAGE index, PIECE_COLOR color);
	void Init(int x, int y) override;
	void Draw(HDC hdc) override;
	void RouteNav() override;
	void RouteDraw(HDC hdc) override;
};