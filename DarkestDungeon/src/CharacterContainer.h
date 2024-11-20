#pragma once
#include "GameObject.h"
#include "Character.h"
#include "DebuffText.h"
#include "DamageText.h"
#include "Effector.h";

class MonsterContainer;
class DebuffText;

class CharacterContainer :
	public GameObject
{
private:
	Character character;
	Effector stunEffect;

	sf::Sprite spriteSelect;
	sf::RectangleShape hpBar;
	sf::RectangleShape stressBar[10];
	SpriteGo target;

	int currentPos;
	int speed;

	CharacterInfo info;
	DebuffText debuffText;
	DamageText damageText;

	bool selected;
	bool isAlive;
	bool moving;

	std::unordered_map<DebuffType, std::pair<short, int>> debuffStack;

	sf::Vector2f dest;
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

	void ActiavteTargetUi(TargetUi type);
	void DeactiavteTargetUi() { target.SetActive(false); };

	void ChangePos(short pos) { this->currentPos = pos; }
	void MoveToCoord(sf::Vector2f coord);
	void MoveToCoordDouble(sf::Vector2f coord);

	void SetInitialStatus(const json& info);

	void SetToIdle();
	void SetToCombat();
	void SetToWalk();

	void UseSkill(std::vector<CharacterContainer*>& characters, std::vector<MonsterContainer*>& monsters, short user, short target, int num);


	//Getter
	int GetPos() { return currentPos; }
	CharacterInfo& GetCharacterInfo() { return info; }
	std::vector<int> CheckAvailableSkill();
	std::vector<short>& GetSkillRange(int skillnum);
	

	//For Combat
	void OnHit(int damage, float acc);
	void OnDamage(int damage);
	void OnDebuffed(DebuffType type, float acc, int damage= 0, int stack = 1);
	void OnHeal(int amount);

	//About Debuff
	int CheckDebuffCount();
	void PlayDebuffText(DebuffType type);
	void ApplyDebuff();
	void EndStun();
	bool IsStuned();
	
	bool IsAlive() { return isAlive; }
	


};

	

