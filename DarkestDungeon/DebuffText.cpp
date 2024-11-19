#include "stdafx.h"
#include "DebuffText.h"

DebuffText::DebuffText(const std::string& name)
	: GameObject(name), text("")
{
}

void DebuffText::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	text.SetPosition(position);
	icon.SetPosition(position -
		sf::Vector2f(text.GetGlobalBounds().width * 0.5f + 20.f, 0.f));
}

void DebuffText::SetScale(const sf::Vector2f& s)
{
	scale = s;
	text.SetScale(scale);
	icon.SetScale(0.7f * scale);
}

void DebuffText::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		text.SetOrigin(preset);
		icon.SetOrigin(preset);
	}
}

void DebuffText::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	text.SetOrigin(origin);
	icon.SetOrigin(origin);
}

void DebuffText::Init()
{
}

void DebuffText::Release()
{
}

void DebuffText::Reset()
{
	text.ChangeFont("Bokor");
	text.SetFontSize(40);
	text.SetOutline(2, sf::Color::Black);
}

void DebuffText::Update(float dt)
{
	if (!isPlay && !playQueue.empty())
	{
		PlayAnimation(playQueue.front());
		playQueue.pop();
	}
	if (isPlay) {
		timer += dt;
		posForAnim += sf::Vector2f(0, -120 * dt);
		text.SetPosition(posForAnim);
		icon.SetPosition(posForAnim -
			sf::Vector2f(text.GetGlobalBounds().width * 0.5f +
				icon.GetGlobalBounds().width + 10.f, -10.f));
		if (timer > duration)
		{
			isPlay = false;
			this->active = false;
		}
			
	}
}

void DebuffText::Draw(sf::RenderWindow& window)
{
	if (active)
	{
		text.Draw(window);
		icon.Draw(window);
	}
}

void DebuffText::AddAnimation(DebuffType type)
{
	playQueue.push(type);
}

void DebuffText::PlayAnimation(DebuffType type)
{
	timer = 0;
	isPlay = true;
	this->active = true;
	posForAnim = position;
	SetText(type);
}

void DebuffText::SetText(DebuffType type)
{
	switch (type)
	{
		case DebuffType::Stun:
		{
			text.SetStringByTable("stun");
			icon.SetActive(false);
			text.SetColor(sf::Color(220, 187, 79, 255));
			break;
		}
		case DebuffType::Blight:
		{
			icon.ChangeTexture("poptext_poison");
			text.SetStringByTable("blight");
			text.SetColor(sf::Color(121, 135, 26, 255));
			icon.SetActive(true);
			break;
		}
		case DebuffType::Bleed:
		{
			icon.ChangeTexture("poptext_bleed");
			text.SetStringByTable("bleed");
			text.SetColor(sf::Color(197, 7, 0, 255));
			icon.SetActive(true);
			break;
		}
		case DebuffType::Debuff:
		{
			icon.ChangeTexture("poptext_debuff");
			text.SetStringByTable("debuff");
			text.SetColor(sf::Color(183, 73, 23, 255));
			icon.SetActive(true);
			break;
		}
		case DebuffType::Move:
		{
			break;
		}
	}
	SetOrigin(originPreset);
}
