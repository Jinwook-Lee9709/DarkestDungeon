#pragma once
#include "GameObject.h"

class Skill;
class Slot;
class CharacterContainer;
class MonsterContainer;
struct MonsterInfo;

class Monster : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;

	Skill* skill;
	Slot* skillSlot;
	int skillCount;

	MonsterType type;
public:
	Monster(const std::string& name = "");
	~Monster() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	virtual void SetToCombat();
	virtual void OnHit(int damage);


	void Reset(const MonsterInfo& info);

	void SetSlot(const MonsterInfo& info);
	void AddSkill(int num);

	void UseSkill(std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target, int num);

};
