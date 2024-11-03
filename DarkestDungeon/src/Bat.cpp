#include "stdafx.h"
#include "Bat.h"

Bat::Bat(const std::string& name)
	:GameObject(name)
{
}

void Bat::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Bat::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Bat::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Bat::Init()
{
	body.setSize({ 200.f, 10.f });
	body.setFillColor(sf::Color::White);
	SetOrigin(Origins::TC);
	auto windowSize = FRAMEWORK.GetWindowSizeF();
	initPos = { windowSize.x * 0.5f , windowSize.y -100.f };

	auto halfWidth = body.getSize().x * 0.5f;
	minX = halfWidth;
	maxX = windowSize.x - halfWidth;
}


void Bat::Reset()
{
	body.setPosition(initPos);
	position = initPos;
}

void Bat::Update(float dt)
{
	direction.x = InputManager::GetAxis(Axis::horizontal);
	auto newPos = position + direction * speed * dt;
	newPos.x = Utils::Clamp(newPos.x, minX, maxX);
	SetPosition(newPos);

}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
