#pragma once

class Torch : public GameObject
{
protected:
	sf::Sprite torchSprite;
	Animator animator;
	SpriteGo vignetteOverlay;
	short torchLevel;
public:
	Torch(const std::string& name = "");
	~Torch() = default;

	void SetPosition(const sf::Vector2f& pos) override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void IncreaseLevel();
	void DecreaseLevel();
	void UpdateEffect();
};
