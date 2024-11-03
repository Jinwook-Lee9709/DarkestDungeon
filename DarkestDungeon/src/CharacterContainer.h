#pragma once
#include "GameObject.h"

enum class Animation {
	idle,
	walk,
	combat,
	skil1,
	skil2,
	skil3,
	skil4
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
	int hp;
	int maxHp;
	int stress;
	int speed;
	float crtical;
	float minDamage;
	float maxDamage;
	float prot;
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
};

	

