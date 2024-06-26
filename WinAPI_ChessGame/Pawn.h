#pragma once
#include "Piece.h"

class Pawn : public Piece
{
private:
	bool firstMove;
public:
	Pawn(int x, int y, IMAGE index);
	void Init(int x, int y) override;
	bool RouteNav() override;
	void Draw(HDC hdc) override;
	void RouteDraw(HDC hdc) override;
};
