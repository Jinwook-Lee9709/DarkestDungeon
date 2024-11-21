#pragma once

class ShadowRect : public GameObject
{
protected:
	sf::RectangleShape rect;
	float currentOpacity = 0;
	float maxOpacity = 150;
	bool isVisible;
public:
	ShadowRect(const std::string& name = "");
	~ShadowRect() = default;

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

	void SetToVisible() { isVisible = true; }
	void SetToInvisible() { isVisible = false; }
};
