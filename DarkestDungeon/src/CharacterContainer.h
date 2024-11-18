#pragma once
#include "GameObject.h"
#include "Character.h"

class MonsterContainer;

class CharacterContainer :
	public GameObject
{
private:

	Character character;

	sf::Sprite spriteSelect;
	sf::RectangleShape hpBar;
	sf::RectangleShape stressBar[10];
	SpriteGo target;

	int currentPos;

	CharacterInfo info;

	bool selected;
	bool isAlive;
	bool moving;

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


	void OnHit(int damage, float acc);
	void OnDebuffed(DebufType type, float acc);
	void OnHeal(int amount);

	bool IsAlive() { return isAlive; }


};

	

