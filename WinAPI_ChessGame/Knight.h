#pragma once
#include "Piece.h"
#include "GameManager.h"

class Knight : public Piece
{
public:
	Knight(int x, int y, IMAGE index, PIECE_COLOR color);
	void Init(int x, int y) override;
	void Draw(HDC hdc) override;
	vector<RECT> RouteNav() override;
	void RouteDraw(HDC hdc) override;
	bool IsMoveable(RECT rect) override;
	void Test(RECT temp, int w, int h);
};
