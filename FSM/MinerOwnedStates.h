#pragma once
#include "Miner.h"


//수업을 듣는 상태
class Study : public State
{
private:
	Study() {}
	Study(const Study&);
	Study& operator=(const Study&);

public:
	//싱글톤
	static Study* Instance();

	virtual void Enter(Miner*);
	virtual void Excute(Miner*);
	virtual void Exit(Miner*);
};

//쉬는 시간 상태
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

//점심 시간 상태
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

//쪽지 시험 상태 
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

//무단결(수업 째고 도망)
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

//집 상태
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