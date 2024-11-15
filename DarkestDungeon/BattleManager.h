#pragma once

class SceneDev1;

class CharacterContainer;
class MonsterContainer;
class UiDungeon;



class BattleManager
{
public:
	enum class Status
	{
		JudgeTurn,
		CharacterTurn,
		SkillSelected,
		ItemSelected,
		CharacterAnimate,
		MonsterTurn,
		MonsterAnimate,
	};

private:
	SceneDev1* currenScene;
	UiDungeon* ui;
	Status beforeStatus;
	Status currentStatus;

	json monsterTable;

	std::vector<CharacterContainer*>* characters;
	std::vector<MonsterContainer*>* monsters;

	short currentCharacter;
	short currentMonster;


	std::queue<int> orderQueue;


	struct Compare {
		bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
			if (a.first != b.first) {
				return a.first < b.first;
			}
			return a.second > b.second;
		}
	};
public:
	BattleManager() = default;
	BattleManager(SceneDev1* scene);
	~BattleManager() = default;


	void Init();
	void Reset(std::vector<CharacterContainer*>* characters,
		std::vector<MonsterContainer*>* monsters, UiDungeon* ui);
	void Update(float dt);
	
	void SetMonsterInfo();

	void UpdateJudgeTurn(float dt);
	void UpdateCharacterTurn(float dt);
	void UpdateSkillSelected(float dt);
	void UpdateItemSelected(float dt);
	void UpdateCharacterAnimate(float dt);
	void UpdateMonsterTurn(float dt);
	void UpdateMonsterAnimate(float dt);


};

