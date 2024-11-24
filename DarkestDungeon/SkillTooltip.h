#pragma once

#include "SkillTooltip_RangeUi.h"

class CharacterContainer;

class SkillTooltip : public GameObject
{
protected:
	short skillType;
	sf::Vector2f defaultPlateSize = { 140.f, 40.f };

	sf::RectangleShape plate;
	SkillTooltip_RangeUi rangeUi;
	std::vector<TextGo*> text;
	ObjectPool<TextGo> textPool;

	std::vector<CharacterContainer*> characters;

	float frameMargin = 10.f;
	sf::Vector2f verticalSpace = {0.f, 20.f};
	float characterSpace = 4.f;

public:
	SkillTooltip(const std::string& name = "");
	~SkillTooltip() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Set(const CharacterInfo& info, const short& characterNum, const short& skillNum);
};
