#pragma once
#include "Mecro.h"
#include <memory> // 스마트 포인터를 사용하기 위한 헤더파일

//Strategy 비슷한 동작을 할 인터페이스 여기서는 스킬과 동작
__interface SkillStrategy { void Excute(); };
__interface ActionStrategy { void Excute(); };

//concreteStrategy 위 인터페이스를 실체화
class Bash : public SkillStrategy { 
	void Excute() override { cout << "무기로 강하게 때린다!" << endl; }
};
class Blink : public SkillStrategy {
	void Excute() override { cout << "가까운 위치로 빠르게 이동!" << endl; }
};
class FireBall : public SkillStrategy {
	void Excute() override { cout << "화염의 구체를 날린다!!" << endl; }
};
class Idle : public ActionStrategy {
	void Excute() override { cout << "가만히 서있는다" << endl; }
};
class Walk : public ActionStrategy {
	void Excute() override { cout << "걸어 간다" << endl; }
};
class Run : public ActionStrategy {
	void Excute() override { cout << "달려 간다" << endl; }
};

//Context : concreteStrategy를 이용하여 역할을 수행하는 클래스
class Character {
private:
	//메모리를 공유하는 스마트 포인터 
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
	//get은 SkillStrategy의 메모리를 가리켜준다.
	void Attack() { if (nullptr != skill.get()) skill->Excute(); }
	void Move() { if (nullptr != action.get()) action->Excute(); }
};

//스킬과 액션이라는 기본 인터페이스가 있다
//Setter를 통해 이 스킬을 만약 불에 연결하면 화염을 발사 블링크를 연결하면 순간이동
//액션을 Idle에 연결하면 가만히 서있고 Run에 연결하면 달린다!


