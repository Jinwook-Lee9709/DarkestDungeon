#pragma once
#include "Scene.h"

class CharacterContainer;
class SpriteGo;

class SceneDev1 : public Scene
{
public:
	enum class Status
	{
		Battle,
		Explore
	};
protected:
	Anim animIdle;
	sf::Vector2f characterContainerPos[4]; //for 1 size container
	sf::Vector2f enemyContainerPos1[4];
	sf::Vector2f enemyContainerPos2[3];
	std::vector<CharacterContainer*> characters;
	SpriteGo* background;
public:
	SceneDev1();
	~SceneDev1() = default;;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void InitPos(sf::Vector2f windowSize);
	void InitUIBackground(sf::Vector2f windowSize);

};

