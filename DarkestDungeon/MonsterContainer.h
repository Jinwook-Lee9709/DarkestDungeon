#pragma once
#include "Monster.h"
#include "DebuffText.h"
#include "DamageText.h"
#include "Effector.h"
#include "DebuffIcon.h"

class Monster;

struct MonsterInfo
{
	MonsterType type;
	std::string name;
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
		, type, name, hp, maxHp, speed, dodge,
		accuracy, critical, minDamage, maxDamage, protect, skillCount,
		resistStun, resistBlight, resistBleed, resistDebuff, resistMove,
		skill1, skill2, skill3, skill4);
};

class MonsterContainer : public GameObject
{
protected:
	Monster monster;
	Effector stunEffect;

	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarBackground;
	DebuffIcon debuffIcon;
	SpriteGo target;

	Effector BottomEffector;
	Effector MiddleEffector;
	Effector DeathEffector;

	int currentPos;
	int speed;

	MonsterInfo info;
	//float Timer;
	//float duration;
	DebuffText debuffText;
	DamageText damageText;

	bool isAlive;
	bool moving;
	bool isDying;
	float deathTimer;
	float deathDuration = 1.2f;


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
	void MoveToCoordDouble(sf::Vector2f coord);
    void SetStatus(const json& info);

	void UseSkill(std::vector<CharacterContainer*>& characters, std::vector<MonsterContainer*>& monsters, short user, short target, int num);
	void SetToIdle();
	void SetToDefend();
	void SetToDeath();
	//Getter
	int GetPos() const { return currentPos; }
	MonsterInfo& GetMonsterInfo() { return info; }
	std::vector<int> CheckAvailableSkill();
	std::vector<short>& GetSkillRange(int skillnum);
	
	//For Combat
	bool OnHit(int damage, float acc);
	void OnDamage(int damage);
	void OnDebuffed(DebuffType type, float acc, int damage = 0, int stack = 1);

	void PlayBottomEffect(const std::string& animId, float duration = 2.f);
	void PlayMiddleEffect(const std::string& animId, float duration = 2.f);

	bool CheckDebuffCount();
	void PlayDebuffText(DebuffType type);
	void ApplyDebuff();
	void EndStun();
	bool IsStuned();



	bool IsAlive() { return isAlive; }


};
