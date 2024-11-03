#include "stdafx.h"
#include "Ball.h"
#include "Bat.h"

Ball::Ball(const std::string& name)
	:GameObject(name)
{
}

void Ball::SetPosition(const sf::Vector2f& pos)
{
}


void Ball::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Ball::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Ball::Init()
{
	body.setRadius(10.f);
	body.setFillColor(sf::Color::White);
	SetOrigin(Origins::BC);
	float radius = 10.f;
	float half = radius * 0.5f;
	auto windowBounds = FRAMEWORK.GetWindowBoudns();
	moveableBounds.top = windowBounds.top + radius;
	moveableBounds.height = windowBounds.height - radius;
	moveableBounds.left = windowBounds.left + half;
	moveableBounds.width = windowBounds.width - radius;


}

void Ball::Reset()
{
	isDie = false;
	isFired = false;
}

void Ball::Update(float dt)
{
	sf::Vector2f newPos = position;
	sf::FloatRect batBounds = bat->GetGlobaBounds();
	if (InputManager::GetKeyDown(sf::Keyboard::Space)) {
		Fire();
	}
	if (isFired == false) {
		position = bat->GetPosition();
		body.setPosition(position);
		return;
	}
	newPos += direction * speed * dt;
	if (newPos.x < moveableBounds.left) 
	{
		direction.x *= -1.f;
		newPos.x = moveableBounds.left;
	}
	if (newPos.x > moveableBounds.left + moveableBounds.width) 
	{
		direction.x *= -1.f;
		newPos.x = moveableBounds.left + moveableBounds.width;
	}
	if (newPos.y < moveableBounds.top)
	{
		direction.y *= -1.f;
		newPos.y = moveableBounds.top;
	}
	if (newPos.y > moveableBounds.top + moveableBounds.height)
	{
		direction.y *= -1.f;
		newPos.y = moveableBounds.top + moveableBounds.height;
		speed = 0;
		isDie = true;
	}
	if (body.getGlobalBounds().intersects(batBounds)) {
		direction.y = -1.f;
		newPos.y = bat->GetPosition().y;
		intersect = true;
	}

	position = newPos;
	body.setPosition(position);
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Ball::Fire()
{
	if (speed == 0 && isDie == false) {
		isFired = true;
		speed = 500.f;
		direction = { 1.f, -1.f };
	}
	
}