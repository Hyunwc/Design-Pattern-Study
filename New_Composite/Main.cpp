#include "Mecro.h"
#include "News.h"
#include "Composite.h"


int main()
{
	//������
	
	////�̱��� �ν��Ͻ� ���� �� �������â ȣ��
	//News::getInstance()->Display();
	////�����Ҵ�� �̱��� �޸� ����
	//News::Release();

	//������Ʈ
	
	PlayerInput playerInput;
	EnemyInput enemyInput;
	Physics physics;
	Graphics graphics;

	cout << "==== set player components ====" << endl;
	GameObject player;
	player.AddComponent(&playerInput);
	player.AddComponent(&physics);


	return 0;
}