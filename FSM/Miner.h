#pragma once
#include "BaseGameEntity.h"
#include "Locations.h"

#define COMFORT_LEVEL		5	// 안락함을 느끼는 금덩이의 양.
#define MAX_NUGGETS			3	// 최대 소지금.
#define THIRST_LEVEL		5	// 갈증 한계.
#define TIREDNESS_THRESHOLD	5	// 피로 한계.
//#define MAX_CONDITION       10  // 최상의 컨디션.
#define NORMAL_CONDITION    5   //보통 컨디션.
#define BAD_CONDITION       2   // 좋지않은 컨디션.
#define LUNCH_TIME          5   // 점심 시간.
#define AFTER_SCHOOL        8   //방과후
 
class Miner;
//State 추상클래스
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
	int             m_Condition; //컨디션
	int				m_Knowledge; //지식
	int             m_HourCount; //시간(교시)

public:
	Miner(const int& id);
	virtual ~Miner() {}

	void Update() override;
	void ChangeState(State*);
	
	Location_Type Location() const { return m_Location; } //위치 반환
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