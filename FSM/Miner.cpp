#include "Miner.h"
#include "MinerOwnedStates.h"
#include <cassert>
#include <cstdlib>
#include <time.h>

Miner::Miner(const int& id) :
	BaseGameEntity(id),
	//m_Location(Location_Type::shack),
	m_Condition(0),
	m_Knowledge(0),
	m_HourCount(0),
	m_pCurrState(Home::Instance()) {
	srand((unsigned int)time(0));
}

void Miner::Update()
{
	//������ + 1
	//m_nThirst += 1;

	//���°� nullptr�� �ƴҶ� ���� ����?
	if (m_pCurrState)
	{
		m_pCurrState->Excute(this);
	}
}

void Miner::ChangeState(State* pState)
{
	assert(m_pCurrState && pState); // throw�� �����ִ�. ������³� �����Ϸ��� ���� ���� �ϳ��� null�̸� ���ܸ� �Ͷ߸�.

	m_pCurrState->Exit(this);
	m_pCurrState = pState;
	//��ġ ����
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