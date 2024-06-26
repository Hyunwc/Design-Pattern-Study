#include<iostream>
#include<string>
#define max_len 100
using namespace std;

class Student
{
private:
	string name;
	int kor, eng, math, sum;
	float avg;
	int num;
	char Class;
public:
	Student() { num = 0; }
	~Student() {}
	void SetStudent(int _num);
	void showStudent();
	int getnum()
	{
		return num;
	}
	string getname()
	{
		return name;
	}
	char getClass()
	{
		return Class;
	}
};

void Student::SetStudent(int _num)
{
	cout << "이름을 입력 하시오 : ";
	cin >> name;
	cout << "3과목의 점수를 입력하시오" << endl;
	cout << "국어 : ";
	cin >> kor;
	cout << "영어 : ";
	cin >> eng;
	cout << "수학 : ";
	cin >> math;
	sum = kor + eng + math;
	avg = (float)sum / 3;
	num = _num;
	if (avg >= 90)
		Class = 'A';
	else if (avg >= 80)
		Class = 'B';
	else if (avg >= 70)
		Class = 'C';
	else if (avg >= 60)
		Class = 'D';
	else
		Class = 'F';
	return;
}

void Student::showStudent()
{
	cout << "----------------------" << endl;
	cout << num << "번 학생" << endl;
	cout << "이름 : " << name << endl;
	cout << "국어 점수 : " << kor << endl << "수학 점수 : " << math << endl << "영어 점수 : " << eng << endl;
	cout << "합계 점수 : " << sum << "\t 평균점수 : " << avg << endl;
	cout << "등급 : [ " << Class << "]" << endl << endl;
	return;
}

class Std_manager {
private:
	Student* std[30];
	//정적 멤버 변수
	static Std_manager* std_manager;
	//외부에서 인스턴스 생성하지 못하게 private로 제한
	Std_manager();
public:
	//nullptr인 경우에만 새로운 메모리 할당 아니면 반환
	static Std_manager* get_Instance()
	{
		if (std_manager == nullptr) std_manager = new Std_manager;
		return std_manager;
	}
	static void Release()
	{
		if (std_manager)
		{
			delete std_manager;
			std_manager = nullptr;
		}
	}
	void display();
	void setStudent();
	void showStudent();
	void findNumber();
	void findname();
	void findClass();
	~Std_manager()
	{
		for (int i = 0; i < 30; i++)
		{
			delete std[i];
		}
	}

};

Std_manager::Std_manager()
{
	for (int i = 0; i < 30; i++)
		std[i] = new Student;
}

Std_manager* Std_manager::std_manager = nullptr;

void Std_manager::display() {
	int sel;
	while (true)
	{
		cout << "=========================" << endl;
		cout << "   1.학생 등록" << endl;
		cout << "   2.전체 학생정보 출력" << endl;
		cout << "   3.학생 번호 검색" << endl;
		cout << "   4.학생 이름 검색" << endl;
		cout << "   5.등급별 출력" << endl;
		cout << "   0.종료" << endl;
		cout << "=========================" << endl;
		cin >> sel;
		switch (sel) {
		case 1:
			setStudent();
			break;
		case 2:
			showStudent();
			break;
		case 3:
			findNumber();
			break;
		case 4:
			findname();
			break;
		case 5:
			findClass();
			break;
		case 0:
			return;
		default:cout << "잘못 입력 " << endl;
		}
		system("pause"); system("cls");
	}
}

void Std_manager::setStudent()
{
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getnum() == 0)
		{
			std[i]->SetStudent(i + 1);
			return;
		}
	}
	cout << "학생이 전원 등록 되었습니다." << endl;
}

void Std_manager::showStudent()
{
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getnum() != 0)
		{
			std[i]->showStudent();
		}
		else
			return;
	}
}

void Std_manager::findNumber()
{
	int _find;
	cout << "찾을 학생의번호를 입력 하시오";
	cin >> _find;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getnum() == _find)
		{
			std[i]->showStudent();
			return;
		}
	}
	cout << endl << "해당 번호의 학생이 없습니다." << endl;
}

void Std_manager::findname()
{
	string _find;
	int find_num = 0;
	cout << "찾을 학생의이름을 입력 하시오";
	cin >> _find;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getname() == _find)
		{
			std[i]->showStudent();
			find_num++;
		}
	}
	if (find_num == 0)
		cout << "해당 이름의 학생이 없습니다." << endl;
}

void Std_manager::findClass()
{
	int _find = 0;
	cout << "========= [ A ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'A')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "총 " << _find << "명" << endl;
	cout << "=========================" << endl << endl << endl;
	_find = 0;
	cout << "========= [ B ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'B')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "총 " << _find << "명" << endl;
	cout << "=========================" << endl;
	_find = 0;
	cout << "========= [ C ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'C')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "총 " << _find << "명" << endl;
	cout << "=========================" << endl;
	_find = 0;
	cout << "========= [ D ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'D')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "총 " << _find << "명" << endl;
	cout << "=========================" << endl;
	_find = 0;
	cout << "========= [ F ] =========" << endl;
	for (int i = 0; i < 30; i++)
	{
		if (std[i]->getClass() == 'F')
		{
			std[i]->showStudent();
			_find++;
		}
	}
	cout << "총 " << _find << "명" << endl;
	cout << "=========================" << endl;

}



int main() {
	//Std_manager* Std_Manager = Std_manager::get_Instance();
	Std_manager::get_Instance()->display();
	//메모리가 해제가 되어야 소멸자가 호출되기 때문에
	//반드시 소멸자에서 해제가 아닌 함수내에서 해제하자
	Std_manager::Release();
	
	return 0;
}