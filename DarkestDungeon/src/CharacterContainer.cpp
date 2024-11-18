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
		position = Utils::Lerp(position, dest, 10 * dt, true);
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
		info.hp -= Utils::Clamp(damage - info.protect, 0, damage);
	}
}

void CharacterContainer::OnDebuffed(DebufType type, float acc)
{
}

void CharacterContainer::OnHeal(int amount)
{
	info.hp += amount;
	if (info.hp > info.maxHp) {
		info.hp = info.maxHp;
	}

}
