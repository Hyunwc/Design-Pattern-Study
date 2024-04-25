#include <iostream>
#include "Miner.h"
#include "ConsoleUtils.h"
#include "EntityNames.h"


int main()
{
	Miner miner(ent_Miner_Bob);
	Miner elsa(ent_Elsa);

	for (int i = 0; 50 > i; i++)
	{
		elsa.Update();

		Sleep(1000);
	}
}