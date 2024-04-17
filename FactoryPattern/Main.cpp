#include "Mecro.h"
#include "Composite.h"
#include "FactoryMethod.h"
#include <memory>
//#include "Abstract.h"

int main()
{
	//���丮 �޼ҵ�
	
	////��ĳ����
	//CharacterCreator* warriorCreator = new Warrior();
	//CharacterCreator* magicianrCreator = new Magicion();

	////ĳ���� ����(���� id�� �´� �޸� �Ҵ� ����)
	//Character* knight = warriorCreator->Create(1);
	//Character* berserker = warriorCreator->Create(2);
	//Character* sorceress = magicianrCreator->Create(1);
	//Character* summoner = magicianrCreator->Create(2);

	//knight->Init();
	//cout << knight->Attack() << endl;
	//berserker->Init();
	//cout << berserker->Attack() << endl;
	//sorceress->Init();
	//cout << sorceress->Attack() << endl;
	//summoner->Init();
	//cout << summoner->Attack() << endl;

	//delete knight;
	//delete berserker;
	//delete sorceress;
	//delete summoner;
	//delete warriorCreator;
	//delete magicianrCreator;

	//�߻� ���丮
   /* EquipmentAbstractFactory* knightFactory = new KnightEquipment();
	EquipmentAbstractFactory* summonerFactory = new SummonerEquipment();

	Character* knight = new Character(knightFactory);
	Character* summoner = new Character(summonerFactory);

	cout << "==== Knight ====" << endl;
	knight->ShowEquipmentInfo();
	cout << endl;

	cout << "==== summoner ====" << endl;
	summoner->ShowEquipmentInfo();
	cout << endl;

	delete knight;
	delete summoner;
	delete knightFactory;
	delete summonerFactory;*/

	//����Ʈ ������ ����

	std::unique_ptr< CharacterCreator> warriorCreator(new Warrior());
	std::unique_ptr< CharacterCreator> magicianrCreator(new Magicion());
	//CharacterCreator* warriorCreator = new Warrior();
	//CharacterCreator* magicianrCreator = new Magicion();

	//ĳ���� ����(���� id�� �´� �޸� �Ҵ� ����)
	std::unique_ptr< Character> knight(warriorCreator->Create(1));
	std::unique_ptr< Character> berserker(warriorCreator->Create(2));
	std::unique_ptr< Character> sorceress(magicianrCreator->Create(1));
	std::unique_ptr< Character> summoner(magicianrCreator->Create(2));
	

	knight->Init();
	cout << knight->Attack() << endl;
	berserker->Init();
	cout << berserker->Attack() << endl;
	sorceress->Init();
	cout << sorceress->Attack() << endl;
	summoner->Init();
	cout << summoner->Attack() << endl;

	
	return 0;
}