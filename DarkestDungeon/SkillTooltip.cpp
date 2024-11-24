#include "stdafx.h"
#include "SkillTooltip.h"
#include "CharacterContainer.h"
#include "SceneDev1.h"

SkillTooltip::SkillTooltip(const std::string& name)
	: GameObject(name)
{
	plate.setFillColor(sf::Color::Black);
	plate.setOutlineThickness(2);
	plate.setOutlineColor(sf::Color(60, 60, 60, 255));
	plate.setSize(defaultPlateSize);
	Utils::SetOrigin(plate, Origins::TC);
}

void SkillTooltip::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	plate.setPosition(position);
	rangeUi.SetPosition(position + sf::Vector2f(0.f, 10.f));
}


void SkillTooltip::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void SkillTooltip::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void SkillTooltip::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void SkillTooltip::Init()
{
}

void SkillTooltip::Release()
{
}

void SkillTooltip::Reset()
{
	SceneDev1* currentScene = dynamic_cast<SceneDev1*>(SCENE_MGR.GetCurrentScene());
	characters = currentScene->GetCharacters();
}

void SkillTooltip::Update(float dt)
{
}

void SkillTooltip::Draw(sf::RenderWindow& window)
{
	if (IsActive())
	{
		window.draw(plate);
		rangeUi.Draw(window);
		for (auto& line : text)
		{
			line->Draw(window);
		}
	}

}

void SkillTooltip::Set(const CharacterInfo& info, const short& characterNum, const short& skillNum )
{
	if (!text.empty())
	{
		for (auto& line : text)
		{
			textPool.Return(line);
		}
		text.clear();
	}

	int currentRow = 0;
	std::vector<int> colorCode;
	sf::Vector2f plateSize = defaultPlateSize; 
	json skillText;
	switch (skillNum)
	{
	case 0:
		skillText = SKILL_STRING_TABLE->Get(info.skill1[0]);
		break;
	case 1:
		skillText = SKILL_STRING_TABLE->Get(info.skill2[0]);
		break;
	case 2:
		skillText = SKILL_STRING_TABLE->Get(info.skill3[0]);
		break;
	case 3:
		skillText = SKILL_STRING_TABLE->Get(info.skill4[0]);
		break;
	}

	//Set Range Info
	std::vector<short> range = characters[characterNum]->GetSkillRange(skillNum);
	rangeUi.Set(range);
	TextGo* obj = textPool.Take();
	currentRow++;

	colorCode = skillText["name"]["color"].get<std::vector<int>>();
	obj->ChangeFont("LeeL");
	obj->SetCharacterSize(15);
	obj->SetText(STR(skillText["name"]["stringKey"]));
	obj->SetColor(sf::Color(colorCode[0], colorCode[1], colorCode[2], 255));
	obj->SetOrigin(Origins::MC);
	obj->SetPosition(position + verticalSpace * (float)currentRow);
	if ((obj->GetGlobalBounds().width + frameMargin * 2) > plateSize.x)
	{
		plateSize.x = obj->GetGlobalBounds().width + frameMargin * 2;
	}
	text.push_back(obj);
	
	if (skillText["type"]["stringKey"] != "NULL")
	{
		obj = textPool.Take();
		currentRow++;

		colorCode = skillText["type"]["color"].get<std::vector<int>>();
		obj->ChangeFont("LeeL");
		obj->SetCharacterSize(15);
		obj->SetText(STR(skillText["type"]["stringKey"]));
		obj->SetColor(sf::Color(colorCode[0], colorCode[1], colorCode[2], 255));
		obj->SetOrigin(Origins::MC);
		obj->SetPosition(position + verticalSpace * (float)currentRow);
		if ((obj->GetGlobalBounds().width + frameMargin * 2) > plateSize.x)
		{
			plateSize.x = obj->GetGlobalBounds().width + frameMargin * 2;
		}
		text.push_back(obj);
		plateSize += verticalSpace;
	}
	
	for (int i = 0; i < (int)skillText["Count"]; i++)
	{
		currentRow++;
		json line = skillText["line_" + std::to_string(i)];
		std::vector<TextGo*> texts;
		float length = 0;
		for (int j = 0; j < (int)line["count"]; j++)
		{
			colorCode = line["color" + std::to_string(j)].get<std::vector<int>>();
			obj = textPool.Take();
			obj->ChangeFont("LeeL");
			obj->SetCharacterSize(15);
			obj->SetText(STR(line["stringKey"+ std::to_string(j)]));
			obj->SetColor(sf::Color(colorCode[0], colorCode[1], colorCode[2], 255));
			obj->SetOrigin(Origins::ML);
			length += obj->GetLocalBounds().width;
			if (j < (int)line["count"] - 1)
			{
				length += characterSpace;
			}
			texts.push_back(obj);
		}
		if (length + frameMargin * 2 > plateSize.x)
		{
			plateSize.x = length + frameMargin * 2;
		}
		sf::Vector2f startPos = position + (verticalSpace * (float)currentRow) - sf::Vector2f(length / 2, 0.f);
		for (auto& word : texts)
		{
			word->SetPosition(startPos);
			startPos.x += word->GetLocalBounds().width + characterSpace;
			text.push_back(word);
		}
		plateSize += verticalSpace;
	}
	plate.setSize(plateSize);
	Utils::SetOrigin(plate, Origins::TC);
	
}
