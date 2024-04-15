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
	//상속받은 함수 재정의
	void Operation() override
	{
		// *& ??
		for (Component*& component : components)
			component->Operation();
	}

	//컴포넌트 추가
	void AddComponent(Component* component)
	{
		if (component)
			components.push_back(component);
	}

	void RemoveComponent(Component* component)
	{
		if (nullptr == component) return;
		//component와 일치하는 반복자를 찾아서
		auto iter = find(components.begin(), components.end(), component);
		//벡터가 end가 아닐 경우 erase
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


