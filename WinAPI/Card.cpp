#include "Card.h"



Card::Card()
{
	//카드는 후방 상태로(뒤집혀 있는 상태)
	m_eCardState = CARD_REAR;
}


void Card::Init(IMAGE Index, int x, int y)
{
	//ex 시작을 100 100으로 받는다면
	m_ImageIndex = Index;
	m_pBitMap[CARD_FRONT] = BitMapManager::GetInstance()->GetImage(Index);
	m_pBitMap[CARD_REAR] = BitMapManager::GetInstance()->GetImage(IMAGE_BLACK);
	// 그려질 영역 100 100으로
	m_ix = x; 
	m_iy = y;
	//GetSize()로 받아오는 값 145 235
	// 영역 left 100 top 100 right 245 335
	m_BitMapRect.left = x; 
	m_BitMapRect.top = y; 
	m_BitMapRect.right = m_BitMapRect.left + 100;
	m_BitMapRect.bottom = m_BitMapRect.top + 150;
	//m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[CARD_FRONT]->GetSize().cx;
	//m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[CARD_FRONT]->GetSize().cy;
}
void Card::Draw(HDC hdc)
{
	//카드 상태에 따라 비트맵의 StretchBlt 작업 수행
	m_pBitMap[m_eCardState]->Draw(hdc, m_ix, m_iy);
}
//
bool Card::ColliderCheck(POINT point)
{
	
	//체크할 사각형의 영역과 x,y(대상의 위치)
	if (PtInRect(&m_BitMapRect, point))
	{
		//충돌한 상태에서 카드가 앞면일때 뒷면으로
		//반대인 상황에선 앞면으로
		//
		if (m_eCardState == CARD_FRONT)
			m_eCardState = CARD_REAR;
		else
			m_eCardState = CARD_FRONT;
		return true;
	}
	return false;
}

void Card::SetState(bool success)
{
	//
	if (success)
		m_eCardState = CARD_END;
	else 
	    (m_eCardState == CARD_FRONT) ? m_eCardState = CARD_REAR : m_eCardState = CARD_FRONT;
		
}

Card::~Card()
{
}
