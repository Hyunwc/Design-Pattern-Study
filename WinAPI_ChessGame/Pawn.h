#pragma once
#include "Piece.h"

class Pawn : public Piece
{
private:
	bool firstMove;
public:
	Pawn(int x, int y, IMAGE index, PIECE_COLOR color);
	void Init(int x, int y) override;
	vector<RECT> RouteNav() override;
	void Draw(HDC hdc) override;
	void RouteDraw(HDC hdc) override;
	bool IsMoveable(RECT rect) override;
	bool IsEnemy(RECT rect);
	//~Pawn(){ GameManager::Release(); }
};
