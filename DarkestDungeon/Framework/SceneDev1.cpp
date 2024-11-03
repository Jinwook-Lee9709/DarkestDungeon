#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"
#include "CharacterContainer.h"



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
	background = AddGo(new SpriteGo("Resource/Dungeons/crypts.room_wall.empty.png"));
	background->SetOrigin(Origins::TC);
	background->SetPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, 0.f });
	background->sortingLayer = SortingLayers::Background;
	InitPos(windowSize);
	InitUIBackground(windowSize);


	Scene::Init();
}

void SceneDev1::Enter()
{
	SCENE_RES_MGR.Load("Dev1");
	for (int i = 0; i < 4; i++) {
		characters[i]->SetPosition(characterContainerPos[i]);
	}
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

void SceneDev1::InitPos(sf::Vector2f windowSize)
{
	float block = windowSize.x / 14.f;
	float height = windowSize.y * 0.6f;
	float positionBuf = windowSize.x * 0.5f - block * 1.5f;
	for (int i = 0; i < 4; i++) {
		characterContainerPos[i] = sf::Vector2f({ positionBuf, height });
		positionBuf -= block;
	}
	

}

void SceneDev1::InitUIBackground(sf::Vector2f windowSize)
{
	auto decor1 = AddGo(new SpriteGo("Resource/Panels/side_decor.png"));
	decor1->SetOrigin(Origins::BL);
	decor1->SetPosition({ 0.f, windowSize.y });
	decor1->sortingLayer = SortingLayers::UI;
	decor1->sortingOrder = 5;
	auto decor2 = AddGo(new SpriteGo("Resource/Panels/side_decor.png"));
	decor2->SetOrigin(Origins::BL);
	decor2->FlipX(true);
	decor2->SetPosition({ windowSize.x, windowSize.y });
	decor2->sortingLayer = SortingLayers::UI;
	decor2->sortingOrder = 5;	
	auto banner = AddGo(new SpriteGo("Resource/Panels/panel_banner.png"));
	banner->SetOrigin(Origins::BC);
	banner->SetPosition({ windowSize.x * 0.302f, windowSize.y * 0.792f });
	banner->SetScale({ 1.f,1.f });
	decor2->sortingLayer = SortingLayers::UI;
	decor2->sortingOrder = 4;
	auto hero = AddGo(new SpriteGo("Resource/Panels/panel_hero.png"));
	hero->SetOrigin(Origins::BC);
	hero->SetPosition({ windowSize.x * 0.31f, windowSize.y });
	decor2->sortingLayer = SortingLayers::UI;
	decor2->sortingOrder = 5;
	auto monster = AddGo(new SpriteGo("Resource/Panels/panel_monster.png"));
	monster->SetOrigin(Origins::BL);
	monster->SetPosition({ windowSize.x * 0.493f,  windowSize.y });
	monster->sortingLayer = SortingLayers::UI;
	monster->sortingOrder = 5;
	auto inventory = AddGo(new SpriteGo("Resource/Panels/panel_inventory.png"));
	inventory->SetOrigin(Origins::BL);
	inventory->SetPosition({ windowSize.x * 0.5f,  windowSize.y * 0.999f });
	inventory->sortingLayer = SortingLayers::UI;
	inventory->sortingOrder = 0;
}



