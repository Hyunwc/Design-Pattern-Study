#include "Mecro.h"
#include "News.h"


int main()
{
	//�̱��� �ν��Ͻ� ���� �� �������â ȣ��
	News::getInstance()->Display();
	//�����Ҵ�� �̱��� �޸� ����
	News::Release();
	return 0;
}