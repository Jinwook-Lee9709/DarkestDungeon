#pragma once
#include "Scene.h"

class Bat;
class Ball;
class TextGo;

enum class State{
	play,
	gameover
};

class SceneGame : public Scene
{
private:
	Bat* bat;
	Ball* ball;
	TextGo* textScore;
	TextGo* msMsg;
	State state;

	int score;
public:
	SceneGame();
	~SceneGame() = default;
private:
	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Pong();
};

