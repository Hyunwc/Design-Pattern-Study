#include "Mecro.h"
#include "Command.h"

int main()
{
	//Client


	MoveReceiver move;
	//ConcreteCommand�� Reciver�� �������ִ� �κ� 
	//��üȭ�� ��ư�� �ൿ�� ����
	LeftCommand leftCommand(&move);
	RightCommand rightCommand(&move);

	//ȣ����
	InputInvoker input;
	//ȣ���ڿ��� ������ �׼ǰ� Ű�� ����
	//���ÿ� ���ÿ� left > right �� ���̰Ե�
	input.SetInputCommand(&leftCommand, "left");
	input.SetInputCommand(&rightCommand, "right");

	cout << "=======Input=======" << endl;
	input.KeyDown("right");
	input.KeyDown("right");
	input.KeyDown("left");
	input.KeyDown("right");

	cout << "=======Undo=======" << endl;
	//����Ʈ ����Ʈ ������ �����
	input.Undo();
	input.Undo();
	return 0;
}