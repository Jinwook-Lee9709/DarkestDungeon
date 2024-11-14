#include "stdafx.h"
#include "CharacterContainer.h"
#include "MonsterContainer.h"

CharacterContainer::CharacterContainer(const std::string& name)
{
}

CharacterContainer::~CharacterContainer()
{
}

void CharacterContainer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	character.SetPosition(position);
	SetOrigin(Origins::BC);

	float hpBarMargin = hpBar.getSize().x * 0.5f;
	hpBar.setPosition(position + sf::Vector2f(-hpBarMargin, 0));

	sf::Vector2f stressRectPos = hpBar.getPosition() + sf::Vector2f(stressBar[0].getOutlineThickness(), 15.f);
	float rectGap = (hpBar.getSize().x / 10 - stressBar->getSize().x - stressBar[0].getOutlineThickness() * 2) / 10 + hpBar.getSize().x / 10;
	for (int i = 0; i < 10; i++) {
		stressBar[i].setPosition(stressRectPos);
		stressRectPos.x += rectGap;
	}
}

void CharacterContainer::SetScale(const sf::Vector2f& size)
{
	character.SetScale(scale);
}

void CharacterContainer::FlipX(bool flag)
{
}

void CharacterContainer::FlipY(bool flag)
{
}

void CharacterContainer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom) {
		character.SetOrigin(originPreset);
	}

}

void CharacterContainer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	character.SetOrigin(origin);
}

void CharacterContainer::Init()
{
	character.Init();
	hpBar.setSize({ 90.f,10.f });
	hpBar.setFillColor(sf::Color(128, 0, 0, 255));
	for (int i = 0; i < 10; i++) {
		stressBar[i].setSize({ 4.f, 5.f });
		stressBar[i].setOutlineThickness(2.f);
		stressBar[i].setFillColor(sf::Color(20, 20, 20, 255));
		stressBar[i].setOutlineColor(sf::Color(50, 50, 50, 255));
	}
}

void CharacterContainer::Reset()
{
	character.Reset();
	character.Reset(info);
	character.SetScale(originalCharacterScale);
	hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
	SetOrigin(Origins::BC);

	float hpBarMargin = hpBar.getSize().x * 0.5f;
	hpBar.setPosition(position + sf::Vector2f(-hpBarMargin, -hpBar.getSize().y));

	sf::Vector2f stressRectPos = hpBar.getPosition() + sf::Vector2f(stressBar[0].getOutlineThickness(), 15.f);
	float rectGap = (hpBar.getSize().x / 10 - stressBar->getSize().x - stressBar[0].getOutlineThickness()*2) / 10 + hpBar.getSize().x / 10;
	for (int i = 0; i < 10; i++) {
		stressBar[i].setPosition(stressRectPos);
		stressRectPos.x += rectGap;
	}
	

}

void CharacterContainer::Update(float dt)
{
	character.Update(dt);
	//if(InputManager::GetKeyDown(sf::Keyboard::A))
	//{
	//	animator.Play("crusader_idle");
	//	SetOrigin(Origins::BC);
	//}
	//if (InputManager::GetKeyDown(sf::Keyboard::Num1))
	//{
	//	animator.Play("crusader_smite");
	//	SetOrigin(Origins::BC);
	//}
	//if (InputManager::GetKeyDown(sf::Keyboard::Num2))
	//{
	//	animator.Play("crusader_stun");
	//	SetOrigin(Origins::BC);
	//}
	//if (InputManager::GetKeyDown(sf::Keyboard::Num3))
	//{
	//	animator.Play("crusader_heal");
	//	SetOrigin(Origins::BC);
	//}
	//if (InputManager::GetKeyDown(sf::Keyboard::Num4))
	//{
	//	animator.Play("crusader_scroll");
	//	SetOrigin(Origins::BC);
	//}

	//animator.Update(dt);
	hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
}

void CharacterContainer::Draw(sf::RenderWindow& window)
{
	character.Draw(window);
	window.draw(hpBar);
	for (int i = 0; i < 10; i++) {
		window.draw(stressBar[i]);
	}

}

void CharacterContainer::SetInitialStatus(const json& info)
{

	this->info = info;
	/*this->info.name = info["name"];
	this->info.type = info["type"];
	this->info.hp = info["hp"];
	this->info.maxHp = info["maxHp"];
	this->info.stress = info["stress"];
	this->info.speed = info["speed"];
	this->info.dodge = info["dodge"];
	this->info.accuracy = info["accuracy"];
	this->info.critical = info["critical"];
	this->info.minDamage = info["minDamage"];
	this->info.maxDamage = info["maxDamage"];
	this->info.prot = info["protect"];
	this->info.skill1 = info["skill1"];
	this->info.skill2 = info["skill2"];
	this->info.skill3 = info["skill3"];
	this->info.skill4 = info["skill4"];*/
	
}

void CharacterContainer::UseSkill(std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target, int num)
{
	character.UseSkill(characters, monsters, user, target, num);
}

void CharacterContainer::OnHeal(int amount)
{
	info.hp += amount;

}
