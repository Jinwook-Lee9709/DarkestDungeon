#include "stdafx.h"
#include "Character.h"

Character::Character(const std::string& name)
	: GameObject(name)
{
}

void Character::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void Character::SetRotation(float angle)
{
	rotation = angle;
}

void Character::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Character::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void Character::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void Character::Init()
{
}

void Character::Release()
{
}

void Character::Reset()
{
}

void Character::Update(float dt)
{
}

void Character::Draw(sf::RenderWindow& window)
{
}
