#pragma once
#include "BitMap.h"
#include "BitMapManager.h"
#include "Board.h"
#include "Piece.h"
#include "Pawn.h"

#define XSTART 0
#define YSTART 0
#define TILE_SIZE 75

class GameManager
{
private:
	static GameManager* instance;
	//�׽�Ʈ��
	BitMap* m_tile1;
	BitMap* m_tile2;
	HWND m_hWnd;
	HDC m_hdc;
	RECT m_board[8][8]; //Ÿ�� ���� 
	Piece* m_pieces[8][8]; 

	GameManager(){}
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
	void Draw(HDC hdc);
	void InitBoard(); //���� �ʱ�ȭ
	void InitPieces(); //�� �ʱ�ȭ
	void DrawPieces(HDC hdc); //�� Draw
};
