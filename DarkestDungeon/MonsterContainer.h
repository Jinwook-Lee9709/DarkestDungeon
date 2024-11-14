#pragma once

struct MonsterInfo
{
	std::string name;
	CharacterType type;
	int hp;
	int maxHp;
	int speed;
	int dodge;
	float accuracy;
	float critical;
	float minDamage;
	float maxDamage;
	float protect;
	std::string skill1;
	std::string skill2;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(MonsterInfo
		, name, type, hp, maxHp, speed, dodge,
		accuracy, critical, minDamage, maxDamage, protect, skill1, skill2);
};

class MonsterContainer : public GameObject
{
protected:
	bool isAlive;
	MonsterInfo info;
public:
	MonsterContainer(const std::string& name = "");
	~MonsterContainer() = default;

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


	MonsterInfo& GetMonsterInfo() { return info; }

	void OnHit(int damage, float acc);
	void OnDebuffed(DebufType type, float acc);
	bool IsAlive() { return isAlive; }
};
