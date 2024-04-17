#pragma once
#include "Mecro.h"
#define DEL(p) if(nullptr != p) {delete p; p = nullptr;}

// AbstractProduct 생성될 장비(객체)의 인터페이스
__interface Weapon { string Name(); int Attack(); };
__interface Armor { string Name(); int Deffend(); };

//Product 위 인터페이스를 실체화한 클래스
class LongSword : public Weapon {
	string Name() { return "롱 소드"; }
	int Attack() { return 100; }
};

class GreatSword : public Weapon {
	string Name() { return "그레이트 소드"; }
	int Attack() { return 500; }
};

class Wand : public Weapon {
	string Name() { return "완드"; }
	int Attack() { return 30; }
};

class Staft : public Weapon {
	string Name() { return "스태프"; }
	int Attack() { return 80; }
};

class FullPlateArmor : public Armor {
	string Name() { return "풀 플레이트 아머"; }
	int Deffend() { return 200; }
};

class LeatherArmor : public Armor {
	string Name() { return "레더 아머"; }
	int Deffend() { return 90; }
};

class Robe : public Armor {
	string Name() { return "로브"; }
	int Deffend() { return 30; }
};

//AbstractFactory Product 장비(객체)들을 만드는 함수를 가지는 인터페이스
__interface EquipmentAbstractFactory
{
	Weapon* CreateWeaopn() const;
	Armor* CreateArmor() const;
};

//ConcreteFactory AbstractFactory를 실체화한 클래스. Product를 참조
class KnightEquipment : public EquipmentAbstractFactory
{
	Weapon* CreateWeaopn() const override { return new LongSword; }
	Armor* CreateArmor() const override { return new FullPlateArmor; }
};

class BerserkerEquipment : public EquipmentAbstractFactory
{
	Weapon* CreateWeaopn() const override { return new GreatSword; }
	Armor* CreateArmor() const override { return new LeatherArmor; }
};

class SorceressEquipment : public EquipmentAbstractFactory
{
	Weapon* CreateWeaopn() const override { return new Staft; }
	Armor* CreateArmor() const override { return new Robe; }
};

class SummonerEquipment : public EquipmentAbstractFactory
{
	Weapon* CreateWeaopn() const override { return new Wand; }
	Armor* CreateArmor() const override { return new Robe; }
};

//Client : ConcreteFactory(무기공장)을 이용하여 만들어진 Product(장비)를 연관 관계로
//Client(캐릭터)가 Product(장비)를 참조 또는 장비가 캐릭터를 참조.,?
class Character
{
private:
	Weapon* weapon;
	Armor* armor;
public:
	//여러 객체를 생성하는곳 
	Character(const EquipmentAbstractFactory* equiment)
	{
		weapon = equiment->CreateWeaopn();
		armor = equiment->CreateArmor();
	}
	~Character()
	{
		DEL(weapon);
		DEL(armor);
	}

	void ShowEquipmentInfo()
	{
		cout << weapon->Name() << " 공격력 : " << weapon->Attack() << endl;
		cout << armor->Name() << " 방어력 : " << armor->Deffend() << endl;
	}
};