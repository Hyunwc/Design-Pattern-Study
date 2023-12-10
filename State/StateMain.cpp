#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "MonsterState.h"
#include "HeroState.h"
using namespace std;

int main() {
    Hero hero(new IdleState, 100);
    Monster monster(new M_IdleState, 100);
    srand(static_cast<unsigned int>(time(0)));
    //�����ϰ� ���� ���� �����Ұ��� ����
    bool heroTurn = rand() % 2;
    int choose;
   
    while (true)
    {
        system("cls");
        cout << "���̵����� ���� ���� ȯ���մϴ�." << endl;
        cout << "��� Hp : " << hero.getHp() << ", Mp : " << hero.getMp() << endl;
        cout << "���� Hp : " << monster.getHp() << endl;

        if (heroTurn) {
            cout << "������ ���Դϴ�." << endl;
            cout << "1. �Ϲ� ���� 2. �ʻ��(MP������ 50�̻�)" << endl;
            cout << "�Է� : ";
            cin >> choose;
            if (choose == 1)
            {
                hero.setState(new AttackState);
                hero.handle();
                int damage = rand() % 20 + 1;
                monster.takeDamage(damage);
                hero.increaseMP(damage);
            }
            else if (choose == 2 && hero.isEnoughMP())
            {
                hero.setState(new SpecialAttackState);
                hero.handle();
                monster.takeDamage(50);
                hero.useMP(); //�ʻ�� ��� ��  MP����
            }
            else {
                cout << "MP�� �����ϰų� �߸� �����ϼ̽��ϴ�. �ٽ� �������ּ���." << endl;
                system("pause");
                continue;
            }
           
            hero.setState(new DefenceState);

        }
        else {
            cout << "������ ���Դϴ�." << endl;
            monster.setState(new M_AttackState);
            monster.handle();
            Sleep(2000);
            if (hero.getState() == DEFEND && hero.isDefenceSuccess())
                cout << "������ ������ �Ϻ��ϰ� ���ҽ��ϴ�!" << endl;
            else
                hero.takeDamage(rand() % 20 + 1);
           
            monster.setState(new M_DefenceState);
        }

        if (hero.getState() == DIE || monster.getState() == M_DIE)
        {
            if (hero.getState() == DIE)
                cout << "������ �й��ϼ̽��ϴ�." << endl;
            else
                cout << "������ �¸��ϼ̽��ϴ�." << endl;
            break;
        }

        heroTurn = !heroTurn;

        system("pause");
    }

    return 0;
}