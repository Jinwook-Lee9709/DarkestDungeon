#include "stdafx.h"
#include "MonsterInfoPanel.h"
#include "MonsterContainer.h"

MonsterInfoPanel::MonsterInfoPanel(const std::string& name)
	: GameObject(name)
{
}

void MonsterInfoPanel::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void MonsterInfoPanel::SetRotation(float angle)
{
	rotation = angle;
}

void MonsterInfoPanel::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void MonsterInfoPanel::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void MonsterInfoPanel::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}


void MonsterInfoPanel::Release()
{
	delete(panel);
	for (auto& text : texts)
	{
		delete(text);
	}
	for (auto& icon : resIcons)
	{
		delete(icon);
	}
	texts.clear();
	resIcons.clear();
}

void MonsterInfoPanel::Reset()
{
	sf::Vector2f position, size;
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	SpriteGo* obj1;
	obj1 = new SpriteGo("panel_monster");
	SetGoInfo(obj1, Origins::BL, { windowSize.x * 0.486f,  windowSize.y }, 5);
	panel = obj1;
	panel->Reset();

	position = obj1->GetPosition();
	size = obj1->GetSize();
	
	obj1 = new SpriteGo("tray_stun");
	SetGoInfo(obj1, Origins::MC, { position.x + size.x * 0.152f,  position.y - size.y * 0.334f }, 5);
	resIcons.push_back(obj1);

	obj1 = new SpriteGo("tray_poison");
	SetGoInfo(obj1, Origins::MC, { position.x + size.x * 0.152f,  position.y - size.y * 0.269f }, 5);
	resIcons.push_back(obj1);

	obj1 = new SpriteGo("tray_bleed");
	SetGoInfo(obj1, Origins::MC, { position.x + size.x * 0.152f,  position.y - size.y * 0.204f }, 5);
	resIcons.push_back(obj1);

	obj1 = new SpriteGo("tray_debuff");
	SetGoInfo(obj1, Origins::MC, { position.x + size.x * 0.152f,  position.y - size.y * 0.139f }, 5);
	resIcons.push_back(obj1);

	obj1 = new SpriteGo("tray_move");
	SetGoInfo(obj1, Origins::MC, { position.x + size.x * 0.152f,  position.y - size.y * 0.074f }, 5);
	resIcons.push_back(obj1);

	TextGo* obj2;
	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.110f,  position.y - size.y * 0.8f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(30);
	obj2->SetString("SKELETON");
	obj2->SetColor(sf::Color(221, 9, 0, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::MR, { position.x + size.x * 0.8f,  position.y - size.y * 0.8f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(30);
	obj2->SetStringByTable("hpText");
	obj2->SetColor(sf::Color(221, 9, 0, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.81f,  position.y - size.y * 0.8f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(30);
	obj2->SetString("12 / 12");
	obj2->SetColor(sf::Color(221, 9, 0, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.320f,  position.y - size.y * 0.67f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(18);
	obj2->SetStringByTable("protectText");
	obj2->SetColor(sf::Color(220, 220, 220, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.389f,  position.y - size.y * 0.67f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(18);
	obj2->SetString("15%");
	obj2->SetColor(sf::Color(220, 220, 220, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.320f,  position.y - size.y * 0.61f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(18);
	obj2->SetStringByTable("dodgeText");
	obj2->SetColor(sf::Color(220, 220, 220, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.389f,  position.y - size.y * 0.61f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(18);
	obj2->SetString("2");
	obj2->SetColor(sf::Color(220, 220, 220, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.320f,  position.y - size.y * 0.55f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(18);
	obj2->SetStringByTable("speedText");
	obj2->SetColor(sf::Color(220, 220, 220, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.389f,  position.y - size.y * 0.55f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(18);
	obj2->SetString("3");
	obj2->SetColor(sf::Color(220, 220, 220, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.22f,  position.y - size.y * 0.459f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(25);
	obj2->SetStringByTable("resistanceText");
	obj2->SetColor(sf::Color(150, 150, 150, 255));


	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.180f,  position.y - size.y * 0.344f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(20);
	obj2->SetStringByTable("stunText");
	obj2->SetColor(sf::Color(214, 181, 76, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::MR, { position.x + size.x * 0.45f,  position.y - size.y * 0.344f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(20);
	obj2->SetString("25%");

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.180f,  position.y - size.y * 0.279f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(20);
	obj2->SetStringByTable("blightText");
	obj2->SetColor(sf::Color(121, 135, 26, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::MR, { position.x + size.x * 0.45f,  position.y - size.y * 0.279f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(20);
	obj2->SetString("25%");

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.180f,  position.y - size.y * 0.214f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(20);
	obj2->SetStringByTable("bleedText");
	obj2->SetColor(sf::Color(221, 9, 0, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::MR, { position.x + size.x * 0.45f,  position.y - size.y * 0.214f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(20);
	obj2->SetString("25%");

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.180f,  position.y - size.y * 0.149f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(20);
	obj2->SetStringByTable("debuffText");
	obj2->SetColor(sf::Color(238, 132, 20, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::MR, { position.x + size.x * 0.45f,  position.y - size.y * 0.149f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(20);
	obj2->SetString("5%");


	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::ML, { position.x + size.x * 0.180f,  position.y - size.y * 0.084f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(20);
	obj2->SetStringByTable("moveText");
	obj2->SetColor(sf::Color(83, 191, 236, 255));

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::MR, { position.x + size.x * 0.45f,  position.y - size.y * 0.084f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(20);
	obj2->SetString("5%");

	obj2 = new TextGo("Bokor");
	SetGoInfo(obj2, Origins::MC, { position.x + size.x * 0.7f,  position.y - size.y * 0.459f }, 5);
	texts.push_back(obj2);
	obj2->SetCharacterSize(25);
	obj2->SetStringByTable("skillText");
	obj2->SetColor(sf::Color(150, 150, 150, 255));


	for (auto& icon : resIcons)
	{
		icon->Reset();
	}
	for (auto& text : texts)
	{
		text->Reset();
	}



}

void MonsterInfoPanel::Update(float dt)
{
	

}

void MonsterInfoPanel::Draw(sf::RenderWindow& window)
{
	if (active)
	{
		panel->Draw(window);
		for (auto& icon : resIcons)
		{
			icon->Draw(window);
		}
		for (auto& text : texts)
		{
			text->Draw(window);
		}
	}
	
}

void MonsterInfoPanel::UpdateInfo(const MonsterInfo& info)
{
	texts[(int)textId::MonsterName]->SetString(info.name);
	texts[(int)textId::HpValue]->SetString(std::to_string((int)info.hp) + "/" + std::to_string(info.maxHp));
	texts[(int)textId::ProtectValue]->SetString(std::to_string((int)info.protect) + "%");
	texts[(int)textId::DodgeValue]->SetString(std::to_string((int)info.dodge));
	texts[(int)textId::SpeedValue]->SetString(std::to_string((int)info.speed));
	texts[(int)textId::ResStunValue]->SetString(std::to_string((int)info.resistStun) + "%");
	texts[(int)textId::ResBlightValue]->SetString(std::to_string((int)info.resistBlight) + "%");
	texts[(int)textId::ResBleedValue]->SetString(std::to_string((int)info.resistBleed) + "%");
	texts[(int)textId::ResDebuffValue]->SetString(std::to_string((int)info.resistDebuff) + "%");
	texts[(int)textId::ResMoveValue]->SetString(std::to_string((int)info.resistMove) + "%");
}

void MonsterInfoPanel::SetGoInfo(GameObject* obj, const Origins& origin, const sf::Vector2f pos, const int& order, const bool& flipX, const bool& flipY)
{
	obj->SetOrigin(origin);
	obj->SetPosition(pos);
	obj->FlipX(flipX);
	obj->sortingLayer = SortingLayers::UI;
	obj->sortingOrder = order;
}
