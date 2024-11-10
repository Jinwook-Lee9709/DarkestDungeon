#pragma once
#include "GameObject.h"

enum class Animation {
	IDLE,
	WALK,
	COMBAT,
	SKILL_ONE,
	SKILL_TWO,
	SKILL_THREE,
	SKILL_FOUR,
	HIT,
};

class Anim;

class CharacterContainer :
	public GameObject
{
private:
	std::string characterName;
	sf::Sprite character;
	sf::Sprite spriteSelect;
	sf::RectangleShape hpBar;
	sf::RectangleShape stressBar[10];
	CharacterInfo info;
	bool selected;

	sf::Vector2f originalCharacterScale = { 0.8f, 0.8f };
public:
	CharacterContainer(const std::string& name = "");
	virtual ~CharacterContainer();

	virtual void SetPosition(const sf::Vector2f& pos);
	virtual void SetScale(const sf::Vector2f& size);

	virtual void FlipX(bool flag);
	virtual void FlipY(bool flag);
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin);
	virtual void Init();
	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	void SetInitialStatus(const json& info);
};

	

