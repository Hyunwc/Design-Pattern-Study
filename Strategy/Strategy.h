#pragma once
#include "Mecro.h"
#include <memory> // ����Ʈ �����͸� ����ϱ� ���� �������

//Strategy ����� ������ �� �������̽� ���⼭�� ��ų�� ����
__interface SkillStrategy { void Excute(); };
__interface ActionStrategy { void Excute(); };

//concreteStrategy �� �������̽��� ��üȭ
class Bash : public SkillStrategy { 
	void Excute() override { cout << "����� ���ϰ� ������!" << endl; }
};
class Blink : public SkillStrategy {
	void Excute() override { cout << "����� ��ġ�� ������ �̵�!" << endl; }
};
class FireBall : public SkillStrategy {
	void Excute() override { cout << "ȭ���� ��ü�� ������!!" << endl; }
};
class Idle : public ActionStrategy {
	void Excute() override { cout << "������ ���ִ´�" << endl; }
};
class Walk : public ActionStrategy {
	void Excute() override { cout << "�ɾ� ����" << endl; }
};
class Run : public ActionStrategy {
	void Excute() override { cout << "�޷� ����" << endl; }
};

//Context : concreteStrategy�� �̿��Ͽ� ������ �����ϴ� Ŭ����
class Character {
private:
	//�޸𸮸� �����ϴ� ����Ʈ ������ 
	std::shared_ptr<SkillStrategy> skill;
	std::shared_ptr<ActionStrategy> action;
public:
	//SetterMethod
	void SetSkillStrategy(std::shared_ptr<SkillStrategy> strategy)
	{
		skill = strategy;
	}
	void SetActionStrategy(std::shared_ptr<ActionStrategy> strategy)
	{
		action = strategy;
	}
	//ContextMethod
	//get�� SkillStrategy�� �޸𸮸� �������ش�.
	void Attack() { if (nullptr != skill.get()) skill->Excute(); }
	void Move() { if (nullptr != action.get()) action->Excute(); }
};

//��ų�� �׼��̶�� �⺻ �������̽��� �ִ�
//Setter�� ���� �� ��ų�� ���� �ҿ� �����ϸ� ȭ���� �߻� ��ũ�� �����ϸ� �����̵�
//�׼��� Idle�� �����ϸ� ������ ���ְ� Run�� �����ϸ� �޸���!


