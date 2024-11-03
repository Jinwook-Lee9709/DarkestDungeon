#pragma once
#include "stdafx.h"

class GameObject
{
protected:
	std::string name;
	bool active = true; //determine object run Update, Draw
	sf::Vector2f position;
	sf::Vector2f scale;
	sf::Vector2f origin;
	Origins originPreset;

public:
	SortingLayers sortingLayer = SortingLayers::Default;
	int sortingOrder = 0;

	GameObject(const std::string& name = "");
	virtual ~GameObject();

	const std::string& GetName() const { return name; }
	void SetName(const std::string& n) { name = n; }


	bool IsActive() const { return active; }
	void SetActive(bool a) { active = a; }

	sf::Vector2f GetPosition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }

	sf::Vector2f GetScale() const { return scale; }
	virtual void SetScale(const sf::Vector2f& size) { scale = size; }

	virtual void FlipX(bool flag);
	virtual void FlipY(bool flag);

	sf::Vector2f GetOrigin() const { return origin; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin)
	{
		origin = newOrigin;
		originPreset = Origins::Custom;
	}

	virtual void Init();
	virtual void Release();

	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);


};

struct DrawOrderComparer
{
	bool operator()(GameObject* a, GameObject* b)
	{
		if (a->sortingLayer != b->sortingLayer)
			return a->sortingLayer > b->sortingLayer;
		return a->sortingOrder > b->sortingOrder;
	}
};
