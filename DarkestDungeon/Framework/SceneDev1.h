#pragma once
#include "Scene.h"

class BattleManager;
class ExplorerManager;
class CharacterContainer;
class MonsterContainer;
class SpriteGo;
class UiDungeon;


class SceneDev1 : public Scene
{
public:
	enum class Status
	{
		Battle,
		Explore
	};
protected:
	BattleManager* battleManager;

	std::vector<CharacterContainer*> characters;
	std::vector<MonsterContainer*> monsters;

	std::vector<int> characterOrder;

	//Entity Pos;
	std::vector<sf::Vector2f> characterContainerPos;
	std::vector<sf::Vector2f> monsterContainerPos1;
	std::vector<sf::Vector2f> monsterContainerPos2;

	SpriteGo* background;

	Status currentStatus;

	UiDungeon* uiDungeon;
public:
	SceneDev1();
	~SceneDev1() = default;;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	//Init Scene
	void InitContaierPos(sf::Vector2f windowSize);
	void SetCharacterInfo();
	void LoadCharacterResource();
	void LoadMonsterResource();
	//Getter
	UiDungeon* GetUi() { return uiDungeon; }
	std::vector<CharacterContainer*>& GetCharacters() { return characters; }
	std::vector<MonsterContainer*>& GetMonsters() { return monsters; }
	std::vector<sf::Vector2f>& GetCharacterPos() { return characterContainerPos; }
	std::vector<sf::Vector2f>& GetMonsterPos() { return monsterContainerPos1; }
	

	void ChangeCharacterPos(int first, int second);
};
