#include "MinerOwnedStates.h"
#include "EntityNames.h"
#include "ConsoleUtils.h"

// 수업 시간  ------------------------------------
Study* Study::Instance()
{
	//인스턴스 반환
	static Study instance;
	return &instance;
}

void Study::Enter(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":수업 시간이다....." << std::endl;
}
//수업 시간의 재정의된 Excute는 나쁜 컨디션이 아니라면 수업을 잘 들어 지식증가. 나쁜 컨디션이라면 깜빡 졸아 지식증가x 컨디션 감소 x 
void Study::Excute(Miner* pMiner)
{
	//여기서 나쁜 컨디션이 아니라면 수업을 잘 들어 지식량 증가
	if (pMiner->GetCondition() > BAD_CONDITION)
	{
		pMiner->IncreaseKnowledge();
		pMiner->DecreaseCondition();
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":유익한 내용이였어!" << std::endl;
	}
	else
	{
		//졸았으니 컨디션 감소는 없고 지식 증가도 x
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":zzzzzz..." << std::endl;
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":이런!! 깜빡 졸아버렸다! ㅜㅜ" << std::endl;
	}
	
	//수업이 끝났으니 쉬는 시간 상태로
	pMiner->ChangeState(BreakTime::Instance());
}

void Study::Exit(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":수업이 드디어 끝났다..!" << std::endl;
}
// -------------------------------------------------------------

// 쉬는 시간 ------------------------------------
BreakTime* BreakTime::Instance()
{
	static BreakTime instance;
	return &instance;
}

void BreakTime::Enter(Miner* pMiner)
{
	//1교시 끝났으니 시간(교시) Count 증가
	pMiner->IncreaseHourCount();
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":쉬는 시간이다!!" << std::endl;
}

//쉬는 시간의 재정의된 Excute 
void BreakTime::Excute(Miner* pMiner)
{
	
	//점심시간(4)라면 점심시간 상태로 변경
	if (pMiner->GetHourCount() == LUNCH_TIME)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":드디어 점심 시간이다!!" << std::endl;
		//점심시간으로 상태 변경
		pMiner->ChangeState(LunchTime::Instance());
	}

	//방과후(8)시간이라면 집으로
	else if(pMiner->GetHourCount() >= AFTER_SCHOOL)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":드디어 집갈 시간이다!" << std::endl;
		//점심시간으로 상태 변경
		pMiner->ChangeState(Home::Instance());
	}
	//랜덤의 숫자로 컨디션 증가. 1에서 3? 
    int rand_condition = (rand() % 3) + 1;
	//랜덤확률로 수업상태 or 쪽지 시험 상태로 ( 9:1로 )
	int rand_test = (rand() % 100) + 1;

	//10 이상이면 수업 아니면 쪽지시험
	if (rand_test > 10)
	{
		//1~3만큼 컨디션 증가
		pMiner->SetCondition(rand_condition);
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":다시 화이팅 해보자!!" << std::endl;
		// 수업 시간으로
		pMiner->ChangeState(Study::Instance());
	}
	else {
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":으아아.. 쪽지 시험이다.." << std::endl;
		// 쪽지 시험으로
		pMiner->ChangeState(PaperTest::Instance());
	}
}

void BreakTime::Exit(Miner* pMiner)
{
	//SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	//std::cout << GetNameOfEntity(pMiner->ID()) << ":은행을 떠난다" << std::endl;
}
// -------------------------------------------------------------

// 점심 시간 -------------------------------------
LunchTime* LunchTime::Instance()
{
	static LunchTime instance;
	return &instance;
}

void LunchTime::Enter(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":배부르게 먹어보자 ㅎㅎ" << std::endl;
}

void LunchTime::Excute(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":너무 맛있다 ㅎㅎ!" << std::endl;
	//컨디션 회복
	pMiner->IncreaseCondition();
	//다시 수업시간으로
	pMiner->ChangeState(Study::Instance());
}

void LunchTime::Exit(Miner* pMiner)
{
	//SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	//std::cout << GetNameOfEntity(pMiner->ID()) << ":집을 떠난다" << std::endl;
}
// -------------------------------------------------------------

// 쪽지 시험 ------------------------------------------------
PaperTest* PaperTest::Instance()
{
	static PaperTest instance;
	return &instance;
}

void PaperTest::Enter(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":긴장된다!" << std::endl;
}

void PaperTest::Excute(Miner* pMiner)
{
	if (pMiner->GetKnowledge() >= 5)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":A를 받았네!" << std::endl;
		std::cout << GetNameOfEntity(pMiner->ID()) << ":열심히 수업 들은 보람이 있었어 ㅎㅎ" << std::endl;
		pMiner->IncreaseCondition();
	}
	else
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":성적이 엉망이네.." << std::endl;
		std::cout << GetNameOfEntity(pMiner->ID()) << ":수업을 더 열심히 들어야겠어" << std::endl;
	}

	pMiner->ChangeState(BreakTime::Instance());
}

void PaperTest::Exit(Miner* pMiner)
{
	//SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	//std::cout << GetNameOfEntity(pMiner->ID()) << ":술집을 떠난다" << std::endl;
}
// -------------------------------------------------------------
// 무단결(도망)
Truancy* Truancy::Instance()
{
	static Truancy instance;
	return &instance;
}

void Truancy::Enter(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":오늘은 꼭 승급하고 말거야!" << std::endl;
}

void Truancy::Excute(Miner* pMiner)
{
	//붙잡힐 확률
	int rand_caught = (rand() % 100) + 1;

	//잡힐 확률 30 안걸릴 확률 70
	if (rand_caught > 30)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":정말 재밌다!!" << std::endl;
		std::cout << GetNameOfEntity(pMiner->ID()) << ":즐겼으니 걸리기 전에 돌아가보실까" << std::endl;
		pMiner->IncreaseCondition();
	}
	else
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":선생님에게 잡히고 말았네.." << std::endl;
		pMiner->DecreaseCondition();
	}

	pMiner->ChangeState(BreakTime::Instance());
}

void Truancy::Exit(Miner* pMiner)
{
	//SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	//std::cout << GetNameOfEntity(pMiner->ID()) << ":술집을 떠난다" << std::endl;
}

// 집 ------------------------------------------------
Home* Home::Instance()
{
	static Home instance;
	return &instance;
}

void Home::Enter(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":드디어 집 도착했다! ㅜㅜ" << std::endl;
}

void Home::Excute(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":고생했으니 내일을 위해 푹 쉬자" << std::endl;
	std::cout << GetNameOfEntity(pMiner->ID()) << ":zzzzzz.." << std::endl;
	pMiner->IncreaseCondition();
	pMiner->SetCondition(0);
	pMiner->SetKnowledge(0);
	//다음날 되었으니 다시 학교로
	pMiner->ChangeState(Study::Instance());
}

void Home::Exit(Miner* pMiner)
{
	//SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	//std::cout << GetNameOfEntity(pMiner->ID()) << ":술집을 떠난다" << std::endl;
}