#pragma once
#include "Miner.h"


//������ ��� ����
class Study : public State
{
private:
	Study() {}
	Study(const Study&);
	Study& operator=(const Study&);

public:
	//�̱���
	static Study* Instance();

	virtual void Enter(Miner*);
	virtual void Excute(Miner*);
	virtual void Exit(Miner*);
};

//���� �ð� ����
class BreakTime : public State
{
private:
	BreakTime() {}
	BreakTime(const BreakTime&);
	BreakTime& operator=(const BreakTime&);

public:
	static BreakTime* Instance();

	virtual void Enter(Miner*);
	virtual void Excute(Miner*);
	virtual void Exit(Miner*);
};

//���� �ð� ����
class LunchTime : public State
{
private:
	LunchTime() {}
	LunchTime(const LunchTime&);
	LunchTime& operator=(const LunchTime&);

public:
	static LunchTime* Instance();

	virtual void Enter(Miner*);
	virtual void Excute(Miner*);
	virtual void Exit(Miner*);
};

//���� ���� ���� 
class PaperTest : public State
{
private:
	PaperTest() {}
	PaperTest(const PaperTest&);
	PaperTest& operator=(const PaperTest&);

public:
	static PaperTest* Instance();

	virtual void Enter(Miner*);
	virtual void Excute(Miner*);
	virtual void Exit(Miner*);
};

//���ܰ�(���� °�� ����)
class Truancy : public State
{
private:
	Truancy() {}
	Truancy(const Truancy&);
	Truancy& operator=(const Truancy&);

public:
	static Truancy* Instance();

	virtual void Enter(Miner*);
	virtual void Excute(Miner*);
	virtual void Exit(Miner*);
};

//�� ����
class Home : public State
{
private:
	Home() {}
	Home(const Home&);
	Home& operator=(const Home&);

public:
	static Home* Instance();

	virtual void Enter(Miner*);
	virtual void Excute(Miner*);
	virtual void Exit(Miner*);
};