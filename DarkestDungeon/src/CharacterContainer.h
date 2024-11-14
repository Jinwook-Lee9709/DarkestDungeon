#pragma once
#include "GameObject.h"


struct CharacterInfo
{
	std::string name;
	std::string type;
	int hp;
	int maxHp;
	int stress;
	int speed;
	int dodge;
	float accuracy;
	float critical;
	float minDamage;
	float maxDamage;
	float protect;
	std::string skill1;
	std::string skill2;
	std::string skill3;
	std::string skill4;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(CharacterInfo
		,name, type, hp, maxHp, stress, speed ,dodge,
		accuracy, critical, minDamage, maxDamage, protect, skill1, skill2, skill3, skill4);
};
class CharacterContainer :
	public GameObject
{
private:
	sf::Sprite character;
	Animator animator;
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

	CharacterInfo& GetCharacterInfo() { return info; }
};

	

