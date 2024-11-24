#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"
#include "BattleManager.h"
#include "ExploreManager.h"
#include "CharacterContainer.h"
#include "MonsterContainer.h"
#include "UiDungeon.h"
#include "ShadowRect.h"
#include <fstream>


SceneDev1::SceneDev1()
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	//Create Containers
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
	AddGo(new ShadowRect("shadow"));
	corridorWall = AddGo(new TileMap("corridorWall"));
	corridorBackground = AddGo(new SpriteGo("dungeon_background", "corridorBackground"));
	corridorBackground->SetOrigin(Origins::MC);
	corridorBackground->SetPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, 400.f });
	corridorBackground->SetScale({3.f, 3.f});
	corridorBackground->sortingLayer = SortingLayers::Background;
	corridorBackground->sortingOrder = -2;
	roomBackground = AddGo(new SpriteGo("room_empty", "roomBackground"));
	roomBackground->SetOrigin(Origins::TC);
	roomBackground->SetPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, 0.f });
	roomBackground->sortingLayer = SortingLayers::Background;
	roomBackground->SetActive(false);


	uiDungeon = AddGo(new UiDungeon());
	uiDungeon->sortingLayer = SortingLayers::UI;

	//Set View 
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);
	popupView.setSize(windowSize);
	popupView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);


	battleManager = new BattleManager(this);
	battleManager->Init();

	exploreManager = new ExploreManager(this);
	exploreManager->Init();
	InitContaierPos(windowSize);





	Scene::Init();
}


void SceneDev1::Enter()
{
	RES_TABLE_MGR.LoadScene("Dev1");
	RES_TABLE_MGR.LoadScene("Ruin");
	SetCharacterInfo();
	LoadCharacterResource();
	LoadMonsterResource();
	LoadEffectResource();
	exploreManager->Reset(&characters, uiDungeon, &characterOrder);
	battleManager->Reset(&characters, &monsters, uiDungeon, &characterOrder);
	beforeStatus = Status::Start;
	currentStatus = Status::Explore;
	Scene::Enter();
}

void SceneDev1::Exit()
{
	RES_TABLE_MGR.UnLoadScene("Dev1");
}

void SceneDev1::Update(float dt)
{
	if (beforeStatus == Status::Start)
	{
		beforeStatus = Status::None;
		for (auto& monster : monsters)
		{
			monster->SetActive(false);
		}
		exploreManager->StartExploreMode();
	}
	switch(currentStatus) {
	case Status::Battle:
		battleManager->Update(dt);
		break;
	case Status::Explore:
		exploreManager->Update(dt);
		break;
	}
	Scene::Update(dt);
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
		characterContainerPos.push_back(sf::Vector2f({ positionBuf, height }));
		characterOrder.push_back(i);
		positionBuf -= block;
	}
	FixedCharacterContainerPos = characterContainerPos;
	positionBuf = windowSize.x * 0.5f + block * 1.5f;;
	for (int i = 0; i < 4; i++) {
		monsterContainerPos1.push_back(sf::Vector2f({ positionBuf, height }));
		positionBuf += block;
	}
	FixedMonsterContainerPos1 = monsterContainerPos1;
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
		characters[i]->ChangePos(i);
		json info = TABLE["Character" + std::to_string(i+1)];

		characters[i]->SetInitialStatus(info);
	}
}

void SceneDev1::LoadCharacterResource()
{
	for (auto& it : characters) {
		RES_TABLE_MGR.LoadSkillIcon(it->GetCharacterInfo().skill1[0]);
		RES_TABLE_MGR.LoadSkillIcon(it->GetCharacterInfo().skill2[0]);
		RES_TABLE_MGR.LoadSkillIcon(it->GetCharacterInfo().skill3[0]);
		RES_TABLE_MGR.LoadSkillIcon(it->GetCharacterInfo().skill4[0]);
		RES_TABLE_MGR.LoadPortrait("portrait" + std::to_string((int)it->GetCharacterInfo().type));
		RES_TABLE_MGR.LoadCharacterAnimation(it->GetCharacterInfo().type);
		RES_TABLE_MGR.LoadCharacterSound(it->GetCharacterInfo().type);
	}

}

void SceneDev1::LoadMonsterResource()
{
	RES_TABLE_MGR.LoadMonsterAnimation();
}

void SceneDev1::LoadEffectResource()
{
	RES_TABLE_MGR.LoadEffectAnimation();
}

std::vector<sf::View*> SceneDev1::GetViews()
{
	std::vector<sf::View*> views;
	views.push_back(&worldView);
	views.push_back(&popupView);
	views.push_back(&uiView);
	return views;
}

void SceneDev1::ChangeCharacterPos(int first, int second)
{
	int firstPos = characters[first]->GetPos();
	int secondPos = characters[second]->GetPos();
	sf::Vector2f firstCoord = characterContainerPos[firstPos];
	sf::Vector2f secondCoord = characterContainerPos[secondPos];
	characters[first]->ChangePos(secondPos);
	characters[second]->ChangePos(firstPos);
	characters[first]->MoveToCoord(secondCoord);
	characters[second]->MoveToCoord(firstCoord);
	characterOrder[firstPos] = second;
	characterOrder[secondPos] = first;
}

void SceneDev1::ResetContainerPos()
{
	characterContainerPos = FixedCharacterContainerPos;
	monsterContainerPos1 = FixedMonsterContainerPos1;
}

void SceneDev1::EnterRoom()
{
	currentStatus = Status::Battle;
	battleManager->StartBattleMode();
}







