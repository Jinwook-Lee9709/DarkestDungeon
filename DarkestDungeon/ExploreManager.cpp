#include "stdafx.h"
#include "ExploreManager.h"
#include "CharacterContainer.h"
#include "SceneDev1.h"
#include "UiDungeon.h"
#include "ShadowRect.h"

ExploreManager::ExploreManager(SceneDev1* scene)
{
	this->currentScene = scene;
}

void ExploreManager::StartExploreMode()
{
	beforeStatus = Status::Start;
	currentStatus = Status::Idle;
}

void ExploreManager::Init()
{
}

void ExploreManager::Release()
{
}

void ExploreManager::Reset(std::vector<CharacterContainer*>* characters, UiDungeon* ui, std::vector<int>* chracterOrder)
{
	this->characters = characters;
	this->characterOrder = chracterOrder;
	this->ui = ui;
	views = currentScene->GetViews();
	characterContainerPos = &currentScene->GetCharacterPos();
	monsterContainerPos = &currentScene->GetMonsterPos();
	SetCorridorBackground();
}

void ExploreManager::Update(float dt)
{
	if (beforeStatus == Status::Start)
	{
		SetCorridorInfo();
		beforeStatus = Status::None;
	}
	switch (currentStatus)
	{
		case Status::Idle:
		{
			UpdateIdle(dt);
			break;
		}
		case Status::EnterRoom:
		{
			UpdateEnterRoom(dt);
			break;
		}
	}
}

void ExploreManager::UpdateIdle(float dt)
{
	float speed;
	if ((speed = InputManager::GetAxis(Axis::horizontal)) != 0)
	{
		if (!isMoving)
		{
			isMoving = true;
			for (auto& character : (*characters))
			{
				character->SetToWalk();
			}
		}
		float moveAmount = 500 * dt * speed;
		sf::Vector2f currentViewCenter = views[0]->getCenter();


		if ((*characterContainerPos)[3].x + moveAmount < playableBounds.first + 50.f)
		{
			moveAmount = (*characterContainerPos)[3].x - (playableBounds.first + 50.f);
		}
		else if ((*characterContainerPos)[0].x + moveAmount > playableBounds.second - 50.f)
		{
			moveAmount = (*characterContainerPos)[0].x - (playableBounds.second - 50.f);
		}
	
		for (auto& pos : (*characterContainerPos))
		{
			pos += sf::Vector2f(moveAmount, 0.f);
		}
		for (auto& character : (*characters))
		{
			sf::Vector2f pos = character->GetPosition();
			character->SetPosition(pos + sf::Vector2f(moveAmount, 0.f ));
		}
		for (auto& pos :(*monsterContainerPos))
		{
			pos += sf::Vector2f(moveAmount, 0.f);
		}
		float currentDistance = (views[0]->getCenter().x - (*characterContainerPos)[0].x);
		if (cameraThreshold.first < currentDistance && currentDistance < cameraThreshold.second)
		{
			sf::Vector2f newPos = { (*characterContainerPos)[0].x + cameraDistance, currentViewCenter.y };
			newPos.x = Utils::Clamp(newPos.x, cameraCenterBounds.first, cameraCenterBounds.second);
			views[0]->setCenter(newPos);

			background->SetPosition(views[0]->getCenter());
		}
	}
	else
	{
		if (isMoving)
		{
			isMoving = false;
			for (auto& character : (*characters))
			{
				character->SetToIdle();
			}
		}
	}
	for (auto& door : doors)
	{
		if (door->IsHover(currentScene->ScreenToWorld(InputManager::GetMousePosition())))
		{
			door->ChangeTexture("door_close_hover");
		}else
		{
			door->ChangeTexture("door_close");
		}
	}
	if (doors[1]->IsClicked(currentScene->ScreenToWorld(InputManager::GetMousePosition())))
	{
		doors[1]->ChangeTexture("door_open");
		shadow->SetToVisible();
		for (auto& character : (*characters))
		{
			character->SetToIdle();
		}
		currentStatus = Status::EnterRoom;
	}


}

void ExploreManager::UpdateEnterRoom(float dt)
{
	shadow->SetPosition(views[0]->getCenter());
	if (!shadow->IsChanging())
	{
		currentScene->EnterRoom();
	}
}

void ExploreManager::Draw(sf::RenderWindow& window)
{
}

void ExploreManager::SetCorridorInfo()
{
	TileMap* map = dynamic_cast<TileMap*>(currentScene->FindGo("corridorWall"));
	sf::FloatRect bounds = map->GetGlobalBounds();
	playableBounds = { bounds.left, bounds.left + bounds.width };
	cameraCenterBounds = { playableBounds.first + FRAMEWORK.GetWindowSizeF().x * 0.5f,
	playableBounds.second - FRAMEWORK.GetWindowSizeF().x * 0.5f };
	cameraDistance = views[0]->getCenter().x - (*characterContainerPos)[0].x;
	cameraThreshold = { cameraDistance - 4.f, cameraDistance + 4.f };
	auto obj = currentScene->AddGo(new SpriteGo("door_close","door1"));
	obj->SetOrigin(Origins::BC);
	obj->SetPosition({ (playableBounds.first + 365.f),bounds.height - 95.f });
	obj->sortingLayer = SortingLayers::Background;
	obj->Reset();
	doors.push_back(obj);
	obj = currentScene->AddGo(new SpriteGo("door_close","door2"));
	obj->SetOrigin(Origins::BC);
	obj->SetPosition({ (playableBounds.second - 355.f),bounds.height - 95.f });
	obj->sortingLayer = SortingLayers::Background;
	obj->Reset();
	doors.push_back(obj);

	shadow = dynamic_cast<ShadowRect*>(currentScene->FindGo("shadow"));
	shadow->SetMaxOpacity(255);
	ui->ChangeCharacterInfo((*characters)[0]->GetCharacterInfo());
	ui->ChangeSkillButtonTexture((*characters)[0]->GetCharacterInfo());
	ui->DeactivateAllSkillButton();
}

void ExploreManager::SetCorridorBackground()
{
	TileMap* tilemap = dynamic_cast<TileMap*>(currentScene->FindGo("corridorWall"));
	background = dynamic_cast<SpriteGo*>(currentScene->FindGo("corridorBackground"));
	background->SetPosition(views[0]->getCenter());
	tilemap->Reset();

}
