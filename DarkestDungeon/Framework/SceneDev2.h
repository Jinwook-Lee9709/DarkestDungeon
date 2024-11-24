#pragma once
#include "Scene.h"

class SkillTooltip;

class SceneDev2 : public Scene
{
protected:
	SkillTooltip* ui;

public:
	SceneDev2();
	~SceneDev2() = default;

	virtual void Init() override;
	virtual void Enter() override;
	virtual void Exit() override;


	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

