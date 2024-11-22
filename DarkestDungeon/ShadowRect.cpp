#include "stdafx.h"
#include "ShadowRect.h"
#include "stdafx.h"
#include "ShadowRect.h"

ShadowRect::ShadowRect(const std::string& name)
	: GameObject(name)
{
}

void ShadowRect::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	rect.setPosition(position);
}

void ShadowRect::SetRotation(float angle)
{
	rotation = angle;
	rect.setRotation(rotation);
}

void ShadowRect::SetScale(const sf::Vector2f& s)
{
	rect.setScale(scale);
	scale = s;
}

void ShadowRect::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(rect, originPreset);
	}
}

void ShadowRect::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	rect.setOrigin(origin);
}

void ShadowRect::Init()
{
}

void ShadowRect::Release()
{
}

void ShadowRect::Reset()
{
	auto windowsize = FRAMEWORK.GetWindowSizeF();
	rect.setSize(windowsize);
	rect.setFillColor(sf::Color(0, 0, 0, currentOpacity));
	SetPosition({ 0.5f * windowsize.x, 0.5f * windowsize.y });
	SetOrigin(Origins::MC);
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 10;
	isVisible = false;
}

void ShadowRect::Update(float dt)
{
	if (isVisible)
	{
		if (currentOpacity < maxOpacity)
		{
			currentOpacity = Utils::Clamp(currentOpacity + 500 * dt, 0, maxOpacity);
			rect.setFillColor(sf::Color(0, 0, 0, currentOpacity));
		}
		else {
			isChanging = false;
		}
	}
	else
	{
		if (currentOpacity > 0)
		{
			currentOpacity = Utils::Clamp(currentOpacity - 500 * dt, 0, maxOpacity);
			rect.setFillColor(sf::Color(0, 0, 0, currentOpacity));

		}
		else
		{
			isChanging = false;
		}
	}
}
void ShadowRect::Draw(sf::RenderWindow& window)
{
	window.draw(rect);
}
