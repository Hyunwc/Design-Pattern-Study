#pragma once
#include "Mecro.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

#pragma comment(lib, "msimg32.lib") //TransparentBlt() �Լ��� ����ϱ� ���� ���̺귯��


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
	BitMap* m_rBitMap;
	HWND m_hWnd;
	HDC m_hdc;
	RECT m_board[8][8]; //Ÿ���� ����
	bool isMove;
	//��� ���� ���� 2���� ���͸� ���̰�2�� m_pieces��� ���Ϳ��� �Ҵ�
	vector<Piece*> m_pieces[2] = { vector<Piece*>(16, nullptr), vector<Piece*>(16, nullptr) };
	Piece* m_select = nullptr;
	GameManager() : isMove(false) {}
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
	//void RouteDraw(HDC hdc);

	//�׽�Ʈ��
	bool CheckRoute(POINT point);
	void MovePiece(POINT point);
};
