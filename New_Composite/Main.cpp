#include "Mecro.h"
#include "News.h"
#include "Composite.h"


int main()
{
	PlayerInput playerInput;
	EnemyInput enemyInput;
	Physics physics;
	Graphics graphics;

	cout << "==== set player components ====" << endl;
	GameObject player;
	player.AddComponent(&playerInput);
	player.AddComponent(&physics);
	player.AddComponent(&graphics);
	player.Operation();
	//���� ��ü playerinput, physics, graphics����
	//�÷��̾�(������Ʈ)���� �߰��ϰ� 
	//�̵��� �����ϰ� �ٷ��. 
	cout << "==== set player components ====" << endl;
	GameObject enemy;
	enemy.AddComponent(&enemyInput);
	enemy.AddComponent(&physics);
	enemy.AddComponent(&graphics);
	enemy.RemoveComponent(&enemyInput);
	enemy.Operation();

	return 0;
}