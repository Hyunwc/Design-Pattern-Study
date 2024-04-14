#pragma once
#include "Mecro.h"

//������ �������̽�
class Observer
{
public:
	//push
	virtual void Update(string news, string date) = 0;
	virtual void ShowDisplay() = 0;
};

//��������� �������̽�
class Subject
{
public:
	virtual void Add(Observer* observer) = 0;
	virtual void notify() = 0;
};
