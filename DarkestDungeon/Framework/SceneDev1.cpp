#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"
#include "CharacterContainer.h"
#include "UiDungeon.h"
#include <fstream>


SceneDev1::SceneDev1()
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{	
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	for (int i = 0; i < 4; i++) {
		auto obj = AddGo(new CharacterContainer("character" + std::to_string(i)));
		obj->sortingLayer = SortingLayers::Foreground;
		characters.push_back(obj);
	}
	
	uiDungeon = AddGo(new UiDungeon());
	background = AddGo(new SpriteGo("Resource/Dungeons/crypts.room_wall.empty.png"));
	background->SetOrigin(Origins::TC);
	background->SetPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, 0.f });
	background->sortingLayer = SortingLayers::Background;

	worldView.setSize(windowSize);
	worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);
	InitContaierPos(windowSize);



	Scene::Init();
}


void SceneDev1::Enter()
{
	SCENE_RES_MGR.Load("Dev1");
	SetCharacterInfo();
	Scene::Enter();
}

void SceneDev1::Exit()
{
	SCENE_RES_MGR.UnLoad("Dev1");

}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
	
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
void SceneDev1::InitContaierPos(sf::Vector2f windowSize)
{
	float block = windowSize.x / 14.f;
	float height = windowSize.y * 0.6f;
	float positionBuf = windowSize.x * 0.5f - block * 1.5f;
	for (int i = 0; i < 4; i++) {
		characterContainerPos[i] = sf::Vector2f({ positionBuf, height });
		positionBuf -= block;
	}

}

void SceneDev1::SetCharacterInfo()
{
	std::ifstream file("Config/CHARACTER_TABLE.json", std::ios::in);
	json TABLE = json::parse(file);
	for (int i = 0; i < 4; i++) {
		characters[i]->SetPosition(characterContainerPos[i]);
		json info = TABLE["Character" + std::to_string(i)];
	}
}





