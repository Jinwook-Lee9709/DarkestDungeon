#include "stdafx.h"
#include "NameFrame.h"

#include "stdafx.h"
#include "NameFrame.h"

NameFrame::NameFrame(const std::string& name)
	: GameObject(name)
{
}

void NameFrame::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	plate.setPosition(position);
	text.setPosition(position);
}

void NameFrame::SetRotation(float angle)
{
	rotation = angle;
	plate.rotate(rotation);
	text.rotate(rotation);
}

void NameFrame::SetScale(const sf::Vector2f& s)
{
	scale = s;
	plate.setScale(scale);
	text.setScale(scale);
}

void NameFrame::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(plate, originPreset);
		Utils::SetOrigin(text, originPreset);
		text.setPosition(position + sf::Vector2f( 0.f, -6.f ));
	}
}

void NameFrame::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	plate.setOrigin(origin);
	text.setOrigin(origin);
}

void NameFrame::Init()
{
	
}

void NameFrame::Release()
{
}

void NameFrame::Reset()
{
	plate.setTexture(GET_TEX("name_frame"));
	text.setFont(GET_FONT("LeeB"));
	text.setFillColor(sf::Color::Yellow);
	text.setCharacterSize(30);
	SetOrigin(Origins::MC);
}

void NameFrame::Update(float dt)
{

}

void NameFrame::Draw(sf::RenderWindow& window)
{
	if (active)
	{
		window.draw(plate);
		window.draw(text);
	}
	
}

void NameFrame::ChangeText(const std::string& str)
{
	text.setString(str);
	SetOrigin(Origins::MC);
}

void NameFrame::SetOpacity(int opacity)
{
	plate.setColor(sf::Color(255, 255, 255, opacity));
}
