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
		None,
		JudgeTurn,
		ApplyDebuff,
		CharacterTurn,
		SkillSelected,
		ItemSelected,
		CharacterAnimate,
		MonsterTurn,
		MonsterAnimate,
		FillEmptyPos,
	};

private:
	SceneDev1* currentScene;
	UiDungeon* ui;
	Status beforeStatus;
	Status currentStatus;

	json monsterTable;

	std::vector<CharacterContainer*>* characters;
	std::vector<MonsterContainer*>* monsters;

	std::vector<int>* chracterOrder;
	std::vector<int> monsterOrder;

	bool isCharacterTurn;
	short currentCharacter;
	short currentMonster;

	int selectedSkill;
	std::vector<short> monsterTargetInfo;

	float timer;
	float duration = 2.f;

	bool monsterSkillSelected;
	bool animationPlaying = false;
	bool isStuned = false;

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
		std::vector<MonsterContainer*>* monsters, UiDungeon* ui, std::vector<int>* chracterOrder);
	void Update(float dt);
	
	void SetMonsterInfo();

	void UpdateJudgeTurn(float dt);
	void UpdateApplyDebuff(float dt);
	void UpdateCharacterTurn(float dt);
	void UpdateSkillSelected(float dt);
	void UpdateItemSelected(float dt);
	void UpdateCharacterAnimate(float dt);
	void UpdateMonsterTurn(float dt);
	void UpdateMonsterAnimate(float dt);
	void UpdateFillEmptyPos(float dt);

	void ResetTargetUi();
	void ChangeTargetUi();

	void ChangeMonsterPos(int first, int second);
};

