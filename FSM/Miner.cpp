#include "Miner.h"
#include "MinerOwnedStates.h"
#include <cassert>

Miner::Miner(const int& id) :
	BaseGameEntity(id),
	m_Location(Location_Type::shack),
	m_nGoldCarried(0),
	m_nMoneyInBank(0),
	m_nThirst(0),
	m_nFatigue(0),
	m_pCurrState(GoHomeAndSleepTilRested::Instance()) { }

void Miner::Update()
{
	//갈증도 + 1
	m_nThirst += 1;

	//상태가 nullptr이 아닐때 상태 변경?
	if (m_pCurrState)
	{
		m_pCurrState->Excute(this);
	}
}

void Miner::ChangeState(State* pState)
{
	assert(m_pCurrState && pState); // throw를 던져주는. 현재상태나 변경하려는 상태 둘중 하나라도 null이면 예외를 터뜨림.

	m_pCurrState->Exit(this);
	m_pCurrState = pState;
	//위치 변경
	m_pCurrState->Enter(this);
}

void Miner::AddToGoldCarried(const int& value)
{
	m_nGoldCarried += value;
	if (m_nGoldCarried < 0)
	{
		m_nGoldCarried = 0;
	}
}

void Miner::AddToWealth(const int& value)
{
	m_nMoneyInBank += value;
	if (m_nMoneyInBank < 0)
	{
		m_nMoneyInBank = 0;
	}
}

bool Miner::Thirsty() const
{
	if (THIRST_LEVEL <= m_nThirst)
	{
		return true;
	}

	return false;
}

bool Miner::Fatigued() const
{
	if (TIREDNESS_THRESHOLD < m_nFatigue)
	{
		return true;
	}

	return false;
}