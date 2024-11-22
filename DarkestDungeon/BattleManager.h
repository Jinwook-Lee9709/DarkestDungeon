#pragma once

class SceneDev1;

class CharacterContainer;
class MonsterContainer;
class UiDungeon;
class ShadowRect;


class BattleManager
{
public:
	enum class Status
	{
		None,
		Start,
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
	std::vector<sf::View*> views;
	UiDungeon* ui;
	Status beforeStatus;
	Status currentStatus;

	json monsterTable;

	ShadowRect* shadow;

	std::vector<CharacterContainer*>* characters;
	std::vector<MonsterContainer*>* monsters;

	std::vector<sf::Vector2f> zoomedChracterPos;
	std::vector<sf::Vector2f> zoomedContainerPos;

	std::vector<int>* characterOrder;
	std::vector<int> monsterOrder;

	bool isCharacterTurn;
	short currentCharacter;
	short currentMonster;

	int selectedSkill;
	short characterTargetInfo;
	std::vector<short> monsterTargetInfo;

	float timer;
	float duration = 2.f;
	float elapsedZoom = 0.f;
	std::queue<float> zoomSnapshot;

	bool monsterSkillSelected;
	bool animationPlaying = false;
	bool isStuned = false;
	bool moveCamera = false;


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

	void StartBattleMode();

	void Init();
	void Reset(std::vector<CharacterContainer*>* characters,
		std::vector<MonsterContainer*>* monsters, UiDungeon* ui, std::vector<int>* chracterOrder);
	void Update(float dt);


	void SetMonsterInfo();

	void UpdateStart(float dt);
	void UpdateJudgeTurn(float dt);
	void UpdateApplyDebuff(float dt);
	void UpdateCharacterTurn(float dt);
	void UpdateSkillSelected(float dt);
	void UpdateItemSelected(float dt);
	void UpdateCharacterAnimate(float dt);
	void UpdateMonsterTurn(float dt);
	void UpdateMonsterAnimate(float dt);
	void UpdateFillEmptyPos(float dt);

	void UpdateMonsterPanel();

	void ResetTargetUi();
	void ChangeTargetUi();

	void ChangeMonsterPos(int first, int second);

	void AnimateView(bool isCharacter);
	void ResetView();
};

