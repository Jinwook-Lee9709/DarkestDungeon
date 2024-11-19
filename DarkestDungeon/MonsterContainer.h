#pragma once
#include "Monster.h"
#include "DebuffText.h"
#include "DamageText.h"

class Monster;

struct MonsterInfo
{
	MonsterType type;
	int hp;
	int maxHp;
	int speed;
	int dodge;
	float accuracy;
	float critical;
	float minDamage;
	float maxDamage;
	float protect;
	int skillCount;
	float resistStun;
	float resistBlight;
	float resistBleed;
	float resistDebuff;
	float resistMove;
	std::vector<std::string> skill1;
	std::vector<std::string> skill2;
	std::vector<std::string> skill3;
	std::vector<std::string> skill4;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(MonsterInfo
		, type, hp, maxHp, speed, dodge,
		accuracy, critical, minDamage, maxDamage, protect, skillCount,
		resistStun, resistBlight, resistBleed, resistDebuff, resistMove,
		skill1, skill2, skill3, skill4);
};

class MonsterContainer : public GameObject
{
protected:
	Monster monster;

	sf::RectangleShape hpBar;
	SpriteGo target;

	int currentPos;

	MonsterInfo info;
	//float Timer;
	//float duration;
	DebuffText debuffText;
	DamageText damageText;

	bool isAlive;
	bool moving;

	std::unordered_map<DebuffType, std::pair<short, int>> debuffStack;

	sf::Vector2f dest;
	sf::Vector2f originalMonsterScale = { 0.8f, 0.8f };
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
	
	void ActiavteTargetUi(TargetUi type);
	void DeactiavteTargetUi() { target.SetActive(false); };

	void ChangePos(short pos) { this->currentPos = pos; }
	void MoveToCoord(sf::Vector2f coord);

    void SetStatus(const json& info);

	void UseSkill(std::vector<CharacterContainer*>& characters, std::vector<MonsterContainer*>& monsters, short user, short target, int num);
	void SetToIdle();
	//Getter
	int GetPos() const { return currentPos; }
	MonsterInfo& GetMonsterInfo() { return info; }
	std::vector<int> CheckAvailableSkill();
	std::vector<short>& GetSkillRange(int skillnum);

	void OnHit(int damage, float acc);
	void OnDebuffed(DebuffType type, float acc, int damage = 0, int stack = 1);

	bool CheckDebuff();
	bool IsAlive() { return isAlive; }


};
