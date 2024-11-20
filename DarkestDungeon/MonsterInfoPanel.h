#pragma once


enum class textId
{
	MonsterName,
	HpText,
	HpValue,
	ProtectText,
	ProtectValue,
	DodgeText,
	DodgeValue,
	SpeedText,
	SpeedValue,
	Resistance,
	ResStunText,
	ResStunValue,
	ResBlightText,
	ResBlightValue,
	ResBleedText,
	ResBleedValue,
	ResDebuffText,
	ResDebuffValue,
	ResMoveText,
	ResMoveValue,
	Skill


};

struct MonsterInfo;

class MonsterInfoPanel : public GameObject
{

protected:
	SpriteGo* panel;
	std::vector<TextGo*> texts;
	std::vector<SpriteGo*> resIcons;



public:
	MonsterInfoPanel(const std::string& name = "");
	~MonsterInfoPanel() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void UpdateInfo(const MonsterInfo& info);
	void SetGoInfo(GameObject* obj, const Origins& origin,
		const sf::Vector2f pos, const int& order,
		const bool& flipX = false, const bool& flipY = false);

	void SetOpacity(int opacity);
};
