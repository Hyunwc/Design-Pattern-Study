#include "Mecro.h"
#include "News.h"


int main()
{
	//싱글톤 인스턴스 생성 후 정보출력창 호출
	News::getInstance()->Display();
	//동적할당된 싱글톤 메모리 해제
	News::Release();
	return 0;
}