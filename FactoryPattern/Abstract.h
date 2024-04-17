#pragma once
#include "Mecro.h"
#define DEL(p) if(nullptr != p) {delete p; p = nullptr;}

// AbstractProduct ������ ���(��ü)�� �������̽�
__interface Weapon { string Name(); int Attack(); };
__interface Armor { string Name(); int Deffend(); };

//Product �� �������̽��� ��üȭ�� Ŭ����
class LongSword : public Weapon {
	string Name() { return "�� �ҵ�"; }
	int Attack() { return 100; }
};

class GreatSword : public Weapon {
	string Name() { return "�׷���Ʈ �ҵ�"; }
	int Attack() { return 500; }
};

class Wand : public Weapon {
	string Name() { return "�ϵ�"; }
	int Attack() { return 30; }
};

class Staft : public Weapon {
	string Name() { return "������"; }
	int Attack() { return 80; }
};

class FullPlateArmor : public Armor {
	string Name() { return "Ǯ �÷���Ʈ �Ƹ�"; }
	int Deffend() { return 200; }
};

class LeatherArmor : public Armor {
	string Name() { return "���� �Ƹ�"; }
	int Deffend() { return 90; }
};

class Robe : public Armor {
	string Name() { return "�κ�"; }
	int Deffend() { return 30; }
};

//AbstractFactory Product ���(��ü)���� ����� �Լ��� ������ �������̽�
__interface EquipmentAbstractFactory
{
	Weapon* CreateWeaopn() const;
	Armor* CreateArmor() const;
};

//ConcreteFactory AbstractFactory�� ��üȭ�� Ŭ����. Product�� ����
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

//Client : ConcreteFactory(�������)�� �̿��Ͽ� ������� Product(���)�� ���� �����
//Client(ĳ����)�� Product(���)�� ���� �Ǵ� ��� ĳ���͸� ����.,?
class Character
{
private:
	Weapon* weapon;
	Armor* armor;
public:
	//���� ��ü�� �����ϴ°� 
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
		cout << weapon->Name() << " ���ݷ� : " << weapon->Attack() << endl;
		cout << armor->Name() << " ���� : " << armor->Deffend() << endl;
	}
};