#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class Inven // �̱��� ����
{
private:

    vector<string> items;
    static Inven* instance;
    Inven() { items.push_back("����"); }

public:
    vector<string>& getItems() { return items; }
    static Inven* getInstance()
    {
        if (!instance)
        {
            instance = new Inven();
        }
        return instance;
    }

    void addItem(const string& item)
    {
        items.push_back(item);
    }

    void displayInven()
    {
        cout << "�κ��丮" << endl << "�� ";

        if (!items.empty())
        {
            cout << items[0];
            for (size_t i = 1; i < items.size(); i++)
            {
                cout << "/" << items[i];
            }
        }

        cout << " ��" << endl;
        cout << endl;
    }

    auto back()
    {
        return items;
    }
};

Inven* Inven::instance = nullptr;

void playerHavior(Inven* playerInven) // �÷��̾� �ൿ �Լ�
{
    int choose, count = 0;
    bool endGame = false;
    srand(time(0));

    do // �� 4���� �ൿ�� �����մϴ�. 3������ ������ �� ��� �����մϴ�.
    {
        count++;
        cout << "1) ���� �ɾ��. 2) �κ��丮�� Ȯ���Ѵ� 3) �����Ѵ�." << endl;
        cin >> choose;
        switch (choose)
        {
        case 1:
        {
            string foundItem;

            int randomItem = rand() % 3;

            switch (randomItem)
            {
            case 0:
                foundItem = "��";
                cout << "���� �߰��߽��ϴ�." << endl;
                playerInven->addItem(foundItem);
                break;
            case 1:
                foundItem = "����";
                cout << "���и� �߰��߽��ϴ�." << endl;
                playerInven->addItem(foundItem);
                break;
            case 2:
                foundItem = "����";
                cout << "�ƹ��͵� �߰����� ���Ͽ����ϴ�." << endl;
                break;
            }
            break;
        }
        case 2:
            playerInven->displayInven();
            break;
        case 3:
            cout << "������ �����մϴ�." << endl;
            endGame = true;
            break;
        default:
            cout << "�߸��� �����Դϴ�. �ٽ� �������ּ���." << endl;
            break;
        }

    } while (!endGame && count < 4);
    playerInven->displayInven();
}