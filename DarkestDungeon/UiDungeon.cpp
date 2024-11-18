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

	skillNameFrame.SetPosition({ 0.7f * FRAMEWORK.GetWindowSizeF().x, 0.2f * FRAMEWORK.GetWindowSizeF().y });

	instanceChk = true;
}

void UiDungeon::Release()
{
	for (auto it : fixedUi) {
		it->Release();
		delete(it);
	}
	fixedUi.clear();
	for (auto it : skillButton) {
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
	for (auto it : skillButton) {
		it->Reset();
	}
	for (auto it : playerText) {
		it.second->Reset();
	}
	skillNameFrame.Reset();
	skillNameFrame.SetActive(false);
}

void UiDungeon::Update(float dt)
{
	CheckSkillClick();
	if (isFramePlaying) {
		UpdateSkillNameFrame(dt);
	}

}

void UiDungeon::Draw(sf::RenderWindow& window)
{
	if (active) {
		for (auto ui : fixedUi) {
			ui->Draw(window);
		}
		for (auto ui : skillButton) {
			if (ui->IsActive()) {
				ui->Draw(window);
			}
		}
		for (auto ui : playerText) {
			if (ui.second->IsActive()) {
				ui.second->Draw(window);
			}
		}
		skillNameFrame.Draw(window);
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
	obj = new SpriteGo("side_decor");
	SetSpriteInfo(obj, Origins::BL, { 0.f, windowSize.y }, 5);
	fixedUi.push_back(obj);
	obj = new SpriteGo("side_decor");
	SetSpriteInfo(obj, Origins::BL, { windowSize.x, windowSize.y }, 5, true);
	fixedUi.push_back(obj);

	obj = new SpriteGo("panel_banner");
	SetSpriteInfo(obj, Origins::BC, { windowSize.x * 0.302f, windowSize.y * 0.792f }, 4);
	fixedUi.push_back(obj);

	obj = new SpriteGo("panel_hero");
	SetSpriteInfo(obj, Origins::BC, { windowSize.x * 0.31f, windowSize.y }, 5);
	fixedUi.push_back(obj);

	obj = new SpriteGo("panel_monster");
	SetSpriteInfo(obj, Origins::BL, { windowSize.x * 0.493f,  windowSize.y }, 5);
	fixedUi.push_back(obj);
}

void UiDungeon::InitSkillUi(const sf::Vector2f& windowSize)
{
	SpriteGo* obj;
	obj = new SpriteGo("crusader_ability_one");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.2885f, windowSize.y * 0.732f }, 5);
	skillButton[0] = obj;
	obj = new SpriteGo("crusader_ability_two");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.3281f, windowSize.y * 0.732f }, 5);
	skillButton[1] = obj;
	obj = new SpriteGo("crusader_ability_three");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.3677f, windowSize.y * 0.732f }, 5);
	skillButton[2] = obj;
	obj = new SpriteGo("crusader_ability_four");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.4075f, windowSize.y * 0.732f }, 5);
	skillButton[3] = obj;
	obj = new SpriteGo("ability_move");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.4471f, windowSize.y * 0.732f }, 5);
	skillButton[4] = obj;
	obj = new SpriteGo("ability_pass");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.473f, windowSize.y * 0.732f }, 8);
	skillButton[5] = obj;
	obj = new SpriteGo("selected_ability");
	SetSpriteInfo(obj, Origins::MC, { windowSize.x * 0.2885f, windowSize.y * 0.732f }, 6);
	skillButton[6] = obj;
	obj->SetActive(false);

	isSkillActive.set();


}

void UiDungeon::InitPlayerTextUi(const sf::Vector2f& windowSize)
{
	TextGo* obj;
	obj = new TextGo("LeeB");
	obj->SetColor(sf::Color::Red);
	obj->SetPosition({ windowSize.x * 0.21f, windowSize.y * 0.81f });
	obj->SetString("50 / 50");
	obj->SetCharacterSize(20);
	obj->SetOrigin(Origins::MR);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;

	playerText.insert({ PlayerTextIndex::HP, obj });
	obj = new TextGo("LeeB");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.21f, windowSize.y * 0.837f });
	obj->SetString("3 / 200");
	obj->SetCharacterSize(20);
	obj->SetOrigin(Origins::MR);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::STRESS, obj });

	obj = new TextGo("LeeB");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.15f, windowSize.y * 0.865f });
	obj->SetString("ACC");
	obj->SetCharacterSize(18);
	obj->SetOrigin(Origins::ML);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::ACCURACY, obj });

	obj = new TextGo("LeeB");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.15f, windowSize.y * 0.885f });
	obj->SetString("CRIT");
	obj->SetCharacterSize(18);
	obj->SetOrigin(Origins::ML);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::CRITICAL, obj });
	obj = new TextGo("LeeB");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.15f, windowSize.y * 0.905f });
	obj->SetString("DMG");
	obj->SetCharacterSize(18);
	obj->SetOrigin(Origins::ML);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::DAMAGE, obj });
	obj = new TextGo("LeeB");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.15f, windowSize.y * 0.925f });
	obj->SetString("DODGE");
	obj->SetCharacterSize(18);
	obj->SetOrigin(Origins::ML);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::DODGE, obj });

	obj = new TextGo("LeeB");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.15f, windowSize.y * 0.945f });
	obj->SetString("PROT");
	obj->SetCharacterSize(18);
	obj->SetOrigin(Origins::ML);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::PROTECT, obj });

	obj = new TextGo("LeeB");
	obj->SetColor(sf::Color::White);
	obj->SetPosition({ windowSize.x * 0.15f, windowSize.y * 0.965f });
	obj->SetString("SPD");
	obj->SetCharacterSize(18);
	obj->SetOrigin(Origins::ML);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = 6;
	playerText.insert({ PlayerTextIndex::SPEED, obj });

}

void UiDungeon::PlaySkillNameFrame(const std::string& str)
{
	skillNameFrame.ChangeText(str);
	skillNameFrame.SetActive(true);
	opacity = 0;
	timer = 0;
	isFramePlaying = true;
}

void UiDungeon::UpdateSkillNameFrame(float dt)
{
	timer += dt;
	if (timer > duration)
	{
		timer = 0;
		opacity++;
		skillNameFrame.SetOpacity(opacity);
	}
	if (opacity == 255) {
		isFramePlaying = false;
	}
}

void UiDungeon::ChangeSkillButtonTexture(const CharacterInfo& info)
{
	skillButton[0]->ChangeTexture(info.skill1[0]);
	skillButton[1]->ChangeTexture(info.skill2[0]);
	skillButton[2]->ChangeTexture(info.skill3[0]);
	skillButton[3]->ChangeTexture(info.skill4[0]);
	UpdateSkillUi();
}

void UiDungeon::ChangeSkillButtonActive(const std::vector<bool>& list)
{
	for (int i = 0; i < 4; i++)
	{
		if (list[i])
		{
			isSkillActive.set(i);
		}
		else {
			isSkillActive.reset(i);
		}

	}
	isSkillActive.set(4);
	isSkillActive.set(5);
	UpdateSkillUi();
}


void UiDungeon::DeactivateAllSkillButton()
{
	isSkillActive.reset();
	UpdateSkillUi();
}


void UiDungeon::UpdateSkillUi()
{
	for (int i = 0; i < 6; i++) {
		if (isSkillActive[i]) {
			skillButton[i]->SetFillColor(sf::Color::White);
		}
		else {
			skillButton[i]->SetFillColor(sf::Color(100, 100, 100, 255));
		}
	}

}



int UiDungeon::CheckSkillClick()
{
	if (InputManager::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (int i = 0; i < 5; i++) {
			if (isSkillActive[i]) {
				sf::FloatRect bounds = skillButton[i]->GetGlobalBounds();
				sf::Vector2f pos = (sf::Vector2f)InputManager::GetMousePosition();
				if (bounds.contains(pos)) {
					skillButton[6]->SetPosition(skillButton[i]->GetPosition());
					skillButton[6]->SetActive(true);
					return i + 1;
				}
			}
		}
	}
	return 0;
}

void UiDungeon::DeactivateSelectBox()
{
	skillButton[6]->SetActive(false);
}

void UiDungeon::DeactivateSkillNameFrame()
{
	skillNameFrame.SetActive(false);
}
