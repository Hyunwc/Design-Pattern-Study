#pragma once
#include "Observer.h"
#include "Person.h"

//싱글톤으로 구성된 뉴스 클래스
class News : public Subject
{
private:
	static News* instance;
	vector<Observer*> observers;
	string m_date, m_newsinfo;

	News() {}
public:
	static News* getInstance()
	{
		if (instance == nullptr)
			instance = new News();
		return instance;
	}

	static void Release()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	//옵저버 추가
	void Add(Observer* observer) override {
		observers.push_back(observer);
	}

	//옵저버 정보 업데이트
	void notify() override
	{
		for (auto& obs : observers)
		{
			obs->Update(m_newsinfo, m_date);
		}
	}

	//뉴스정보 업데이트
	void UpdateNews(const string& news) {
		//뉴스 내용을 매개변수 news로 업데이트
		m_newsinfo = news;
		m_date = currentDateTime();
	}
	//옵저버 정보 출력
	void ObserverDisplay()
	{
		for (auto& obs : observers)
		{
			obs->ShowDisplay();
		}
	}
	//정보 출력
	void Display()
	{
		int Select;
		while (true)
		{
			cout << "===News===" << endl;
			cout << "1. 고객등록" << endl;
			cout << "2. News 전송" << endl;
			cout << "3. News 업데이트" << endl;
			cout << "4. News 시청" << endl;
			cout << "0. 종료" << endl;
			cout << "선택 : ";
			cin >> Select;

			switch (Select)
			{
			case 1:
			{
				string customerName;
				cout << "등록할 고객 이름을 입력해주세요 : ";
				cin >> customerName;
				Add(new Person(customerName));
				break;
			}
			case 2:
			{
				//옵저버들의 뉴스 업데이트
				notify();
				break;
			}
			case 3:
			{
				//뉴스 업데이트(뉴스 작성한 시간과 뉴스 내용이 업데이트가 전송된다)
				string news;
				cout << "새로운 기사 내용을 입력 해주세요 : ";
				cin.ignore(); // 입력 버퍼 비우기
				getline(cin, news); // 한 줄 전체를 입력 받음
				UpdateNews(news);
				break;
			}
			case 4:
			{
				//옵저버 정보 출력
				ObserverDisplay();
				break;
			}
			case 0:
				return;
			default: cout << "잘못 입력 " << endl;
			}
			system("pause"); system("cls");
		}

	}

	~News()
	{
		for (auto& obs : observers)
		{
			delete obs;
		}
		observers.clear();
	}
};

News* News::instance = nullptr;
