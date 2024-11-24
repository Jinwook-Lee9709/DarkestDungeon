#pragma once

class SkillTooltip_RangeUi : public GameObject
{
protected:
	std::vector<sf::CircleShape> circles;
	std::vector<sf::RectangleShape> bars;
public:
	SkillTooltip_RangeUi(const std::string& name = "");
	~SkillTooltip_RangeUi() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void Draw(sf::RenderWindow& window) override;

	void Set(std::vector<short> range);
};
