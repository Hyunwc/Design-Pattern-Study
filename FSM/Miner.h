#pragma once
#include "BaseGameEntity.h"
#include "Locations.h"

#define COMFORT_LEVEL		5	// �ȶ����� ������ �ݵ����� ��.
#define MAX_NUGGETS			3	// �ִ� ������.
#define THIRST_LEVEL		5	// ���� �Ѱ�.
#define TIREDNESS_THRESHOLD	5	// �Ƿ� �Ѱ�.
//#define MAX_CONDITION       10  // �ֻ��� �����.
#define NORMAL_CONDITION    5   //���� �����.
#define BAD_CONDITION       2   // �������� �����.
#define LUNCH_TIME          5   // ���� �ð�.
#define AFTER_SCHOOL        8   //�����
 
class Miner;
//State �߻�Ŭ����
class State
{
public:
	virtual ~State() {}

	virtual void Enter(Miner*) abstract;
	virtual void Excute(Miner*) abstract;
	virtual void Exit(Miner*) abstract;
};

class Miner : public BaseGameEntity
{
private:
	State*			m_pCurrState;
	Location_Type	m_Location;
	int             m_Condition; //�����
	int				m_Knowledge; //����
	int             m_HourCount; //�ð�(����)

public:
	Miner(const int& id);
	virtual ~Miner() {}

	void Update() override;
	void ChangeState(State*);
	
	Location_Type Location() const { return m_Location; } //��ġ ��ȯ
	void ChangeLocation(const Location_Type& loc_type) { m_Location = loc_type; } 

	int GetCondition() const { return m_Condition; }
	int GetHourCount() const { return m_HourCount; }
	int GetKnowledge() const { return m_Knowledge; }
	void SetCondition(const int& value) { m_Condition += value; }
	void SetKnowledge(const int& value) { m_Knowledge = value; }
	void SetHourCount(const int& value) { m_HourCount = value; }
	void AddToCondition(const int&);
	void AddToKnowledge(const int&);
	//bool PocketsFull() const { return (MAX_NUGGETS <= m_nGoldCarried); }

	bool Fatigued() const;
	void DecreaseCondition(const int& value) { m_Condition -= value; }
	void IncreaseCondition() { m_Condition++; }
	void IncreaseHourCount() { m_HourCount++; }
	void IncreaseKnowledge() { m_Knowledge++; }


	void AddToWealth(const int&);

	bool Thirsty() const;
	//void BuyAndDrinkAWhiskey() { m_nThirst = 0; m_nMoneyInBank -= 2; }
};