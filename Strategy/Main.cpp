#include "Mecro.h"
#include "Composite.h"
//#include "FactoryMethod.h"
//#include "Abstract.h"
#include "Strategy.h"

int main()
{
	//�����ϰ� �����ϱ� ���� make ��� ����
	std::shared_ptr<Idle> idle = std::make_shared<Idle>();
	std::shared_ptr<Run> run = std::make_shared<Run>();
	std::shared_ptr<FireBall> fireBall = std::make_shared<FireBall>();
	std::shared_ptr<Bash> bash = std::make_shared<Bash>();
	Character character;

	//Setter�� ���� �׼ǰ� ��ų�� ������ ����
	cout << "==== ������ ====" << endl;
	character.SetActionStrategy(idle);
	character.SetSkillStrategy(fireBall);
	character.Move();
	character.Attack();
	cout << endl;

	cout << "==== ���� ====" << endl;
	character.SetActionStrategy(run);
	character.SetSkillStrategy(bash);
	character.Move();
	character.Attack();
	return 0;
}