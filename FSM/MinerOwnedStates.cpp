#include "MinerOwnedStates.h"
#include "EntityNames.h"
#include "ConsoleUtils.h"

// ���� �ð�  ------------------------------------
Study* Study::Instance()
{
	//�ν��Ͻ� ��ȯ
	static Study instance;
	return &instance;
}

void Study::Enter(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ": " << pMiner->GetHourCount() << "���� ���� �ð��̴�....." << std::endl;
}
//���� �ð��� �����ǵ� Excute�� ���� ������� �ƴ϶�� ������ �� ��� ��������. ���� ������̶�� ���� ���� ��������x ����� ���� x 
void Study::Excute(Miner* pMiner)
{
	//����߸� �����
	int rand_condition = (rand() % 4) + 1;
	//���⼭ ������� ���� �̻��̶�� ������ �� ��� ���ķ� ����
	if (pMiner->GetCondition() > NORMAL_CONDITION)
	{
		//���ķ� ����, ����� ����
		pMiner->IncreaseKnowledge();
		pMiner->DecreaseCondition(rand_condition);
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":������ �����̿���!" << std::endl;
	}
	else if(pMiner->GetCondition() > BAD_CONDITION && pMiner->GetCondition() < NORMAL_CONDITION)
	{
		//�������� ����� ���Ҵ� ���� ���� ������ x
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":zzzzzz..." << std::endl;
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":�̷�!! ���� ���ƹ��ȴ�! �̤�" << std::endl;
	}
	else
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":������ ������ �� ��ڴ� ���� pc�� �ٳ����!" << std::endl;
		pMiner->ChangeState(Truancy::Instance());
		return;
	}

	//������ �������� ���� �ð� ���·�
	pMiner->ChangeState(BreakTime::Instance());
}

void Study::Exit(Miner* pMiner)
{
	/*SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":������ ���� ������..!" << std::endl;*/
}
// -------------------------------------------------------------

// ���� �ð� ------------------------------------
BreakTime* BreakTime::Instance()
{
	static BreakTime instance;
	return &instance;
}

void BreakTime::Enter(Miner* pMiner)
{
	//1���� �������� �ð�(����) Count ����
	pMiner->IncreaseHourCount();
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":������ ������!!" << std::endl;
}

//���� �ð��� �����ǵ� Excute 
void BreakTime::Excute(Miner* pMiner)
{
	
	//���ɽð�(4���� ����)�̶�� ���ɽð� ���·� ����
	if (pMiner->GetHourCount() == LUNCH_TIME)
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":���� ���� �ð��̴�!!" << std::endl;
		//���ɽð����� ���� ����
		pMiner->ChangeState(LunchTime::Instance());
		return;
	}

	//�����(8)�ð��̶�� ������
	else if(pMiner->GetHourCount() >= AFTER_SCHOOL)
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":���� ���� �ð��̴�!" << std::endl;
		//���ɽð����� ���� ����
		pMiner->ChangeState(Home::Instance());
		return;
	}
	//������ ���ڷ� ����� ����. 1���� 3? 
    int rand_condition = (rand() % 3) + 1;
	//����Ȯ���� �������� or ���� ���� ���·� ( 9:1�� )
	int rand_test = (rand() % 100) + 1;

	//10 �̻��̸� ���� �ƴϸ� ��������
	if (rand_test > 10)
	{
		//1~3��ŭ ����� ����
		pMiner->SetCondition(rand_condition);
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":�ٽ� ȭ���� �غ���!!" << std::endl;
		// ���� �ð�����
		pMiner->ChangeState(Study::Instance());
		return;
	}
	else
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":���ƾ�.. ���� �����̴�.." << std::endl;
		// ���� ��������
		pMiner->ChangeState(PaperTest::Instance());
		return;
	}
}

void BreakTime::Exit(Miner* pMiner)
{
	//SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	//std::cout << GetNameOfEntity(pMiner->ID()) << ":������ ������" << std::endl;
}
// -------------------------------------------------------------

// ���� �ð� -------------------------------------
LunchTime* LunchTime::Instance()
{
	static LunchTime instance;
	return &instance;
}

void LunchTime::Enter(Miner* pMiner)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":��θ��� �Ծ�� ����" << std::endl;
}

void LunchTime::Excute(Miner* pMiner)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":�ʹ� ���ִ� ����!" << std::endl;
	//����� ȸ��
	pMiner->IncreaseCondition();
	//�ٽ� �����ð�����
	pMiner->ChangeState(Study::Instance());
}

void LunchTime::Exit(Miner* pMiner)
{
	//SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	//std::cout << GetNameOfEntity(pMiner->ID()) << ":���� ������" << std::endl;
}
// -------------------------------------------------------------

// ���� ���� ------------------------------------------------
PaperTest* PaperTest::Instance()
{
	static PaperTest instance;
	return &instance;
}

void PaperTest::Enter(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":����ȴ�!" << std::endl;
}

void PaperTest::Excute(Miner* pMiner)
{
	if (pMiner->GetKnowledge() >= 5)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":A�� �޾ҳ�!" << std::endl;
		std::cout << GetNameOfEntity(pMiner->ID()) << ":������ ���� ���� ������ �־��� ����" << std::endl;
		pMiner->IncreaseCondition();
	}
	else
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":������ �����̳�.." << std::endl;
		std::cout << GetNameOfEntity(pMiner->ID()) << ":������ �� ������ ���߰ھ�" << std::endl;
	}

	pMiner->ChangeState(BreakTime::Instance());
}

void PaperTest::Exit(Miner* pMiner)
{
	//SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	//std::cout << GetNameOfEntity(pMiner->ID()) << ":������ ������" << std::endl;
}
// -------------------------------------------------------------
// ���ܰ�(����)
Truancy* Truancy::Instance()
{
	static Truancy instance;
	return &instance;
}

void Truancy::Enter(Miner* pMiner)
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":������ �� �±��ϰ� ���ž�!" << std::endl;
}

void Truancy::Excute(Miner* pMiner)
{
	//������ Ȯ��
	int rand_caught = (rand() % 100) + 1;

	//���� Ȯ�� 30 �Ȱɸ� Ȯ�� 70
	if (rand_caught > 30)
	{
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":���� ��մ�!!" << std::endl;
		std::cout << GetNameOfEntity(pMiner->ID()) << ":������� �ɸ��� ���� ���ư����Ǳ�" << std::endl;
		pMiner->IncreaseCondition();
	}
	else
	{
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":�����Կ��� ������ ���ҳ�.." << std::endl;
		pMiner->DecreaseCondition(1);
	}

	pMiner->ChangeState(BreakTime::Instance());
}

void Truancy::Exit(Miner* pMiner)
{
	//SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	//std::cout << GetNameOfEntity(pMiner->ID()) << ":������ ������" << std::endl;
}

// �� ------------------------------------------------
Home* Home::Instance()
{
	static Home instance;
	return &instance;
}

void Home::Enter(Miner* pMiner)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":���� �� �����ߴ�! �̤�" << std::endl;
	std::cout << GetNameOfEntity(pMiner->ID()) << ":��������� ������ ���� ǫ ����" << std::endl;
}

void Home::Excute(Miner* pMiner)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":zzzzzz.." << std::endl;
	pMiner->IncreaseCondition();
	pMiner->SetHourCount(1);
	pMiner->SetKnowledge(0);
	//������ �Ǿ����� �ٽ� �б���
	pMiner->ChangeState(Study::Instance());
}

void Home::Exit(Miner* pMiner)
{
	//SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	//std::cout << GetNameOfEntity(pMiner->ID()) << ":������ ������" << std::endl;
}