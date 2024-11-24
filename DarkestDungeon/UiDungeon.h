#pragma once
#include "NameFrame.h"
#include "SkillTooltip.h"
class SpriteGo;
class TextGo;
class MonsterInfoPanel;
class Torch;

struct MonsterInfo;

enum class PlayerTextIndex {
	ACCURACY,
	CRITICAL,
	DAMAGE,
	DODGE,
	PROTECT,
	SPEED,
	HP,
	STRESS,
	NAME,
	CLASS,
	COUNT
};

class UiDungeon : public GameObject
{
private:
	bool instanceChk = false;

	std::vector<SpriteGo*> fixedUi;

	CharacterInfo characterInfo;
	short currentCharacter;

	SpriteGo* skillButton[7];
	std::bitset<6> isSkillActive;
	std::string SkillTexId[4][4];

	NameFrame skillNameFrame;
	NameFrame victoryTextFrame;
	MonsterInfoPanel* monsterInfoPanel;

	std::unordered_map<PlayerTextIndex, TextGo*> fixedText;
	std::unordered_map<PlayerTextIndex, TextGo*> playerText;

	SpriteGo* portrait;
	SpriteGo* inventory;

	Torch* torch;

	SkillTooltip toolTip;

	float timer;
	float duration = 0.001f;
	bool isFramePlaying = false;
	bool isPanelActive = false;
	bool isVictoryPlaying = false;
	int opacity;

	sf::Vector2f windowSize;
public:
	UiDungeon(const std::string& name = "");
	~UiDungeon() = default;

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

	void SetSpriteInfo(SpriteGo* obj, const Origins& origin,
		const sf::Vector2f pos, const int& order,
		const bool& flipX = false, const bool& flipY = false);

	void InitFixedUi(const sf::Vector2f& windowSize);
	void InitSkillUi(const sf::Vector2f& windowSize);
	void InitPlayerTextUi(const sf::Vector2f& windowSize);

	void PlaySkillNameFrame(const std::string& str);
	void PlayVictoryTextFrame(const std::string& str);
	void UpdateSkillNameFrame(float dt);
	void UpdateVictoryTextFrame(float dt);

	void ChangeCharacterInfo(const CharacterInfo& info,const short& characterNum);
	void ChangeSkillButtonTexture(const CharacterInfo& info);
	void ChangeSkillButtonActive(const std::vector<bool>& list);
	void DeactivateAllSkillButton();
	void UpdateSkillUi();

	int CheckSkillClick();

	void DeactivateSelectBox();
	void DeactivateSkillNameFrame();

	void ShowMonsterInfoPanel(const MonsterInfo& info);
	void HideMonsterInfoPanel();
	bool IsInfoPanelActive();
};
