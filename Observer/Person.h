#pragma once
#include "Observer.h"

class Person : public Observer
{
private:
	string m_name, m_news, m_date;
public:
	Person(string name) {
		m_name = name;
	}
	void Update(const string& news, const string& date) override {
		m_news = news;
		m_date = date;
	}

	void ShowDisplay() override {
		cout << m_date << endl;
		cout << m_news << endl;
		cout << m_name << " °í°´´Ô." << endl;
	}
};
