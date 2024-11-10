#include "stdafx.h"
#include "UiDungeon.h"

UiDungeon::UiDungeon(const std::string& name)
	: GameObject(name)
{
}

void UiDungeon::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiDungeon::SetRotation(float angle)
{
	rotation = angle;
}

void UiDungeon::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiDungeon::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiDungeon::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiDungeon::Init()
{
	windowSize = FRAMEWORK.GetWindowSizeF();
	InitFixedUi(windowSize);
	InitSkillUi(windowSize);
	InitPlayerTextUi(windowSize);

	inventory = new SpriteGo("Resource/Panels/panel_inventory.png");
	SetSpriteInfo(inventory, Origins::BL, { windowSize.x * 0.5f,  windowSize.y * 0.999f }, 0);

	instanceChk = true;
}

void UiDungeon::Release()
{
	for (auto it : fixedUi) {
		it->Release();
		delete(it);
	}
	fixedUi.clear();
	for (auto it : skill) {
		it->Release();
		delete(it);
		it = nullptr;
	}
	
	for (auto it : playerText) {
		it.second->Release();
		delete(it.second);
	}
	playerText.clear();
	instanceChk = false;
}

void UiDungeon::Reset()
{
	if (!instanceChk) {
		Init();
	}
	for (auto it : fixedUi) {
		it->Reset();
	}
	for (auto it : skill) {
		it->Reset();
	}
	for (auto it : playerText) {
		it.second->Reset();
	}
}

void UiDungeon::Update(float dt)
{
	CheckSkillClick();
}

void UiDungeon::Draw(sf::RenderWindow& window)
{
	if (active) {
		for (auto ui : fixedUi) {
			ui->Draw(window);
		}
		for (auto ui : skill) {
			if (ui->IsActive()) {
				ui->Draw(window);
			}
		}
		for (auto ui : playerText) {
			if (ui.second->IsActive()) {
				ui.second->Draw(window);
			}
		}
	}
}

void UiDungeon::SetSpriteInfo(SpriteGo* obj,const Origins& origin, const sf::Vector2f pos,const int& order, const bool& flipX, const bool& flipY)
{
	obj->SetOrigin(origin);
	obj->SetPosition(pos);
	obj->FlipX(flipX);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = order;
}

void UiDungeon::InitFixedUi(const sf::Vector2f& windowSize)
{
	SpriteGo* obj;
	obj = new SpriteGo("Resource/Panels/side_decor.png");
	SetSpriteInfo(obj, Origins::BL, { 0.f, windowSize.y }, 5);
	fixedUi.push_back(obj);
	obj = new SpriteGo("Resource/Panels/side_decor.png");
	SetSpriteInfo(obj, Origins::BL, { windowSize.x, windowSize.y }, 5, true);
	fixedUi.push_back(obj);

	obj = new SpriteGo("Resource/Panels/panel_banner.png");
	SetSpriteInfo(obj, Origins::BC, { windowSize.x * 0.302f, windowSize.y * 0.792f }, 4);
	fixedUi.push_back(obj);

	obj = new SpriteGo("Resource/Panels/panel_hero.png");
	SetSpriteInfo(obj, Origins::BC, { windowSize.x * 0.31f, windowSize.y }, 5);
	fixedUi.push_back(obj);

	obj = new SpriteGo("Resource/Panels/panel_monster.png");
	SetSpriteInfo(obj, Origins::BL, { windowSize.x * 0.493f,  windowSize.y }, 5);
	fixedUi.push_back(obj);
}

void UiDungeon::InitSkillUi(const sf::Vector2f& windowSize)
{
	SpriteGo* obj;
	obj = new SpriteGo("Resource/Heroes/Crusader/Icon/crusader.ability.one.png");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.2885f, windowSize.y * 0.732f }, 5);
	skill[0] = obj;
	obj = new SpriteGo("Resource/Heroes/Crusader/Icon/crusader.ability.two.png");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.3281f, windowSize.y * 0.732f }, 5);
	skill[1] = obj;
	obj = new SpriteGo("Resource/Heroes/Crusader/Icon/crusader.ability.three.png");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.3677f, windowSize.y * 0.732f }, 5);
	skill[2] = obj;
	obj = new SpriteGo("Resource/Heroes/Crusader/Icon/crusader.ability.four.png");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.4075f, windowSize.y * 0.732f }, 5);
	skill[3] = obj;
	obj = new SpriteGo("Resource/Panels/icons_ability/ability_move.png");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.4471f, windowSize.y * 0.732f }, 5);
	skill[4] = obj;
	obj = new SpriteGo("Resource/Panels/icons_ability/ability_pass.png");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.473f, windowSize.y * 0.732f }, 8);
	skill[5] = obj;
	obj = new SpriteGo("Resource/Panels/icons_ability/selected_ability.png");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.2885f, windowSize.y * 0.732f }, 6);
	skill[6] = obj;
	obj->SetActive(false);

}

void UiDungeon::InitPlayerTextUi(const sf::Vector2f& windowSize)
{
	TextGo* obj;
	obj = new TextGo("fonts/LeeB.ttf");
	obj->SetColor(sf::Color::Red);
	obj->SetPosition({ windowSize.x * 0.21f, windowSize.y * 0.81f });
	obj->SetString("50 / 50");
	obj->SetCharacterSize(20);
	obj->SetOrigin(Origins::MR);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;

	playerText.insert({ PlayerTextIndex::HP, obj });
	obj = new TextGo("fonts/LeeB.ttf");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.21f, windowSize.y * 0.837f });
	obj->SetString("3 / 200");
	obj->SetCharacterSize(20);
	obj->SetOrigin(Origins::MR);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::STRESS, obj });

	obj = new TextGo("fonts/LeeB.ttf");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.15f, windowSize.y * 0.865f });
	obj->SetString("ACC");
	obj->SetCharacterSize(18);
	obj->SetOrigin(Origins::ML);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::ACCURACY, obj });

	obj = new TextGo("fonts/LeeB.ttf");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.15f, windowSize.y * 0.885f });
	obj->SetString("CRIT");
	obj->SetCharacterSize(18);
	obj->SetOrigin(Origins::ML);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::CRITICAL, obj });
	obj = new TextGo("fonts/LeeB.ttf");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.15f, windowSize.y * 0.905f });
	obj->SetString("DMG");
	obj->SetCharacterSize(18);
	obj->SetOrigin(Origins::ML);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::DAMAGE, obj });
	obj = new TextGo("fonts/LeeB.ttf");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.15f, windowSize.y * 0.925f });
	obj->SetString("DODGE");
	obj->SetCharacterSize(18);
	obj->SetOrigin(Origins::ML);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::DODGE, obj });

	obj = new TextGo("fonts/LeeB.ttf");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.15f, windowSize.y * 0.945f });
	obj->SetString("PROT");
	obj->SetCharacterSize(18);
	obj->SetOrigin(Origins::ML);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::PROTECT, obj });

	obj = new TextGo("fonts/LeeB.ttf");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.15f, windowSize.y * 0.965f });
	obj->SetString("SPD");
	obj->SetCharacterSize(18);
	obj->SetOrigin(Origins::ML);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::SPEED, obj });

}



void UiDungeon::CheckSkillClick()
{
	if (InputManager::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (int i = 0; i < 5; i++) {
			sf::FloatRect bounds = skill[i]->GetGlobalBounds();
			sf::Vector2f pos = (sf::Vector2f)InputManager::GetMousePosition();
			if (bounds.contains(pos)) {
				skill[6]->SetPosition(skill[i]->GetPosition());
				skill[6]->SetActive(true);
			}
		}
	}
}
