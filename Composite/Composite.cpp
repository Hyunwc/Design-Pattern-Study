#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// 게임 엔터티를 표현하는 인터페이스
class Entity
{
public:
    virtual void display() const = 0;  // 엔터티 정보 출력을 위한 가상 함수
    virtual int getHealth() const = 0;  // 현재 체력 반환을 위한 가상 함수
    virtual void takeDamage(int damage) = 0;  // 데미지를 받아 체력을 감소시키는 가상 함수
    virtual void attack(Entity& target) = 0;  // 대상 엔터티를 공격하는 가상 함수
    virtual string getName() const = 0;  // 엔터티 이름 반환을 위한 가상 함수
    virtual ~Entity() {}  // 가상 소멸자
};

// 컴포지트 패턴을 적용한 게임 엔터티 복합 객체
class CompositeEntity : public Entity
{
private:
    vector<Entity*> entities;

public:
    // 엔터티 추가
    void addEntity(Entity* entity)
    {
        entities.push_back(entity);
    }

    // 현재 복합 객체 상태 출력
    void display() const override
    {
        for (const auto& entity : entities)
        {
            entity->display();
        }
    }

    // 모든 엔터티의 총 체력 반환
    int getHealth() const override
    {
        int totalHealth = 0;
        for (const auto& entity : entities)
        {
            totalHealth += entity->getHealth();
        }
        return totalHealth;
    }

    // 모든 엔터티에게 데미지 입힘
    void takeDamage(int damage) override
    {
        for (auto& entity : entities)
        {
            entity->takeDamage(damage);
        }
    }

    // 모든 엔터티가 대상 엔터티를 공격
    void attack(Entity& target) override
    {
        for (auto& entity : entities)
        {
            if (entity != &target)
            {
                entity->attack(target);
            }
        }
    }

    // 게임 엔터티의 이름 반환 (사용되지 않음)
    string getName() const override
    {
        return "";
    }

    // 모든 엔터티 삭제
    ~CompositeEntity()
    {
        for (auto& entity : entities)
        {
            delete entity;
        }
    }
};

// 기본 엔터티 구현 클래스
class BasicEntity : public Entity
{
private:
    string name;
    int health;

public:
    // 생성자: 이름 설정 및 초기 체력 100으로 설정
    BasicEntity(const string& n) : name(n), health(100) {}

    // 엔터티 정보 출력
    void display() const override
    {
        cout << name << "의 체력: " << health << endl;
    }

    // 현재 체력 반환
    int getHealth() const override
    {
        return health;
    }

    // 데미지를 받아 체력을 감소시키고, 체력이 0 이하면 격파 메시지 출력
    void takeDamage(int damage) override
    {
        health -= damage;
        if (health <= 0)
        {
            health = 0; // 음수가 아닌 0으로 설정
            cout << name << "이(가) 격파되었습니다!" << endl;
        }
    }

    // 대상 엔터티를 공격하고, 랜덤한 데미지를 입힘
    void attack(Entity& target) override
    {
        int damage = rand() % 10 + 1;  // 1에서 10까지의 랜덤한 데미지
        cout << name << "이(가) " << target.getName() << "을(를) 공격합니다!\n데미지: " << damage << endl;
        target.takeDamage(damage);
    }

    // 엔터티 이름 반환
    string getName() const override
    {
        return name;
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    // 플레이어 이름 입력
    cout << "플레이어 이름: ";
    string playerName;
    getline(cin, playerName);

    // 게임을 나타내는 엔터티 생성
    CompositeEntity gameEntity;

    // 캐릭터와 몬스터 생성 및 게임 엔터티에 추가
    Entity* character = new BasicEntity(playerName);
    Entity* monster = new BasicEntity("몬스터");
    gameEntity.addEntity(character);
    gameEntity.addEntity(monster);

    // 초기 상태 표시
    cout << "\n초기 Hp 상태:" << endl;
    gameEntity.display();

    // 게임 루프
    while (character->getHealth() > 0 && monster->getHealth() > 0)
    {
        cout << "\n게임 턴:" << endl;
        gameEntity.attack(*character);
        gameEntity.attack(*monster);
        gameEntity.display();
    }

    // 게임 종료 메시지 출력
    if (character->getHealth() <= 0)
    {
        cout << "\nGame Over - 몬스터 승리!" << endl;
    }
    else
    {
        cout << "\nVictory - 플레이어 승리!" << endl;
    }

    return 0;
}