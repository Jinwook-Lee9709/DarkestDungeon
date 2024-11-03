#pragma once
#include "GameObject.h"

class Bat;

class Ball :
    public GameObject
{
protected:
    sf::CircleShape body;
    Bat* bat;

	float speed;
    sf::Vector2f direction;
    sf::FloatRect moveableBounds;

	bool isFired = false;
	bool intersect = false;
	bool isDie = false;


public:
	Ball(const std::string& name);
	~Ball() = default;

	void SetPosition(const sf::Vector2f& pos) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire();

	void SetBat(Bat* bat) { this->bat = bat; }

	bool GetIntersect() { return intersect; }
	void ResetIntersect() { intersect = false; }

	bool IsDie() { return isDie; }
};

