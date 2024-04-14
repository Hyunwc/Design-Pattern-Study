#pragma once
#include "Observer.h"

class Person : public Observer
{
private:
	string m_name;
	string m_news;
	string m_date;
public:
	Person(string name) {
		m_name = name;
	}
	void Update(string news, string date) override {
		m_news = news;
		m_date = date;
	}

	void ShowDisplay() override {
		cout << m_date << endl;
		cout << m_news << endl;
		cout << m_name << " °í°´´Ô." << endl;
	}
};
