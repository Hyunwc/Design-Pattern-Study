#pragma once
#include "Observer.h"
#include "Person.h"

//�̱������� ������ ���� Ŭ����
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

	//������ �߰�
	void Add(Observer* observer) override {
		observers.push_back(observer);
	}

	//������ ���� ������Ʈ
	void notify() override
	{
		for (auto& obs : observers)
		{
			obs->Update(m_newsinfo, m_date);
		}
	}

	//�������� ������Ʈ
	void UpdateNews(const string& news) {
		//���� ������ �Ű����� news�� ������Ʈ
		m_newsinfo = news;
		m_date = currentDateTime();
	}
	//������ ���� ���
	void ObserverDisplay()
	{
		for (auto& obs : observers)
		{
			obs->ShowDisplay();
		}
	}
	//���� ���
	void Display()
	{
		int Select;
		while (true)
		{
			cout << "===News===" << endl;
			cout << "1. �����" << endl;
			cout << "2. News ����" << endl;
			cout << "3. News ������Ʈ" << endl;
			cout << "4. News ��û" << endl;
			cout << "0. ����" << endl;
			cout << "���� : ";
			cin >> Select;

			switch (Select)
			{
			case 1:
			{
				string customerName;
				cout << "����� �� �̸��� �Է����ּ��� : ";
				cin >> customerName;
				Add(new Person(customerName));
				break;
			}
			case 2:
			{
				//���������� ���� ������Ʈ
				notify();
				break;
			}
			case 3:
			{
				//���� ������Ʈ(���� �ۼ��� �ð��� ���� ������ ������Ʈ�� ���۵ȴ�)
				string news;
				cout << "���ο� ��� ������ �Է� ���ּ��� : ";
				cin.ignore(); // �Է� ���� ����
				getline(cin, news); // �� �� ��ü�� �Է� ����
				UpdateNews(news);
				break;
			}
			case 4:
			{
				//������ ���� ���
				ObserverDisplay();
				break;
			}
			case 0:
				return;
			default: cout << "�߸� �Է� " << endl;
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
