#include "Mecro.h"
#include "News.h"
#include "Composite.h"


int main()
{
	//옵저버
	
	////싱글톤 인스턴스 생성 후 정보출력창 호출
	//News::getInstance()->Display();
	////동적할당된 싱글톤 메모리 해제
	//News::Release();

	//컴포지트
	
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