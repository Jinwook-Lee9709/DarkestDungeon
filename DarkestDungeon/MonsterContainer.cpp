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
	stunEffect.SetPosition(position - sf::Vector2f(-hpBar.getSize().y, hpBar.getSize().x * 2.7f));
	BottomEffector.SetPosition(position - sf::Vector2f(-hpBar.getSize().y, hpBar.getSize().x * 2.f));
	DeathEffector.SetPosition(position - sf::Vector2f(-hpBar.getSize().y, hpBar.getSize().x * 2.f));
	MiddleEffector.SetPosition(position);

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
	for (int i = 0; i < (int)DebuffType::Count; i++)
	{
		std::pair<short, int> pair = { 0, 0 };
		debuffStack.insert({ (DebuffType)i, pair });
	}
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

	stunEffect.Reset();
	stunEffect.SetPosition(position - sf::Vector2f(-hpBar.getSize().y, hpBar.getSize().x * 2.7f));
	stunEffect.SetOrigin(Origins::MC);
	debuffText.SetActive(false);

	BottomEffector.Reset();
	BottomEffector.SetPosition(position - sf::Vector2f(-hpBar.getSize().y, hpBar.getSize().x * 2.f));
	BottomEffector.SetOrigin(Origins::MC);
	MiddleEffector.Reset();
	MiddleEffector.SetPosition(position);
	MiddleEffector.SetOrigin(Origins::BC);
	DeathEffector.Reset();
	DeathEffector.SetPosition(position - sf::Vector2f(-hpBar.getSize().y, hpBar.getSize().x * 2.f));
	DeathEffector.SetOrigin(Origins::MC);


	hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
	SetOrigin(Origins::BC);

	float hpBarMargin = hpBar.getSize().x * 0.5f;
	hpBar.setPosition(position + sf::Vector2f(-hpBarMargin, -hpBar.getSize().y));
	target.SetPosition(position + sf::Vector2f(1.f, 2.4f * hpBar.getSize().y));
}

void MonsterContainer::Update(float dt)
{
	if (moving) {
		position = Utils::Lerp(position, dest, speed * dt, true);
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
	if (isDying) {
		deathTimer += dt;

		if (deathTimer > deathDuration)
		{
			isAlive = false;
			isDying = false;
		}
	}
	if (isAlive)
	{
		monster.Update(dt);
		debuffText.Update(dt);
		damageText.Update(dt);
		stunEffect.Update(dt);
		BottomEffector.Update(dt);
		MiddleEffector.Update(dt);
		DeathEffector.Update(dt);
		hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
	}
	
}

void MonsterContainer::Draw(sf::RenderWindow& window)
{
	if (isAlive) {
		monster.Draw(window);
		window.draw(hpBar);

		if (debuffText.IsActive())
			debuffText.Draw(window);
		BottomEffector.Draw(window);
		MiddleEffector.Draw(window);

		if (damageText.IsActive())
			damageText.Draw(window);
		if (stunEffect.IsActive())
			stunEffect.Draw(window);
		if (isDying)
		{
			DeathEffector.Draw(window);
		}
		

		target.Draw(window);
	}
	hitbox.Draw(window);
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
	speed = 10;
	moving = true;
	dest = coord;
}

void MonsterContainer::MoveToCoordDouble(sf::Vector2f coord)
{
	speed = 20;
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
void MonsterContainer::SetToDefend()
{
	monster.SetToDefend();
}
void MonsterContainer::SetToDeath()
{
	isDying = true;
	DeathEffector.SetDuration(1.4f);
	DeathEffector.AddAnimation("blood");
	monster.SetToDeath();
}
std::vector<int> MonsterContainer::CheckAvailableSkill()
{
	return monster.CheckAvailableSkill(currentPos);
}
std::vector<short>& MonsterContainer::GetSkillRange(int skillnum)
{
	return monster.GetSkillRange(skillnum);
}

bool MonsterContainer::OnHit(int damage, float acc)
{	
	SetToDefend();
	if (damage == 0)
	{
		return Utils::RollTheDice(acc - info.dodge / 100);
	}

	if (Utils::RollTheDice(acc - info.dodge / 100))
	{
		int damageBuf = Utils::Clamp(damage - info.protect, 1, 1000);
		info.hp -= damageBuf;
		damageText.AddAnimation(damageBuf);
		if (info.hp < 0)
		{
			info.hp = 0;
			SetToDeath();
		}
		return true;
	}
	else {
		return false;
	}

}

void MonsterContainer::OnDamage(int damage)
{
	int damageBuf = Utils::Clamp(damage, 0, damage);
	info.hp -= damageBuf;
	damageText.AddAnimation(damage);
	Utils::Clamp(info.hp, 0, info.maxHp);
	if (info.hp <= 0)
	{
		SetToDeath();
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
			debuffText.AddAnimation(DebuffType::Stun);
			stunEffect.SetDuration(1.f);
			stunEffect.AddAnimation("stunned");
			stunEffect.AddAnimation("stunned_loop");
		}
		break;
	}
	case DebuffType::Blight:
	{
		if (Utils::RollTheDice(acc - info.resistBlight))
		{
			debuffStack[DebuffType::Blight] = { stack, damage };
			debuffText.AddAnimation(DebuffType::Blight);
		}
		break;
	}
	case DebuffType::Bleed:
	{
		if (Utils::RollTheDice(acc - info.resistBleed))
		{
			debuffStack[DebuffType::Bleed] = { stack, damage };
			debuffText.AddAnimation(DebuffType::Bleed);
		}
		break;
	}
	case DebuffType::Debuff:
	{
		if (Utils::RollTheDice(acc - info.resistDebuff))
		{
			debuffStack[DebuffType::Debuff] = { stack, damage };
			debuffText.AddAnimation(DebuffType::Debuff);
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

void MonsterContainer::PlayBottomEffect(const std::string& animId, float duration)
{
	BottomEffector.SetDuration(duration);
	BottomEffector.AddAnimation(animId);
}

void MonsterContainer::PlayMiddleEffect(const std::string& animId, float duration)
{
	MiddleEffector.SetDuration(duration);
	MiddleEffector.AddAnimation(animId);
}

bool MonsterContainer::CheckDebuffCount()
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

void MonsterContainer::PlayDebuffText(DebuffType type)
{
	debuffText.AddAnimation(type);
}

void MonsterContainer::ApplyDebuff()
{
	for (auto& debuff : debuffStack)
	{
		switch (debuff.first)
		{
		case DebuffType::Stun:
		{
			break;
		}
		case DebuffType::Blight:
		{
			if (debuff.second.first > 0)
			{
				OnDamage(debuff.second.second);
				--debuff.second.first;
			}
			break;
		}
		case DebuffType::Bleed:
		{
			if (debuff.second.first > 0)
			{
				OnDamage(debuff.second.second);
				--debuff.second.first;
			}

			break;
		}
		case DebuffType::Debuff:
		{
			if (debuff.second.first > 0)
			{
				--debuff.second.first;
			}
			break;
		}
		}
	}
}

void MonsterContainer::EndStun()
{
	--debuffStack[DebuffType::Stun].first;
	debuffText.PlayAnimation(DebuffType::Stun);
	stunEffect.SetActive(false);
}

bool MonsterContainer::IsStuned()
{
	if (debuffStack[DebuffType::Stun].first == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
