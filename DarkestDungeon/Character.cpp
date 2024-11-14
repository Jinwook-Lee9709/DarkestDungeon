#include "stdafx.h"
#include "Character.h"
#include "SkillCrusader.h"
#include "Skill.h"
#include "Slot.h"

Character::Character(const std::string& name)
	: GameObject(name)
{
}

void Character::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Character::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Character::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Character::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Character::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Character::Init()
{
	skillSlot = new Slot();
	animator.SetTarget(&body);
}

void Character::Release()
{
}

void Character::Reset()
{
	animator.Play("crusader_idle");

}

void Character::Update(float dt)
{
	if(InputManager::GetKeyDown(sf::Keyboard::A))
	{
		animator.Play("crusader_idle");
		SetOrigin(Origins::BC);
	}
	if (InputManager::GetKeyDown(sf::Keyboard::Num1))
	{
		animator.Play("crusader_smite");
		SetOrigin(Origins::BC);
	}
	if (InputManager::GetKeyDown(sf::Keyboard::Num2))
	{
		animator.Play("crusader_stun");
		SetOrigin(Origins::BC);
	}
	if (InputManager::GetKeyDown(sf::Keyboard::Num3))
	{
		animator.Play("crusader_heal");
		SetOrigin(Origins::BC);
	}
	if (InputManager::GetKeyDown(sf::Keyboard::Num4))
	{
		animator.Play("crusader_scroll");
		SetOrigin(Origins::BC);
	}
	animator.Update(dt);
}

void Character::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Character::SetToIdle()
{
}

void Character::SetToCombat()
{
}

void Character::SetToWalk()
{
}

void Character::OnHit(int damage)
{
}

void Character::Reset(const CharacterInfo& info)
{
	SetSlot(info);
}

void Character::SetSlot(const CharacterInfo& info)
{
	switch (info.type) {
		case CharacterType::Crusader: 
		{
			skill = dynamic_cast<Skill*>(new SkillCrusader());
		}
		default:
		{

		}
	}
	std::function<void(std::vector<CharacterContainer*>, std::vector<MonsterContainer*>, short, short)> skill1 = std::bind(&Skill::skill1, skill, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	std::function<void(std::vector<CharacterContainer*>, std::vector<MonsterContainer*>, short, short)> skill2 = std::bind(&Skill::skill2, skill, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	std::function<void(std::vector<CharacterContainer*>, std::vector<MonsterContainer*>, short, short)> skill3 = std::bind(&Skill::skill3, skill, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	std::function<void(std::vector<CharacterContainer*>, std::vector<MonsterContainer*>, short, short)> skill4 = std::bind(&Skill::skill4, skill, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	skillSlot->InsertSkill(skill1, skill->skillrange1);
	skillSlot->InsertSkill(skill2, skill->skillrange2);
	skillSlot->InsertSkill(skill3, skill->skillrange3);
	skillSlot->InsertSkill(skill4, skill->skillrange4);
}

void Character::UseSkill(std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target, int num )
{
	skillSlot->UseSkill(characters, monsters, user, target, num);
}
