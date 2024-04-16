#include "Mecro.h"
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

	cout << endl << "=== Set Enemy Components ===" << endl;
	GameObject enemy;
	enemy.AddComponent(&enemyInput);
	enemy.AddComponent(&physics);
	enemy.AddComponent(&graphics);
	enemy.RemoveComponent(&physics);
	enemy.Operation();


	return 0;
}