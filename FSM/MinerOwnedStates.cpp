#include "MinerOwnedStates.h"
#include "EntityNames.h"
#include "ConsoleUtils.h"

// EnterMineAndDigForNugget ------------------------------------
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
	//인스턴스 반환
	static EnterMineAndDigForNugget instance;
	return &instance;
}

void EnterMineAndDigForNugget::Enter(Miner* pMiner)
{
	//pMiner의 위치가 광산이 아니면 출력 후 위치를 광산으로 변경
	if (pMiner->Location() != Location_Type::gold_mine)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":광산으로 걸어간다" << std::endl;

		pMiner->ChangeLocation(Location_Type::gold_mine);
	}
}
//광산의 재정의된 Excute는 금덩이를 채고 피로도가 증가하며 주머니가 가득차면 은행으로 전환
//갈증도가 최대치면 갈증해소로 전환
void EnterMineAndDigForNugget::Excute(Miner* pMiner)
{
	//금덩이 1개 채굴
	pMiner->AddToGoldCarried(1);
	//피로도 1증가
	pMiner->IncreaseFatigue();

	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":금덩이 1개를 채굴" << std::endl;

	// 주머니가 가득차면,
	if (pMiner->PocketsFull())
	{
		// 저금을 위해 은행 방문.
		pMiner->ChangeState(VisitBankAndDepositGold::Instance());
	}

	// 목이 마르면,
	if (pMiner->Thirsty())
	{
		// 목마름 해소를 위해 행동.
		pMiner->ChangeState(QuenchThirst::Instance());
	}
}

void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":금덩이 " << pMiner->GoldCarried() << "개를 가지고 광산을 떠난다" << std::endl;
}
// -------------------------------------------------------------

// VisitBankAndDepositGold ------------------------------------
VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
	static VisitBankAndDepositGold instance;
	return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* pMiner)
{
	//현재 위치가 은행이 아니라면 위치를 은행으로 변경
	if (pMiner->Location() != Location_Type::bank)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":은행으로 이동" << std::endl;

		pMiner->ChangeLocation(Location_Type::bank);
	}
}

//은행의 재정의된 Excute 
void VisitBankAndDepositGold::Excute(Miner* pMiner)
{
	//광산에서 캔 금덩이만큼 저축금액 증가
	pMiner->AddToWealth(pMiner->GoldCarried());
	//저축 하였으니 광부가 광산에서 캔 금덩이 초기화
	pMiner->SetGoldCarried(0);

	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":금덩이 저금\n\n현재 잔금:" << pMiner->Wealth() << std::endl << std::endl;

	// 저축 금액을 확인,
	if (pMiner->Wealth() >= COMFORT_LEVEL)
	{
		// 만족할 만큼 돈을 모았다.
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":\"우와! 이제 나는 부자다. 집에 있는 아내에게로 돌아가지.\"" << std::endl;
		//집으로 상태전환
		pMiner->ChangeState(GoHomeAndSleepTilRested::Instance());
	}
	else
	{
		// 아직 돈이 부족하다. 다시 광산으로.
		pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
	}
}

void VisitBankAndDepositGold::Exit(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":은행을 떠난다" << std::endl;
}
// -------------------------------------------------------------

// GoHomeAndSleepTilRested -------------------------------------
GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
	static GoHomeAndSleepTilRested instance;
	return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner)
{
	//위치가 집이 아니면 집으로 상태전환
	if (pMiner->Location() != Location_Type::shack)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":집으로 들어간다" << std::endl;

		pMiner->ChangeLocation(Location_Type::shack);
	}
}

void GoHomeAndSleepTilRested::Excute(Miner* pMiner)
{
	// 피로도를 확인.
	if (!pMiner->Fatigued())
	{
		// 피로가 다 필리면 다시 금을 캐러같다.
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":\"낮잠을 늘어지게 잤네! 다시 금을 캐러 가야겠군.\"" << std::endl;
		//광산으로
		pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else
	{
		// 피곤하니 잠을 잔다. 1씩 줄어드네
		pMiner->DecreaseFatigue();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":...zZ" << std::endl;
	}
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":집을 떠난다" << std::endl;
}
// -------------------------------------------------------------

// QuenchThirst ------------------------------------------------
QuenchThirst* QuenchThirst::Instance()
{
	static QuenchThirst instance;
	return &instance;
}

void QuenchThirst::Enter(Miner* pMiner)
{
	if (pMiner->Location() != Location_Type::saloon)
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":\"목이 마르군!\"" << std::endl;
		std::cout << GetNameOfEntity(pMiner->ID()) << ":술집으로 들어간다" << std::endl;

		pMiner->ChangeLocation(Location_Type::saloon);
	}
}

void QuenchThirst::Excute(Miner* pMiner)
{
	// 갈증이 있다면,
	if (pMiner->Thirsty())
	{
		// 목이 마르니 술을 마시자.
		//갈증0으로 초기화, 현재 금액 -2
		pMiner->BuyAndDrinkAWhiskey();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(pMiner->ID()) << ":술을 마신다" << std::endl;

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "\n현재 잔금:" << pMiner->Wealth() << std::endl << std::endl;
		//광산에서 목이마를때 술집 들렀다가 갈증 해소하고 다시 광산으로 출근
		pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else
	{
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "\nError!\nError!!\nError!!!" << std::endl;
	}
}

void QuenchThirst::Exit(Miner* pMiner)
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << GetNameOfEntity(pMiner->ID()) << ":술집을 떠난다" << std::endl;
}
// -------------------------------------------------------------