#include<Windows.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <iostream>
//#include"Card.h"
#include "GameManager.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("CardGame");


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//아이콘 모양
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;	//프로세스 함수 호출
	WndClass.lpszClassName = lpszClass;	//클레스 이름
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	
	//WS_OVERLAPPEDWINDOW(기본 구성 : 모든 것들이 다 있음) WS_THICKFREME이 포함되기 때문에 윈도우 크기가 조절 가능했던 것
	//SYSMENU X버튼과 MINIMIZEBOX 최소화만 사용하자
	hWnd = CreateWindow(lpszClass, lpszClass, WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	POINT Point;
	
	switch (iMessage)
	{
	case WM_CREATE:
		//비트맵 배열에 이미지 경로 넣는 작업 수행
		GameManager::Instance()->Init(hWnd);
		//핸들값, 타이머의 식별자, 1초, 타이머의 콜백함수
		//Null이므로 WM_TIMER에 전달
		//특정 함수를 설정하면 해당 함수에서 WM_TIMER를 처리
		SetTimer(hWnd, 1, 1000, NULL);
		return 0;
	//좌클릭 했을때 
	case WM_LBUTTONDOWN:
		//이곳에서 Start클릭햇을때 
		//클릭한 곳의 좌표를 card의 충돌검사 함수로 넘겨줌
		Point.x = LOWORD(lParam);
		Point.y = HIWORD(lParam);
		//GameManager::Instance()->CheckCollide(Point);
		//화면 전체를 지우고 새로 그림
		if (GameManager::Instance()->CheckCollide(Point))
		{
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
	case WM_PAINT:
		//이작업들은 여기서만 수행되어야함.
		hdc = BeginPaint(hWnd, &ps);

		//이 함수에서 현재 화면이 시작화면인지, 게임화면인지, 엔딩인지
		GameManager::Instance()->Draw(hdc);

		if (GameManager::Instance()->GetRevCount() >= 2)
		{
			GameManager::Instance()->CardCheck();
			InvalidateRect(hWnd, NULL, TRUE);
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_TIMER:
	{
		if (wParam == 1)
		{
			GameManager::Instance()->HandleTimer();
			//KillTimer(hWnd, 1);
		}
		break;
	}
	case WM_DESTROY:
		//싱글톤 해제
		//delete BitMapManager::GetInstance();
		KillTimer(hWnd, 1);
		GameManager::Release();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}