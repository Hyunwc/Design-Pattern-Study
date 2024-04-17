#include "Mecro.h"
#include "Composite.h"
//#include "FactoryMethod.h"
//#include "Abstract.h"
#include "Strategy.h"

int main()
{
	//안전하게 생성하기 위해 make 사용 권장
	std::shared_ptr<Idle> idle = std::make_shared<Idle>();
	std::shared_ptr<Run> run = std::make_shared<Run>();
	std::shared_ptr<FireBall> fireBall = std::make_shared<FireBall>();
	std::shared_ptr<Bash> bash = std::make_shared<Bash>();
	Character character;

	//Setter를 통해 액션과 스킬의 전략을 보냄
	cout << "==== 마법사 ====" << endl;
	character.SetActionStrategy(idle);
	character.SetSkillStrategy(fireBall);
	character.Move();
	character.Attack();
	cout << endl;

	cout << "==== 전사 ====" << endl;
	character.SetActionStrategy(run);
	character.SetSkillStrategy(bash);
	character.Move();
	character.Attack();
	return 0;
}