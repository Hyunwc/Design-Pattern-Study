#include "Card.h"



Card::Card()
{
	//카드는 후방 상태로(뒤집혀 있는 상태)
	m_eCardState = CARD_REAR;
}


void Card::Init(IMAGE Index, int x, int y)
{
	m_ImageIndex = Index;
	m_pBitMap[CARD_FRONT] = BitMapManager::GetInstance()->GetImage(Index);
	m_pBitMap[CARD_REAR] = BitMapManager::GetInstance()->GetImage(IMAGE_BLACK);
	m_ix = x; //500
	m_iy = y; //200
	m_BitMapRect.left = x; 
	m_BitMapRect.top = y; 
	m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[CARD_FRONT]->GetSize().cx;
	m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[CARD_FRONT]->GetSize().cy;
}
void Card::Draw(HDC hdc)
{
	//카드 상태에 따라 비트맵의 StretchBlt 작업 수행
	m_pBitMap[m_eCardState]->Draw(hdc, m_ix, m_iy);
}
//
bool Card::ColliderCheck(POINT point)
{
	return PtInRect(&m_BitMapRect, point);
	//체크할 사각형의 영역과 x,y(대상의 위치)
	//if (PtInRect(&m_BitMapRect, point))
	//{
	//	//충돌한 상태에서 카드가 앞면일때 뒷면으로
	//	//반대인 상황에선 앞면으로
	//	if (m_eCardState == CARD_FRONT)
	//		m_eCardState = CARD_REAR;
	//	else
	//		m_eCardState = CARD_FRONT;
	//	return true;
	//}
	//return false;
}

IMAGE Card::GetImageIndex()
{
	return m_ImageIndex;
}

void Card::Flip()
{
	m_eCardState = (m_eCardState == CARD_FRONT) ? CARD_REAR : CARD_FRONT;
}

void Card::SetState(CARD state)
{
	m_eCardState = state;
}

CARD Card::GetState()
{
	return m_eCardState;
}

Card::~Card()
{
}
