#include "Card.h"



Card::Card()
{
	//ī��� �Ĺ� ���·�(������ �ִ� ����)
	m_eCardState = CARD_REAR;
}


void Card::Init(IMAGE Index, int x, int y)
{
	//ex ������ 100 100���� �޴´ٸ�
	m_ImageIndex = Index;
	m_pBitMap[CARD_FRONT] = BitMapManager::GetInstance()->GetImage(Index);
	m_pBitMap[CARD_REAR] = BitMapManager::GetInstance()->GetImage(IMAGE_BLACK);
	// �׷��� ���� 100 100����
	m_ix = x; 
	m_iy = y;
	//GetSize()�� �޾ƿ��� �� 145 235
	// ���� left 100 top 100 right 245 335
	m_BitMapRect.left = x; 
	m_BitMapRect.top = y; 
	m_BitMapRect.right = m_BitMapRect.left + 100;
	m_BitMapRect.bottom = m_BitMapRect.top + 150;
	//m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[CARD_FRONT]->GetSize().cx;
	//m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[CARD_FRONT]->GetSize().cy;
}
void Card::Draw(HDC hdc)
{
	//ī�� ���¿� ���� ��Ʈ���� StretchBlt �۾� ����
	m_pBitMap[m_eCardState]->Draw(hdc, m_ix, m_iy);
}
//
bool Card::ColliderCheck(POINT point)
{
	
	//üũ�� �簢���� ������ x,y(����� ��ġ)
	if (PtInRect(&m_BitMapRect, point))
	{
		//�浹�� ���¿��� ī�尡 �ո��϶� �޸�����
		//�ݴ��� ��Ȳ���� �ո�����
		if (m_eCardState == CARD_FRONT)
			m_eCardState = CARD_REAR;
		else
			m_eCardState = CARD_FRONT;
		return true;
	}
	return false;
}

void Card::SetState()
{
	if (m_eCardState == CARD_FRONT)
		m_eCardState = CARD_REAR;
	else
		m_eCardState = CARD_FRONT;
}

Card::~Card()
{
}
