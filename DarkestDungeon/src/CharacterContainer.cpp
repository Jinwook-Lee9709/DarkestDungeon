#include "stdafx.h"
#include "CharacterContainer.h"

CharacterContainer::CharacterContainer(const std::string& name)
{
}

CharacterContainer::~CharacterContainer()
{
}

void CharacterContainer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	character.setPosition(position);
	Utils::SetOrigin(character, Origins::BC);

	float hpBarMargin = hpBar.getSize().x * 0.5f;
	hpBar.setPosition(character.getPosition() + sf::Vector2f(-hpBarMargin, hpBar.getSize().y + 3.f));

	sf::Vector2f stressRectPos = hpBar.getPosition() + sf::Vector2f(stressBar[0].getOutlineThickness(), 15.f);
	float rectGap = (hpBar.getSize().x / 10 - stressBar->getSize().x - stressBar[0].getOutlineThickness() * 2) / 10 + hpBar.getSize().x / 10;
	for (int i = 0; i < 10; i++) {
		stressBar[i].setPosition(stressRectPos);
		stressRectPos.x += rectGap;
	}
}

void CharacterContainer::SetScale(const sf::Vector2f& size)
{
	character.setScale(scale);
}

void CharacterContainer::FlipX(bool flag)
{
}

void CharacterContainer::FlipY(bool flag)
{
}

void CharacterContainer::SetOrigin(Origins preset)
{
}

void CharacterContainer::SetOrigin(const sf::Vector2f& newOrigin)
{
}

void CharacterContainer::Init()
{
	hpBar.setSize({ 90.f,10.f });
	hpBar.setFillColor(sf::Color(128, 0, 0, 255));
	hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
	for (int i = 0; i < 10; i++) {
		stressBar[i].setSize({ 4.f, 5.f });
		stressBar[i].setOutlineThickness(2.f);
		stressBar[i].setFillColor(sf::Color(20, 20, 20, 255));
		stressBar[i].setOutlineColor(sf::Color(50, 50, 50, 255));
	}
}

void CharacterContainer::Reset()
{
	character.setTexture(TEX_MGR.Get("Resource/Heroes/Crusader/armatureName_combat_00.png"));
	character.setScale(originalCharacterScale);
	Utils::SetOrigin(character, Origins::BC);

	float hpBarMargin = hpBar.getSize().x * 0.5f;
	hpBar.setPosition(character.getPosition() + sf::Vector2f(-hpBarMargin, hpBar.getSize().y + 3.f));

	sf::Vector2f stressRectPos = hpBar.getPosition() + sf::Vector2f(stressBar[0].getOutlineThickness(), 15.f);
	float rectGap = (hpBar.getSize().x / 10 - stressBar->getSize().x - stressBar[0].getOutlineThickness()*2) / 10 + hpBar.getSize().x / 10;
	for (int i = 0; i < 10; i++) {
		stressBar[i].setPosition(stressRectPos);
		stressRectPos.x += rectGap;
	}
	

}

void CharacterContainer::Update(float dt)
{
}

void CharacterContainer::Draw(sf::RenderWindow& window)
{
	window.draw(character);
	window.draw(hpBar);
	for (int i = 0; i < 10; i++) {
		window.draw(stressBar[i]);
	}

}

void CharacterContainer::SetInitialStatus(const json& info)
{
	this->info.hp = info["hp"];
	this->info.maxHp = info["maxHp"];
	this->info.stress = info["stress"];
	this->info.speed = info["speed"];
	this->info.dodge = info["dodge"];
	this->info.accuracy = info["accuracy"];
	this->info.crtical = info["critical"];
	this->info.minDamage = info["minDamage"];
	this->info.maxDamage = info["maxDamage"];
	this->info.prot = info["protect"];
}
