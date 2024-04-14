#include "Mecro.h"
#include "News.h"


int main()
{
	News::getInstance()->Display();
	News::Release();
	return 0;
}