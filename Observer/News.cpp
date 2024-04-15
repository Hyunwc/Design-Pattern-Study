//#include "News.h"
//
//News* News::getInstance()
//{
//	if (instance == nullptr)
//		instance = new News();
//	return instance;
//}
//
//void News::Release()
//{
//	if (instance)
//	{
//		delete instance;
//		instance = nullptr;
//	}
//}
//
//void News::Add(Observer* observer)
//{
//	observers.push_back(observer);
//}
//
//void News::notify()
//{
//	for (auto obs : observers)
//	{
//		obs->Update(newsinfo, date);
//	}
//}
//
//void News::UpdateNews(const string& news)
//{
//	//뉴스 내용을 매개변수 news로 업데이트
//	newsinfo = news;
//	date = currentDateTime();
//}
//
//void News::ObserverDisplay()
//{
//	for (auto obs : observers)
//	{
//		obs->ShowDisplay();
//	}
//}
//
//void News::Display()
//{
//	int Select;
//	while (true)
//	{
//		cout << "===News===" << endl;
//		cout << "1. 고객등록" << endl;
//		cout << "2. News 전송" << endl;
//		cout << "3. News 업데이트" << endl;
//		cout << "4. News 시청" << endl;
//		cout << "0. 종료" << endl;
//		cout << "선택 : ";
//		cin >> Select;
//
//		switch (Select)
//		{
//		case 1:
//		{
//			string customerName;
//			cout << "등록할 고객 이름을 입력해주세요 : ";
//			cin >> customerName;
//			Add(new Person(customerName));
//			break;
//		}
//		case 2:
//		{
//			notify();
//			break;
//		}
//		case 3:
//		{
//			string news;
//			cout << "새로운 기사 내용을 입력 해주세요 : ";
//			cin.ignore(); // 입력 버퍼 비우기
//			getline(cin, news); // 한 줄 전체를 입력 받음
//			UpdateNews(news);
//			break;
//		}
//		case 4:
//		{
//			ObserverDisplay();
//			break;
//		}
//		case 0:
//			return;
//		default: cout << "잘못 입력 " << endl;
//		}
//		system("pause"); system("cls");
//	}
//
//}
//
//News::~News()
//{
//	for (auto obs : observers)
//	{
//		delete obs;
//	}
//	observers.clear();
//}
//
//News* News::instance = nullptr;