#include "stdafx.h"
#include "MonsterInfoPanel.h"

#include "stdafx.h"
#include "MonsterInfoPanel.h"

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

void MonsterInfoPanel::Init()
{
}

void MonsterInfoPanel::Release()
{
}

void MonsterInfoPanel::Reset()
{
}

void MonsterInfoPanel::Update(float dt)
{
}

void MonsterInfoPanel::Draw(sf::RenderWindow& window)
{
}
