#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& font, const std::string& str)
	:GameObject(str), font(font)
{
}


TextGo::TextGo(const std::string& font)
	:font(font)
{

}

void TextGo::SetText(const std::string& str)
{
	GameObject::name = str;
	text.setString(str);
}

void TextGo::SetFontSize(int size)
{
	text.setCharacterSize(size);
}

void TextGo::ChangeFont(const std::string& str)
{
	font = str;
	Reset();
}

void TextGo::SetOutline(int tickness, sf::Color color)
{
	text.setOutlineThickness(tickness);
	text.setOutlineColor(color);
}

void TextGo::SetColor(sf::Color color)
{
	text.setFillColor(color);
}

void TextGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(text, originPreset);
}

void TextGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	text.setOrigin(origin);
}

void TextGo::Reset()
{
	text.setFont(GET_FONT(font));
	SetOrigin(originPreset);
}

void TextGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	text.setPosition(pos);
}

void TextGo::SetString(const std::string str)
{
	text.setString(str);
	SetOrigin(originPreset);
}


void TextGo::SetStringByTable(const std::string str)
{
	text.setString(STRING_TABLE->Get(str));
	SetOrigin(originPreset);
}

void TextGo::SetCharacterSize(int size)
{
	text.setCharacterSize(size);
}

void TextGo::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(text);
}
