#pragma once
#include "BitMap.h"
#include "BitMapManager.h"
#include "Card.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <Windows.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define CARD_WIDTH 100
#define CARD_HEIGHT 150
#define SPACING 10

enum GameState
{
	MainMenu,
	GamePlay,
	GameEnd
};

class GameManager
{
private:
	vector<Card> m_cards; //카드를 담을 벡터
	HWND m_hWnd; //핸들
	GameState m_state; //현재 게임 상태
	RECT startRect, endRect; //메인때 사용할 사각형 영역들
	BitMap* m_background;
	static GameManager* instance;
	//잠시 테스트용으로 사용할 변수들 
	Card* first;
	Card* second;
	int rev_count = 0;
	int finish_count = 0;
	int timelimit = 60;
	bool checking; //카드 체크중일 때 클릭이 되지 않게 하기 위한 변수
	bool isWin; 
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
		//게임매니저에서 비트맵 매니저 관리하니 게임매니저에서 비트맵 매니저 해제
		BitMapManager::Release();
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void Init(HWND hWnd); //초기화
	void Draw(HDC hdc);
	int GetRevCount() { return rev_count; }
	void SetState(GameState state) { m_state = state; }
	bool CheckCollide(POINT point);
	void CardCheck();
	void DestroyTimer();
	void UpdateTimer();
	void ResetData(); //모든 정보를 초기 상태로
};

