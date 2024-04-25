#include "Miner.h"
#include "MinerOwnedStates.h"
#include <cassert>
#include <cstdlib>
#include <time.h>

Miner::Miner(const int& id) :
	BaseGameEntity(id),
	//m_Location(Location_Type::shack),
	m_Condition(2),
	m_Knowledge(0),
	m_HourCount(1),
	m_pCurrState(Home::Instance()) {
	srand((unsigned int)time(0));
}

void Miner::Update()
{
	//상태가 nullptr이 아닐때 상태 변경
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

void Miner::AddToCondition(const int& value)
{
	m_Condition += value;
	if (m_Condition < 0)
	{
		m_Condition = 0;
	}
}

void Miner::AddToKnowledge(const int& value)
{
	m_Knowledge += value;
	if (m_Knowledge < 0)
	{
		m_Knowledge = 0;
	}
}

//void Miner::AddToWealth(const int& value)
//{
//	m_nMoneyInBank += value;
//	if (m_nMoneyInBank < 0)
//	{
//		m_nMoneyInBank = 0;
//	}
//}
//
//bool Miner::Thirsty() const
//{
//	if (THIRST_LEVEL <= m_nThirst)
//	{
//		return true;
//	}
//
//	return false;
//}
//
//bool Miner::Fatigued() const
//{
//	if (TIREDNESS_THRESHOLD < m_nFatigue)
//	{
//		return true;
//	}
//
//	return false;
//}