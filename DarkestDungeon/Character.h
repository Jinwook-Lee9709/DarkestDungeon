#pragma once
#include "GameObject.h"

class Character : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;
public:
	Character(const std::string& name = "");
	~Character() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	virtual void SetToIdle() = 0;
	virtual void SetToCombat() = 0;
	virtual void SetToWalk() = 0;

	virtual void UseSkill1() = 0;
	virtual void UseSkill2() = 0;
	virtual void UseSkill3() = 0;
	virtual void UseSkill4() = 0;


	virtual void OnHit(int damage);


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
