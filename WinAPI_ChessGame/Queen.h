#pragma once
#include "Piece.h"
#include "GameManager.h"

class Queen : public Piece
{
public:
	Queen(int x, int y, IMAGE index, PIECE_COLOR color);
	void Init(int x, int y) override;
	void Draw(HDC hdc) override;
	vector<RECT> RouteNav() override;
	void RouteDraw(HDC hdc) override;
	bool IsMoveable(RECT rect) override;
};