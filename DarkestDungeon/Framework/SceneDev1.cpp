#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"
#include "CharacterContainer.h"
#include "MonsterContainer.h"
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
		auto obj = AddGo(new CharacterContainer("container" + std::to_string(i)));
		obj->sortingLayer = SortingLayers::Foreground;
		characters.push_back(obj);
	}
	for (int i = 0; i < 4; i++) {
		auto obj2 = AddGo(new MonsterContainer("container" + std::to_string(i)));
		obj2->sortingLayer = SortingLayers::Foreground;
		monsters.push_back(obj2);
	}
	uiDungeon = AddGo(new UiDungeon());
	background = AddGo(new SpriteGo("room_empty"));
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
	RES_TABLE_MGR.LoadScene("Dev1");
	SetCharacterInfo();
	LoadCharacterResource();
	Scene::Enter();
}

void SceneDev1::Exit()
{
	RES_TABLE_MGR.UnLoadScene("Dev1");

}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
	if (InputManager::GetKeyDown(sf::Keyboard::Num1)) {
		characters[0]->UseSkill(characters, monsters, 1, 0, 2);
	}
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
void SceneDev1::InitContaierPos(sf::Vector2f windowSize)
{
	float block = windowSize.x / 14.f;
	float height = windowSize.y * 0.62f;
	float positionBuf = windowSize.x * 0.5f - block * 1.5f;
	for (int i = 0; i < 4; i++) {
		characterContainerPos[i] = sf::Vector2f({ positionBuf, height });
		positionBuf -= block;
	}

}

void SceneDev1::SetCharacterInfo()
{
	std::ifstream file("tables/character_table.json", std::ios::in);
	if (!file){
		std::cerr << "Failed to Read File";
	}
	json TABLE = json::parse(file);
	file.close();
	for (int i = 0; i < 4; i++) {
		characters[i]->SetPosition(characterContainerPos[i]);
		json info = TABLE["Character" + std::to_string(i+1)];

		characters[i]->SetInitialStatus(info);
	}
}

void SceneDev1::LoadCharacterResource()
{
	for (auto& it : characters) {
		RES_TABLE_MGR.LoadSkillIcon(it->GetCharacterInfo().skill1);
		RES_TABLE_MGR.LoadSkillIcon(it->GetCharacterInfo().skill2);
		RES_TABLE_MGR.LoadSkillIcon(it->GetCharacterInfo().skill3);
		RES_TABLE_MGR.LoadSkillIcon(it->GetCharacterInfo().skill4);
		RES_TABLE_MGR.LoadCharacterAnimation(it->GetCharacterInfo().type);
	}

}





