#pragma once
#include "Mecro.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <string>

#pragma comment(lib, "msimg32.lib") //TransparentBlt() 함수를 사용하기 위한 라이브러리


#define XSTART 0
#define YSTART 0
#define TILE_SIZE 75

enum GameState
{
	Main,
	GamePlay,
	PawnPromotion,
	GameEnd
};
class GameManager
{
private:
	static GameManager* instance;
	BitMap* m_tile1;
	BitMap* m_tile2;
	HWND m_hWnd;
	HDC m_hdc;
	RECT m_board[8][8]; //타일의 영역
	PIECE_COLOR m_colors[8][8]; 
	GameState m_state;
	RECT startRect, endRect;
	wstring winstr;
	bool isEnd; 
	PIECE_COLOR m_turn;
	vector<BitMap*> m_promotionimage[2];
	int timer;
	int widht, height;
	HDC backDC;
	int promotionPos[4][2] =
	{
		{2,1},{5,1}, {2,3}, {5,3}
	};
	RECT promotions[4];
	int newX, newY;
	
	//흑과 백을 담을 2개의 벡터를 길이가2인 m_pieces라는 벡터에게 할당
	vector<Piece*> m_pieces[2] = { vector<Piece*>(16, nullptr), vector<Piece*>(16, nullptr) };
	Piece* m_select = nullptr;
	/*RECT clientRect;
	HBITMAP backBitmap;
	HDC backDC;*/
	GameManager() : m_turn(PIECE_COLOR_WHITE) {
		
	}
public:
	~GameManager();
	static GameManager* Instance()
	{
		if (instance == nullptr) instance = new GameManager;
		return instance;
	}
	static void Release()
	{
		BitMapManager::Release();
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void Init(HWND hWnd);
	void InitBoard(); //보드 초기화
	void InitPiece(); //말 초기화
	bool CheckCollide(POINT point);

	void Draw(HDC hdc);
	void PieceDraw(HDC hdc);
	
	bool CheckRoute(POINT point);
	void MovePiece(POINT point);
	void TurnChange();
	void UpdateTimer();
	void Promotion(int x, int y, IMAGE type = IMAGE_BLACK_QUEEN);
	void SetState(GameState state) { m_state = state; }
	void Reset();

	PIECE_COLOR GetPieceColor(RECT rect);
};
