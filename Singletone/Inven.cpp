#include "Singleton.h"

void EnhanceItem(Inven* playerInven) // ��ȭ �Լ�
{
    vector<string>& items = playerInven->getItems();

    string ItemName;
    bool WeaponCheck = false;

    while (!WeaponCheck) // ������ ���� �ݺ���
    {
        cout << "��ȭ�� �������� �����ϼ��� (�� �Ǵ� ����): ";
        cin >> ItemName;

        if (ItemName == "��" || ItemName == "����")
        {
            WeaponCheck = true;
        }
        else
        {
            cout << "�ٽ� �Է����ּ���." << endl;
        }
    }

    int itemCount = count(items.begin(), items.end(), ItemName);

    if (ItemName == "��") // ���� �������� ��
    {
        if (itemCount == 2) // 2���� +1������
        {
            items.erase(remove(items.begin(), items.end(), ItemName), items.end());
            items.push_back(ItemName + "+1");
        }
        else if (itemCount == 3) // 3���� +2������
        {
            items.erase(remove(items.begin(), items.end(), ItemName), items.end());
            items.push_back(ItemName + "+2");
        }
        else if (itemCount > 3)  // 4���̻��� +3������
        {
            items.erase(remove(items.begin(), items.end(), ItemName), items.end());
            items.push_back(ItemName + "+3");
        }
    }
    else if (ItemName == "����") // �˰� ����
    {
        if (itemCount == 2)
        {
            items.erase(remove(items.begin(), items.end(), ItemName), items.end());
            items.push_back(ItemName + "+1");
        }
        else if (itemCount == 3)
        {
            items.erase(remove(items.begin(), items.end(), ItemName), items.end());
            items.push_back(ItemName + "+2");
        }
        else if (itemCount > 3)
        {
            items.erase(remove(items.begin(), items.end(), ItemName), items.end());
            items.push_back(ItemName + "+3");
        }
    }
}

void chooseWeapon(Inven* playerInven) // ���� ���� �Լ�
{
    playerInven->displayInven();


    bool foundWeapon = false;

    while (!foundWeapon)
    {
        cout << "���⸦ �����ϼ���: ";
        string weapon;
        cin >> weapon;
        for (const auto& item : playerInven->getItems())
        {
            if (item == weapon)
            {
                foundWeapon = true;
                cout << weapon << " ���⸦ �����Ͽ����ϴ�. " << endl;
                break;
            }
        }
        if (!foundWeapon)
        {
            cout << "�κ��丮�� �ش� ���Ⱑ �����ϴ�." << endl;
        }
    }
}

int main()
{
    Inven* PlayerInven = Inven::getInstance();
    Inven* PetInven = Inven::getInstance();

    cout << "�÷��̾ Ȱ���մϴ�." << endl; // �÷��̾ �����Դϴ�.
    playerHavior(PlayerInven);

    cout << endl;

    cout << "���� Ȱ���մϴ�." << endl; // ���� �����Դϴ�.
    playerHavior(PetInven);

    cout << endl;

    EnhanceItem(PlayerInven);

    cout << endl;

    chooseWeapon(PlayerInven);
    return 0;
}