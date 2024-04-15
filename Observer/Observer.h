#pragma once
#include "Mecro.h"

//옵저버 인터페이스
class Observer
{
public:
	//옵저버의 정보 업데이트
	virtual void Update(const string& news, const string& date) = 0;
	//옵저버의 정보 출력
	virtual void ShowDisplay() = 0;

	virtual ~Observer(){ }
};

//관찰대상자 인터페이스
class Subject
{
public:
	//옵저버 추가
	virtual void Add(Observer* observer) = 0;
	virtual void notify() = 0;

	virtual ~Subject(){ }
};
