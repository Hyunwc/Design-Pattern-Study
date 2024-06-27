#pragma once
#include "Mecro.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

#pragma comment(lib, "msimg32.lib") //TransparentBlt() 함수를 사용하기 위한 라이브러리


#define XSTART 0
#define YSTART 0
#define TILE_SIZE 75

class GameManager
{
private:
	static GameManager* instance;
	//테스트용
	BitMap* m_tile1;
	BitMap* m_tile2;
	HWND m_hWnd;
	HDC m_hdc;
	RECT m_board[8][8]; //타일의 영역
	//흑과 백을 담을 2개의 벡터를 길이가2인 m_pieces라는 벡터에게 할당
	vector<Piece*> m_pieces[2] = { vector<Piece*>(16, nullptr), vector<Piece*>(16, nullptr) };
	GameManager() {}
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

	void Draw(HDC hdc);
	void PieceDraw(HDC hdc);
};
