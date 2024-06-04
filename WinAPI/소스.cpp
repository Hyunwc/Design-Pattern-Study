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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//������ ���
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;	//���μ��� �Լ� ȣ��
	WndClass.lpszClassName = lpszClass;	//Ŭ���� �̸�
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	
	//WS_OVERLAPPEDWINDOW(�⺻ ���� : ��� �͵��� �� ����) WS_THICKFREME�� ���ԵǱ� ������ ������ ũ�Ⱑ ���� �����ߴ� ��
	//SYSMENU X��ư�� MINIMIZEBOX �ּ�ȭ�� �������
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
		//��Ʈ�� �迭�� �̹��� ��� �ִ� �۾� ����
		GameManager::Instance()->Init(hWnd);
		//�ڵ鰪, Ÿ�̸��� �ĺ���, 1��, Ÿ�̸��� �ݹ��Լ�
		//Null�̹Ƿ� WM_TIMER�� ����
		//Ư�� �Լ��� �����ϸ� �ش� �Լ����� WM_TIMER�� ó��
		SetTimer(hWnd, 1, 1000, NULL);
		return 0;
	//��Ŭ�� ������ 
	case WM_LBUTTONDOWN:
		//�̰����� StartŬ�������� 
		//Ŭ���� ���� ��ǥ�� card�� �浹�˻� �Լ��� �Ѱ���
		Point.x = LOWORD(lParam);
		Point.y = HIWORD(lParam);
		//GameManager::Instance()->CheckCollide(Point);
		//ȭ�� ��ü�� ����� ���� �׸�
		if (GameManager::Instance()->CheckCollide(Point))
		{
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
	case WM_PAINT:
		//���۾����� ���⼭�� ����Ǿ����.
		hdc = BeginPaint(hWnd, &ps);

		//�� �Լ����� ���� ȭ���� ����ȭ������, ����ȭ������, ��������
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
		//�̱��� ����
		//delete BitMapManager::GetInstance();
		KillTimer(hWnd, 1);
		GameManager::Release();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}