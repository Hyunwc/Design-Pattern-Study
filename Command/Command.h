#pragma once
#include "Mecro.h"
//key�� value�� ���� ���������� �ʴ� �ߺ��� �����ϴ� �����̳�
#include <unordered_map> 
#include <stack>
#include <string>

//Receiver (Ű���带 �������� ������ ����)
class MoveReceiver {
public:
	void Left() { cout << "�������� �̵�" << endl; }
	void Right() { cout << "���������� �̵�" << endl; }
};

//Command : �������̽�
__interface Command { void Excute(); void Undo(); };
//ConcreteCommand : �� �������̽��� ��üȭ
class LeftCommand : public Command
{
private:
	MoveReceiver* recv;
public:
	LeftCommand(MoveReceiver* recv) : recv(recv){}
	void Excute() override { recv->Left(); }
	void Undo() override { recv->Right(); }
};
class RightCommand : public Command
{
private:
	MoveReceiver* recv;
public:
	RightCommand(MoveReceiver* recv) : recv(recv) {}
	void Excute() override { recv->Right(); }
	void Undo() override { recv->Left(); }
};

//Invoker ȣ����
class InputInvoker {
private:
	unordered_map<string, Command*> commands;
	stack<Command*> undoCommand;
public:
	void SetInputCommand(Command* command, string key) {
		commands[key] = command;
		undoCommand.push(commands[key]);
	}
	void KeyDown(string key)
	{
		//key���� �����Ѵٸ� command�� Receiver ����
		if (commands.end() != commands.find(key))
		{
			commands[key]->Excute();
		}
	}
	void Undo()
	{
		//������� �ʴٸ�
		if (!undoCommand.empty())
		{
			//���� ���߿� ���� �� ������ ����.
			undoCommand.top()->Undo();
			undoCommand.pop();
		}
	}
};
