#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King(int x, int y, IMAGE index, PIECE_COLOR color);
	void Init(int x, int y) override;
	void Draw(HDC hdc) override;
	vector<RECT> RouteNav() override;
	void RouteDraw(HDC hdc) override;
};