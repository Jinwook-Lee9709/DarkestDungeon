#pragma once
#include "GameObject.h"
class Bat :
    public GameObject
{
protected:
    sf::RectangleShape body;

    float speed = 500.f;
	sf::Vector2f direction;
	sf::Vector2f initPos;

	float minX = 0.f;
	float maxX = 0.f;

public:
	Bat(const std::string& name);
	~Bat() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override { this->scale = scale; }

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetGlobaBounds() { return body.getGlobalBounds(); }

};

