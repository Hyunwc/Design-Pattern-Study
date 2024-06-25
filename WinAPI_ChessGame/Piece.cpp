#include "Piece.h"

Piece::Piece(int x, int y) : m_x(x), m_y(y)
{
	SetPosition(x, y);
}
//위치 설정.
void Piece::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
	//[1][0] = 75, 0, 150, 75
	//[1][1] = 75, 75, 150, 150
	//[1][2] = 75, 150, 150, 225
	//[1][3] = 75, 225, 150, 300
	/*m_rect.left = x * 75;
	m_rect.top = y * 75;
	m_rect.right = m_rect.left + 75;
	m_rect.bottom = m_rect.top + 75;*/
	//위가 아닌
	//[1][0] = 0, 75, 75, 150
	//[1][1] = 75,75, 150, 150
	//[1][2] = 150, 75, 225, 150
    m_rect.left = y * 75; //0부터
	m_rect.top = x * 75; // 75
	m_rect.right = m_rect.left + 75;
	m_rect.bottom = m_rect.top + 75;

}
