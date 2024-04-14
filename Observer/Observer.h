#pragma once
#include "Mecro.h"

//옵저버 인터페이스
class Observer
{
public:
	//push
	virtual void Update(string news, string date) = 0;
	virtual void ShowDisplay() = 0;
};

//관찰대상자 인터페이스
class Subject
{
public:
	virtual void Add(Observer* observer) = 0;
	virtual void notify() = 0;
};
