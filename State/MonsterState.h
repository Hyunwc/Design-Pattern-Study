#pragma once
#include <iostream>
using namespace std;

enum MonsterStateType {
    M_IDLE,
    M_ATTACK,
    M_DEFEND,
    M_DIE
};
// ���¸� ��Ÿ���� �⺻ �������̽�
class MonsterState {
public:
    virtual ~MonsterState() {}
    virtual void handle() = 0;
    virtual MonsterStateType getStateType() = 0;
};

// �⺻ ����
class M_IdleState : public MonsterState {
public:
    void handle() override {
        cout << "Monster is in Idle state." << endl;
    }
    MonsterStateType getStateType() override { return MonsterStateType::M_IDLE; }
};

// ���� ����
class M_AttackState : public MonsterState {
public:
    void handle() override {
        cout << "Monster is in attack state!" << endl;
    }
    MonsterStateType getStateType() override { return MonsterStateType::M_ATTACK; }
};

// ���� ����
class M_DefenceState : public MonsterState {
public:
    void handle() override {
        cout << "Monster is in Defence state!" << endl;
    }
    MonsterStateType getStateType() override { return MonsterStateType::M_DEFEND; }
};

// ���� ����
class M_DieState : public MonsterState {
public:
    void handle() override {
        cout << "Monster is die State!" << endl;
    }
    MonsterStateType getStateType() override { return MonsterStateType::M_DIE; }
};

// ���� Ŭ����
class Monster {
private:
    MonsterState* state;
    int health;
public:
    Monster(MonsterState* state, int hp) : state(state), health(hp) {}

    void setState(MonsterState* newState) {
        delete state;
        state = newState;
    }


    void takeDamage(int damage)
    {
        health -= damage;
        cout << "���Ϳ��� " << damage << "������ ����. ������ ����ü�� : " << health << endl;

        if (health <= 0)
        {
            setState(new M_DieState);
            cout << "Monster dies!" << endl;

        }
        else if (health >= 0)
        {
            setState(new M_AttackState);
        }
    }

    MonsterStateType getState() { return state->getStateType(); }

    void handle() {
        state->handle();
    }

    ~Monster() {
        delete state;
    }
};
