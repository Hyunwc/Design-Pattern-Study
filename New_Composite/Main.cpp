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
	//단일 객체 playerinput, physics, graphics들을
	//플레이어(컴포지트)에게 추가하고 
	//이들을 동일하게 다룬다. 
	cout << "==== set player components ====" << endl;
	GameObject enemy;
	enemy.AddComponent(&enemyInput);
	enemy.AddComponent(&physics);
	enemy.AddComponent(&graphics);
	enemy.RemoveComponent(&enemyInput);
	enemy.Operation();

	return 0;
}