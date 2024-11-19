#pragma once


#pragma once

class DebuffText : public GameObject
{
protected:
	TextGo text;
	SpriteGo icon;

	sf::Vector2f posForAnim;

	std::queue<DebuffType> playQueue;

	float duration = 1;
	float timer;
	bool isPlay;
public:
	DebuffText(const std::string& name = "");
	~DebuffText() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void AddAnimation(DebuffType type);

	void PlayAnimation(DebuffType type);

	void SetDuration(float duration) { this->duration = duration;  }
	void SetText(DebuffType type);
};

