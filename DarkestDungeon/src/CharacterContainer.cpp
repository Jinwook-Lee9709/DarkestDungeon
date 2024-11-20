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
	hitbox.rect.setPosition(position);
	SetOrigin(Origins::BC);

	float hpBarMargin = hpBar.getSize().x * 0.5f;
	hpBar.setPosition(position + sf::Vector2f(-hpBarMargin, 0));
	target.SetPosition(position + sf::Vector2f(1.f, 2.4f * hpBar.getSize().y));

	damageText.SetPosition(position - sf::Vector2f(hpBar.getSize().y * 2, hpBar.getSize().x * 2.5f));
	debuffText.SetPosition(position - sf::Vector2f(-hpBar.getSize().y * 1, hpBar.getSize().x * 3));
	stunEffect.SetPosition(position - sf::Vector2f(-hpBar.getSize().y, hpBar.getSize().x * 2.7f));
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
	hitbox.rect.setSize({ 100,290 });
	Utils::SetOrigin(hitbox.rect, Origins::BC);
	for (int i = 0; i < 10; i++) {
		stressBar[i].setSize({ 4.f, 5.f });
		stressBar[i].setOutlineThickness(2.f);
		stressBar[i].setFillColor(sf::Color(20, 20, 20, 255));
		stressBar[i].setOutlineColor(sf::Color(50, 50, 50, 255));
	}
	for (int i = 0; i < (int)DebuffType::Count; i++)
	{
		std::pair<short, int> pair = { 0, 0 };
		debuffStack.insert({ (DebuffType)i, pair });
	}
	

}

void CharacterContainer::Reset()
{
	character.Reset();
	character.Reset(info);
	character.SetScale(originalCharacterScale);

	target.ChangeTexture("overlay_target_e");
	target.SetScale({ 0.86f, 0.88f });
	target.SetOrigin(Origins::BC);
	target.SetActive(false);

	debuffText.Reset();
	debuffText.SetPosition(position - sf::Vector2f(-hpBar.getSize().y * 1, hpBar.getSize().x * 3));
	debuffText.SetScale({1.f, 1.f});
	debuffText.SetOrigin(Origins::MC);
	debuffText.SetActive(false);

	damageText.Reset();
	damageText.SetPosition(position - sf::Vector2f(hpBar.getSize().y * 2, hpBar.getSize().x * 2.5f));
	damageText.SetScale({ 1.f, 1.f });
	damageText.SetOrigin(Origins::MC);
	damageText.SetActive(false);

	stunEffect.Reset();
	stunEffect.SetPosition(position- sf::Vector2f(-hpBar.getSize().y, hpBar.getSize().x * 2.7f));
	stunEffect.SetOrigin(Origins::MC);
	debuffText.SetActive(false);

	hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
	SetOrigin(Origins::BC);

	float hpBarMargin = hpBar.getSize().x * 0.5f;
	hpBar.setPosition(position + sf::Vector2f(-hpBarMargin, -hpBar.getSize().y));
	target.SetPosition(position + sf::Vector2f(1.f, 2.4f * hpBar.getSize().y));

	sf::Vector2f stressRectPos = hpBar.getPosition() + sf::Vector2f(stressBar[0].getOutlineThickness(), 15.f);
	float rectGap = (hpBar.getSize().x / 10 - stressBar->getSize().x - stressBar[0].getOutlineThickness()*2) / 10 + hpBar.getSize().x / 10;
	for (int i = 0; i < 10; i++) {
		stressBar[i].setPosition(stressRectPos);
		stressRectPos.x += rectGap;
	}
	

}

void CharacterContainer::Update(float dt)
{
	if (moving) {
		position = Utils::Lerp(position, dest, speed * dt, true);
		if (Utils::Magnitude(dest - position) < 0.05f)
		{
			SetPosition(dest);
			moving = false;
		}else
		{
			SetPosition(position);
		}
	}

	character.Update(dt);
	debuffText.Update(dt);
	damageText.Update(dt);
	stunEffect.Update(dt);
	hpBar.setScale({ (float)info.hp / (float)info.maxHp, 1.0f });
}

void CharacterContainer::Draw(sf::RenderWindow& window)
{
	character.Draw(window);
	window.draw(hpBar);
	for (int i = 0; i < 10; i++) {
		window.draw(stressBar[i]);
	}
	target.Draw(window);
	hitbox.Draw(window);
	if (debuffText.IsActive())
		debuffText.Draw(window);
	
	if (damageText.IsActive())
		damageText.Draw(window);
	if (stunEffect.IsActive())
		stunEffect.Draw(window);
}

void CharacterContainer::ActiavteTargetUi(TargetUi type)
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
		case TargetUi::HEAL:
		{
			target.ChangeTexture("overlay_target_h");
			break;
		}
		case TargetUi::CHANGEPOS:
		{
			target.ChangeTexture("overlay_move");
			break;
		}
	}
	target.SetActive(true);
}

void CharacterContainer::MoveToCoord(sf::Vector2f coord)
{
	speed = 10;
	moving = true;
	dest = coord;
}

void CharacterContainer::MoveToCoordDouble(sf::Vector2f coord)
{
	speed = 20;
	moving = true;
	dest = coord;
}

void CharacterContainer::SetInitialStatus(const json& info)
{
	isAlive = true;
	this->info = info;
}

void CharacterContainer::SetToIdle()
{
	character.SetToIdle();
}

void CharacterContainer::SetToCombat()
{
	character.SetToCombat();
}

void CharacterContainer::SetToWalk()
{
	character.SetToWalk();
}

void CharacterContainer::UseSkill(std::vector<CharacterContainer*>& characters, std::vector<MonsterContainer*>& monsters, short user, short target, int num)
{
	character.UseSkill(characters, monsters, user, target, num);
	
}

std::vector<int> CharacterContainer::CheckAvailableSkill()
{
	return character.CheckAvailableSkill(currentPos);
}

std::vector<short>& CharacterContainer::GetSkillRange(int skillnum)
{
	return character.GetSkillRange(skillnum);
}


void CharacterContainer::OnHit(int damage, float acc)
{
	if (Utils::RollTheDice(acc - (float)info.dodge / 100))
	{
		int damageBuf = Utils::Clamp(damage - info.protect, 0, damage);
		info.hp -= damageBuf;
		damageText.AddAnimation(damageBuf);
	}
}

void CharacterContainer::OnDamage(int damage)
{
	int damageBuf = Utils::Clamp(damage, 0, damage);
	info.hp -= damageBuf;
	damageText.AddAnimation(damage);
}

void CharacterContainer::OnDebuffed(DebuffType type, float acc, int damage, int stack)
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

void CharacterContainer::OnHeal(int amount)
{
	info.hp += amount;
	if (info.hp > info.maxHp) {
		info.hp = info.maxHp;
	}

}

int CharacterContainer::CheckDebuffCount()
{
	int cnt = 0;
	for (auto& debuff : debuffStack)
	{
		if (debuff.second.first > 0)
		{
			cnt++;
		}
	}
	return cnt;
}

void CharacterContainer::PlayDebuffText(DebuffType type)
{
	debuffText.AddAnimation(type);
}

void CharacterContainer::ApplyDebuff()
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

void CharacterContainer::EndStun()
{
	--debuffStack[DebuffType::Stun].first;
	debuffText.PlayAnimation(DebuffType::Stun);
	stunEffect.SetActive(false);
}




bool CharacterContainer::IsStuned()
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
