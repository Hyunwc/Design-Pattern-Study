#pragma once
#include "Mecro.h"

//������ �������̽�
class Observer
{
public:
	//�������� ���� ������Ʈ
	virtual void Update(const string& news, const string& date) = 0;
	//�������� ���� ���
	virtual void ShowDisplay() = 0;

	virtual ~Observer(){ }
};

//��������� �������̽�
class Subject
{
public:
	//������ �߰�
	virtual void Add(Observer* observer) = 0;
	virtual void notify() = 0;

	virtual ~Subject(){ }
};
