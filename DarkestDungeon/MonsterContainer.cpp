#include "stdafx.h"
#include "MonsterContainer.h"

MonsterContainer::MonsterContainer(const std::string& name)
	: GameObject(name)
{
}

void MonsterContainer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	monster.SetPosition(position);
	SetOrigin(Origins::BC);

	float hpBarMargin = hpBar.getSize().x * 0.5f;
	hpBar.setPosition(position + sf::Vector2f(-hpBarMargin, 0));
}

void MonsterContainer::SetRotation(float angle)
{
	rotation = angle;
}

void MonsterContainer::SetScale(const sf::Vector2f& s)
{
	monster.SetScale(scale);
	scale = s;
}

void MonsterContainer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		monster.SetOrigin(originPreset);
	}
}

void MonsterContainer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	monster.SetOrigin(origin);
}

void MonsterContainer::Init()
{
	monster.Init();
	hpBar.setSize({ 90.f,10.f });
	hpBar.setFillColor(sf::Color(128, 0, 0, 255));
}

void MonsterContainer::Release()
{
}

void MonsterContainer::Reset()
{
	monster.Reset();
	monster.Reset(info);
	monster.SetScale(originalMonsterScale);
	hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
	SetOrigin(Origins::BC);

	float hpBarMargin = hpBar.getSize().x * 0.5f;
	hpBar.setPosition(position + sf::Vector2f(-hpBarMargin, -hpBar.getSize().y));
}

void MonsterContainer::Update(float dt)
{
	monster.Update(dt);
	hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
}

void MonsterContainer::Draw(sf::RenderWindow& window)
{
	monster.Draw(window);
	window.draw(hpBar);
}

void MonsterContainer::SetStatus(const json& info)
{
	isAlive = true;
	this->info = info;
}
void MonsterContainer::UseSkill(std::vector<CharacterContainer*>& characters, std::vector<MonsterContainer*>& monsters, short user, short target, int num)
{
	monster.UseSkill(characters, monsters, user, target, num);

}
void MonsterContainer::OnHit(int damage, float acc)
{
	info.hp -= damage;
}

void MonsterContainer::OnDebuffed(DebufType type, float acc)
{
}
