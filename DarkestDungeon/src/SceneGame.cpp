#include "stdafx.h"
#include "SceneGame.h"
#include "Bat.h"
#include "Ball.h"
#include "TextGo.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	bat = AddGo(new Bat("Bat"));
	ball = AddGo(new Ball("Ball"));
	textScore = AddGo(new TextGo("fonts/Sansation.ttf"));
	textScore->SetString("Score: " + std::to_string(score));
	textScore->SetPosition({ 50.f, 50.f });
	textScore->SetCharacterSize(50);
	msMsg = AddGo(new TextGo("fonts/Sansation.ttf"));
	msMsg->SetString("Reset Game by R");
	msMsg->SetPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);
	msMsg->SetOrigin(Origins::MC);
	msMsg->SetCharacterSize(100);

	ball->SetBat(bat);

	Scene::Init();
}

void SceneGame::Enter()
{
	score = 0;
	state = State::play;
	ball->Reset();
	msMsg->SetActive(false);
	FONT_MGR.Load("fonts/Sansation.ttf");
	Scene::Enter();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	if (state == State::play) {
		if (ball->GetIntersect()) {
			Pong();
			ball->ResetIntersect();
		}
		textScore->SetString("Score: " + std::to_string(score));
		if (ball->IsDie()) {
			state = State::gameover;
			msMsg->SetActive(true);
		}
	}
	else if(state == State::gameover){
		if (InputManager::GetKeyDown(sf::Keyboard::R)) {
			bat->Reset();
			ball->Reset();
			msMsg->SetActive(false);
		}

	}
	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::Pong() {
	score += 100;
}
