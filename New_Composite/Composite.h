#pragma once
#include "Mecro.h"

//Component

__interface Component { void Operation(); };

// Composite

class GameObject : public Component
{
private:
	vector<Component*> components;
public:
	//��ӹ��� �Լ� ������
	void Operation() override
	{
		// *& ?? (*Component)& �� ����.
		for (Component*& component : components)
			component->Operation();
	}

	//������Ʈ �߰�
	void AddComponent(Component* component)
	{
		//component�� nullptr�� �ƴҶ� ���Ϳ� ����
		if (component)
			components.push_back(component);
	}

	void RemoveComponent(Component* component)
	{
		if (nullptr == component) return;
		//component�� ��ġ�ϴ� �ݺ��ڸ� ã�Ƽ�
		auto iter = find(components.begin(), components.end(), component);
		//���Ͱ� end�� �ƴ� ��� erase
		if (components.end() != iter) components.erase(iter);
	}
};

//Leaf

class PlayerInput : public Component
{
public:
	void Operation() override { cout << "User Input" << endl; }
};

class EnemyInput : public Component
{
public:
	void Operation() override { cout << "AI Processing" << endl; }
};

class Physics : public Component
{
public:
	void Operation() override { cout << "Physics Processing" << endl; }
};

class Graphics : public Component
{
public:
	void Operation() override { cout << "Graphics Processing" << endl; }
};


