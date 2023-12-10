#pragma once
#include <iostream>
using namespace std;

enum HeroStateType {
	IDLE,
	ATTACK,
	DEFEND,
	SPECIAL_ATTACK,
	DIE
};

class HeroState {
public:
	virtual ~HeroState() {}
	virtual void handle() = 0;
	virtual HeroStateType getStateType() = 0;
};

// �⺻ ����
class IdleState : public HeroState {
public:
	void handle() override {
		cout << "Hero is in Idle state." << endl;
	}
	HeroStateType getStateType() override { return HeroStateType::IDLE; }
};

class AttackState : public HeroState {
public:
	void handle() override {
		cout << "Hero is in attack State!" << endl;
	}
	HeroStateType getStateType() override { return HeroStateType::ATTACK; }
};

class SpecialAttackState : public HeroState {
public:
	void handle() override {
		cout << "Hero is in Special attack State!" << endl;
	}
	HeroStateType getStateType() override { return HeroStateType::SPECIAL_ATTACK; }
};

class DefenceState : public HeroState {
public:
	void handle() override {
		cout << "Hero is in Defence State!" << endl;
	}
	HeroStateType getStateType() override { return HeroStateType::DEFEND; }
};

class DieState : public HeroState {
public:
	void handle() override {
		cout << "Hero is in die State!" << endl;
	}
	HeroStateType getStateType() override { return HeroStateType::DIE; }
};

class Hero
{
private:
	HeroState* state;
	int health;
	int mp;
public:
	Hero(HeroState* state, int hp) : state(state), health(hp), mp(0) {}

	void setState(HeroState* newState)
	{
		delete state;
		state = newState;
	}

	void takeDamage(int damage)
	{
		health -= damage;
		cout << "��翡�� " << damage << "������ ����" << endl;

		if (health <= 0)
		{
			setState(new DieState);
			cout << "hero dies!" << endl;

		}
		else if (health >= 0)
		{
			setState(new AttackState);
		}
	}

	bool isEnoughMP() { return mp >= 50; } //�ʻ�� ��� ���� �Ǵ� �޼ҵ�
	bool isDefenceSuccess() { return rand() % 100 < 20; }
	
	void increaseMP(int damage) { mp += damage; }

	void useMP() { mp -= 50; }

	int getHp() { return health; }
	int getMp() { return mp; }


	HeroStateType getState() { return state->getStateType(); }

	void handle() {
		state->handle();
	}

	~Hero()
	{
		delete state;
	}
};