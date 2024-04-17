#pragma once
#include "Mecro.h"

//Product (������ ��ü�� �������̽�)
__interface Character
{
	void Init(); //�ʱ�ȭ
	string Attack(); //����
};

//ConcreteProduct (ĳ���͸� ��üȭ)

class Knight : public Character
{
	void Init() override { cout << "��� ���� ����!" << endl; }
	string Attack() override { return "����� �ֵθ���."; }
};

class Berserker : public Character
{
	void Init() override { cout << "������ ���� ����!" << endl; }
	string Attack() override { return "����� �ֵθ���."; }
};

class Sorceress : public Character
{
	void Init() override { cout << "���Ҽ��� ���� ����!" << endl; }
	string Attack() override { return "ȭ�� ��ȯ."; }
};

class Summoner : public Character
{
	void Init() override { cout << "���ɻ� ���� ����!" << endl; }
	string Attack() override { return "���� ��ȯ."; }
};

//Creator ĳ���͸� ������ �Լ��� ���� �߻�Ŭ����
//ConcreteProduct�� ����
class CharacterCreator abstract
{
public:
	virtual ~CharacterCreator(){} //���� �Ҹ���
	//���丮 �޼ҵ�
	//Product(ĳ���͸� �����Ѵ�)
	//���⼭ ����
	virtual Character* Create(int id) abstract; 
};

//ConcreteCreator ���丮 �޼ҵ带 ��üȭ

class Warrior : public CharacterCreator
{
public:
	Character* Create(int id) override
	{
		//id�� ���� ��ȯ �߸��� ���̵�� nullptr��ȯ
		switch (id) {
		case 1: return new Knight;
		case 2: return new Berserker;
		}
		throw "error : �߸��� id";
		return nullptr;
	}
};

class Magicion : public CharacterCreator
{
public:
	Character* Create(int id) override
	{
		//id�� ���� ��ȯ �߸��� ���̵�� nullptr��ȯ
		switch (id) {
		case 1: return new Sorceress;
		case 2: return new Summoner;
		}
		throw "error : �߸��� id";
		return nullptr;
	}
};

