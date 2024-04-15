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
//	//���� ������ �Ű����� news�� ������Ʈ
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
//		cout << "1. �����" << endl;
//		cout << "2. News ����" << endl;
//		cout << "3. News ������Ʈ" << endl;
//		cout << "4. News ��û" << endl;
//		cout << "0. ����" << endl;
//		cout << "���� : ";
//		cin >> Select;
//
//		switch (Select)
//		{
//		case 1:
//		{
//			string customerName;
//			cout << "����� �� �̸��� �Է����ּ��� : ";
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
//			cout << "���ο� ��� ������ �Է� ���ּ��� : ";
//			cin.ignore(); // �Է� ���� ����
//			getline(cin, news); // �� �� ��ü�� �Է� ����
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
//		default: cout << "�߸� �Է� " << endl;
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