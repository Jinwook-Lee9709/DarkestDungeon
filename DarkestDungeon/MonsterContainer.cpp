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
	hitbox.rect.setPosition(position);
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
	hitbox.rect.setSize({ 100,290 });
	Utils::SetOrigin(hitbox.rect, Origins::BC);
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

	target.ChangeTexture("overlay_target_e");
	target.SetScale({ 0.88f, 0.88f });
	target.SetOrigin(Origins::BC);
	target.SetActive(false);

	hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
	SetOrigin(Origins::BC);

	float hpBarMargin = hpBar.getSize().x * 0.5f;
	hpBar.setPosition(position + sf::Vector2f(-hpBarMargin, -hpBar.getSize().y));
	target.SetPosition(position + sf::Vector2f(1.f, 2.4f * hpBar.getSize().y));
}

void MonsterContainer::Update(float dt)
{
	monster.Update(dt);
	hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
}

void MonsterContainer::Draw(sf::RenderWindow& window)
{
	if (isAlive) {
		monster.Draw(window);
		window.draw(hpBar);
	}

	hitbox.Draw(window);
	target.Draw(window);
}

void MonsterContainer::ActiavteTargetUi(TargetUi type)
{
	switch (type)
	{
		case TargetUi::SELECT:
		{
			target.ChangeTexture("overlay_selected");
			break;
		}
		case TargetUi::ENEMY:
		{
			target.ChangeTexture("overlay_target_e");
			break;
		}
	}
	target.SetActive(true);
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
std::vector<int> MonsterContainer::CheckAvailableSkill()
{
	return monster.CheckAvailableSkill(currentPos);
}
std::vector<short>& MonsterContainer::GetSkillRange(int skillnum)
{
	return monster.GetSkillRange(skillnum);
}

void MonsterContainer::OnHit(int damage, float acc)
{
	if (Utils::RollTheDice(acc - info.dodge / 100))
	{
		info.hp -= Utils::Clamp(damage - info.protect, 0, 1000);
	}
	Utils::Clamp(info.hp, 0, info.maxHp);
	if (info.hp < 0)
	{
		isAlive = false;
	}
}

void MonsterContainer::OnDebuffed(DebufType type, float acc)
{
}

