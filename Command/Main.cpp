#include "Mecro.h"
#include "Command.h"

int main()
{
	//Client


	MoveReceiver move;
	//ConcreteCommand와 Reciver를 연결해주는 부분 
	//실체화된 버튼과 행동을 연결
	LeftCommand leftCommand(&move);
	RightCommand rightCommand(&move);

	//호출자
	InputInvoker input;
	//호출자에게 실행할 액션과 키를 보냄
	//동시에 스택에 left > right 가 쌓이게됨
	input.SetInputCommand(&leftCommand, "left");
	input.SetInputCommand(&rightCommand, "right");

	cout << "=======Input=======" << endl;
	input.KeyDown("right");
	input.KeyDown("right");
	input.KeyDown("left");
	input.KeyDown("right");

	cout << "=======Undo=======" << endl;
	//레프트 라이트 순으로 실행됨
	input.Undo();
	input.Undo();
	return 0;
}