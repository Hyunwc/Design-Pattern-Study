#pragma once
#include "Mecro.h"
//key와 value를 가진 정렬해주지 않는 중복값 허용안하는 컨테이너
#include <unordered_map> 
#include <stack>
#include <string>

//Receiver (키보드를 눌렀을때 역할을 수행)
class MoveReceiver {
public:
	void Left() { cout << "왼쪽으로 이동" << endl; }
	void Right() { cout << "오른쪽으로 이동" << endl; }
};

//Command : 인터페이스
__interface Command { void Excute(); void Undo(); };
//ConcreteCommand : 위 인터페이스를 실체화
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

//Invoker 호출자
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
		//key값이 존재한다면 command의 Receiver 수행
		if (commands.end() != commands.find(key))
		{
			commands[key]->Excute();
		}
	}
	void Undo()
	{
		//비어있지 않다면
		if (!undoCommand.empty())
		{
			//제일 나중에 들어온 값 수행후 비운다.
			undoCommand.top()->Undo();
			undoCommand.pop();
		}
	}
};
