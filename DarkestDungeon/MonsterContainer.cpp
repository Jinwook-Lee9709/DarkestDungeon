#include "stdafx.h"
#include "MonsterContainer.h"

MonsterContainer::MonsterContainer(const std::string& name)
	: GameObject(name)
{
}

void MonsterContainer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void MonsterContainer::SetRotation(float angle)
{
	rotation = angle;
}

void MonsterContainer::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void MonsterContainer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void MonsterContainer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void MonsterContainer::Init()
{
}

void MonsterContainer::Release()
{
}

void MonsterContainer::Reset()
{
}

void MonsterContainer::Update(float dt)
{
}

void MonsterContainer::Draw(sf::RenderWindow& window)
{
}

void MonsterContainer::OnHit(int damage, float acc)
{
}

void MonsterContainer::OnDebuffed(DebufType type, float acc)
{
}
