#pragma once
#include "Mecro.h"

//Product (생성될 객체의 인터페이스)
__interface Character
{
	void Init(); //초기화
	string Attack(); //공격
};

//ConcreteProduct (캐릭터를 실체화)

class Knight : public Character
{
	void Init() override { cout << "기사 생성 성공!" << endl; }
	string Attack() override { return "장검을 휘두른다."; }
};

class Berserker : public Character
{
	void Init() override { cout << "광전사 생성 성공!" << endl; }
	string Attack() override { return "대검을 휘두른다."; }
};

class Sorceress : public Character
{
	void Init() override { cout << "원소술사 생성 성공!" << endl; }
	string Attack() override { return "화염 소환."; }
};

class Summoner : public Character
{
	void Init() override { cout << "정령사 생성 성공!" << endl; }
	string Attack() override { return "정령 소환."; }
};

//Creator 캐릭터를 만들어내는 함수를 가진 추상클래스
//ConcreteProduct를 참조
class CharacterCreator abstract
{
public:
	virtual ~CharacterCreator(){} //가상 소멸자
	//팩토리 메소드
	//Product(캐릭터를 참조한다)
	virtual Character* Create(int id) abstract; 
};

//ConcreteCreator 팩토리 메소드를 실체화

class Warrior : public CharacterCreator
{
public:
	Character* Create(int id) override
	{
		//id에 따라 반환 잘못된 아이디면 nullptr반환
		switch (id) {
		case 1: return new Knight;
		case 2: return new Berserker;
		}
		throw "error : 잘못된 id";
		return nullptr;
	}
};

class Magicion : public CharacterCreator
{
public:
	Character* Create(int id) override
	{
		//id에 따라 반환 잘못된 아이디면 nullptr반환
		switch (id) {
		case 1: return new Sorceress;
		case 2: return new Summoner;
		}
		throw "error : 잘못된 id";
		return nullptr;
	}
};

