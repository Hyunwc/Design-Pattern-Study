#pragma once
#include "Mecro.h"


class Observer
{
public:
	//push
	virtual void Update(void* data){}
	virtual void ShowInfo(){}
};

class Subject
{
protected:
	vector<Observer*> observers;
public:
	virtual void Add(Observer* observer) { observers.push_back(observer); }
	//virtual void Remove(Observer* observer) { observers.remove(observer); }
	virtual void Notify(){}
};
