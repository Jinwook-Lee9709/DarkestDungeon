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
	target.SetPosition(position + sf::Vector2f(1.f, 2.4f * hpBar.getSize().y));
	SetOrigin(Origins::BC);

	damageText.SetPosition(position - sf::Vector2f(-hpBar.getSize().y * 2, hpBar.getSize().x * 2.5f));
	debuffText.SetPosition(position - sf::Vector2f(hpBar.getSize().y * 1, hpBar.getSize().x * 3));

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

	debuffText.Reset();
	debuffText.SetPosition(position - sf::Vector2f(hpBar.getSize().y * 1, hpBar.getSize().x * 3));
	debuffText.SetScale({ 1.f, 1.f });
	debuffText.SetOrigin(Origins::MC);
	debuffText.SetActive(false);

	damageText.Reset();
	damageText.SetPosition(position - sf::Vector2f(-hpBar.getSize().y * 2, hpBar.getSize().x * 2.5f));
	damageText.SetScale({ 1.f, 1.f });
	damageText.SetOrigin(Origins::MC);
	damageText.SetActive(false);


	hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
	SetOrigin(Origins::BC);

	float hpBarMargin = hpBar.getSize().x * 0.5f;
	hpBar.setPosition(position + sf::Vector2f(-hpBarMargin, -hpBar.getSize().y));
	target.SetPosition(position + sf::Vector2f(1.f, 2.4f * hpBar.getSize().y));
}

void MonsterContainer::Update(float dt)
{
	if (moving) {
		position = Utils::Lerp(position, dest, 10 * dt, true);
		if (Utils::Magnitude(dest - position) < 0.05f)
		{
			SetPosition(dest);
			moving = false;
		}
		else
		{
			SetPosition(position);
		}
	}
	monster.Update(dt);
	debuffText.Update(dt);
	damageText.Update(dt);
	hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
}

void MonsterContainer::Draw(sf::RenderWindow& window)
{
	if (isAlive) {
		monster.Draw(window);
		window.draw(hpBar);
	}
	if (debuffText.IsActive())
		debuffText.Draw(window);

	if (damageText.IsActive())
		damageText.Draw(window);

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


void MonsterContainer::MoveToCoord(sf::Vector2f coord)
{
	moving = true;
	dest = coord;
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
void MonsterContainer::SetToIdle()
{
	monster.SetToIdle();
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
		int damageBuf = Utils::Clamp(damage - info.protect, 0, 1000);
		info.hp -= damageBuf;
		damageText.AddAnimation(damageBuf);
	}
	Utils::Clamp(info.hp, 0, info.maxHp);
	if (info.hp < 0)
	{
		isAlive = false;
	}
}

void MonsterContainer::OnDebuffed(DebuffType type, float acc, int damage, int stack)
{
	switch (type)
	{
	case DebuffType::Stun:
	{
		if (Utils::RollTheDice(acc - info.resistStun))
		{
			debuffStack[DebuffType::Stun] = { stack, damage };
		}
		break;
	}
	case DebuffType::Blight:
	{
		if (Utils::RollTheDice(acc - info.resistBlight))
		{
			debuffStack[DebuffType::Blight] = { stack, damage };
		}
		break;
	}
	case DebuffType::Bleed:
	{
		if (Utils::RollTheDice(acc - info.resistBleed))
		{
			debuffStack[DebuffType::Bleed] = { stack, damage };
		}
		break;
	}
	case DebuffType::Debuff:
	{
		if (Utils::RollTheDice(acc - info.resistDebuff))
		{
			debuffStack[DebuffType::Blight] = { stack, damage };
		}
		break;
	}
	case DebuffType::Move:
	{
		if (Utils::RollTheDice(acc - info.resistMove))
		{

		}
		break;
	}

	}
}

bool MonsterContainer::CheckDebuff()
{
	for (auto& debuff : debuffStack)
	{
		if (debuff.second.first > 0)
		{
			return true;
		}
	}
	return false;
}
