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

#pragma comment(lib, "msimg32.lib") //TransparentBlt() �Լ��� ����ϱ� ���� ���̺귯��


#define XSTART 0
#define YSTART 0
#define TILE_SIZE 75

enum GameState
{
	Main,
	GamePlay,
	GameEnd
};
class GameManager
{
private:
	static GameManager* instance;
	//�׽�Ʈ��
	BitMap* m_tile1;
	BitMap* m_tile2;
	BitMap* m_rBitMap;
	HWND m_hWnd;
	HDC m_hdc;
	RECT m_board[8][8]; //Ÿ���� ����
	PIECE_COLOR m_colors[8][8]; 
	GameState m_state;
	RECT startRect, endRect;
	bool isMove;
	bool isWhiteTurn;
	int winner;
	wstring winstr;
	bool isOver;
	PIECE_COLOR m_turn;
	//��� ���� ���� 2���� ���͸� ���̰�2�� m_pieces��� ���Ϳ��� �Ҵ�
	vector<Piece*> m_pieces[2] = { vector<Piece*>(16, nullptr), vector<Piece*>(16, nullptr) };
	Piece* m_select = nullptr;
	GameManager() : isMove(false), isWhiteTurn(true), isOver(false), m_turn(PIECE_COLOR_WHITE) {}
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
	void InitBoard(); //���� �ʱ�ȭ
	void InitPiece(); //�� �ʱ�ȭ
	bool CheckCollide(POINT point);

	void Draw(HDC hdc);
	void PieceDraw(HDC hdc);
	
	bool CheckRoute(POINT point);
	void MovePiece(POINT point);
	void RemovePiece(int x, int y);
	bool KillPiece(POINT point);
	void TurnChange();
	void Promotion(int x, int y);

	PIECE_COLOR GetPieceColor(RECT rect);
	
};
