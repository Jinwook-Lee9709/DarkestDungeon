#include "stdafx.h"
#include "Crusader.h"

Crusader::Crusader(const std::string& name)
	: GameObject(name)
{
}

void Crusader::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void Crusader::SetRotation(float angle)
{
	rotation = angle;
}

void Crusader::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Crusader::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void Crusader::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
}

void Crusader::Init()
{
}

void Crusader::Release()
{
}

void Crusader::Reset()
{
}

void Crusader::Update(float dt)
{
}

void Crusader::Draw(sf::RenderWindow& window)
{
}
