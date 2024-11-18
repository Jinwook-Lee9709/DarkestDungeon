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
	animator.Update(dt);
	
}

void Character::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Character::SetToIdle()
{
	animator.Play(&RES_TABLE_MGR.GetCharacterAnim(std::to_string((int)(type)), "IDLE"));
	SetOrigin(Origins::BC);
}

void Character::SetToCombat()
{
	animator.Play(&RES_TABLE_MGR.GetCharacterAnim(std::to_string((int)(type)), "COMBAT"));
	SetOrigin(Origins::BC);
}

void Character::SetToWalk()
{
	animator.Play(&RES_TABLE_MGR.GetCharacterAnim(std::to_string((int)(type)), "WALK"));
	SetOrigin(Origins::BC);
}

void Character::OnHit(int damage)
{

}

void Character::Reset(const CharacterInfo& info)
{
	type = info.type;
	SetSlot(info);
}

void Character::SetSlot(const CharacterInfo& info)
{
	switch (info.type) {
		case CharacterType::Crusader: 
		{
			skill = new SkillCrusader();
		}
		default:
		{

		}
	}
	json j = info;
	for (int i = 0; i < 4; i++) {
		AddSkill(std::stoi(j["skill" + std::to_string(i + 1)][1].get<std::string>()));
	}


}

void Character::AddSkill(int num)
{

	switch (num){
	case 1:
	{
		std::function<void(std::vector<CharacterContainer*>, std::vector<MonsterContainer*>, short, short)> skill1 = std::bind(&Skill::skill1, skill, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
		skillSlot->InsertSkill(skill1, skill->skillrange1);
		break;
	}
	case 2:
	{
		std::function<void(std::vector<CharacterContainer*>, std::vector<MonsterContainer*>, short, short)> skill2 = std::bind(&Skill::skill2, skill, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
		skillSlot->InsertSkill(skill2, skill->skillrange2);
		break;
	}
	case 3: 
	{
		std::function<void(std::vector<CharacterContainer*>, std::vector<MonsterContainer*>, short, short)> skill3 = std::bind(&Skill::skill3, skill, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
		skillSlot->InsertSkill(skill3, skill->skillrange3);
		break;
	}
	case 4:
	{
		std::function<void(std::vector<CharacterContainer*>, std::vector<MonsterContainer*>, short, short)> skill4 = std::bind(&Skill::skill4, skill, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
		skillSlot->InsertSkill(skill4, skill->skillrange4);
		break;
	}
	}
}

void Character::UseSkill(std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target, int num )
{
	skillSlot->UseSkill(characters, monsters, user, target, num);
	int skillNum;
	switch(num) {
		case 1: {
			skillNum = std::stoi(characters[user]->GetCharacterInfo().skill1[1]);
			animator.Play(std::to_string((int)type), skillNum);
			break;
		}
		case 2: {
			skillNum = std::stoi(characters[user]->GetCharacterInfo().skill2[1]);
			animator.Play(std::to_string((int)type), skillNum);
			break;
		}
		case 3: {
			skillNum = std::stoi(characters[user]->GetCharacterInfo().skill3[1]);
			animator.Play(std::to_string((int)type), skillNum);
			break;
		}
		case 4: {
			skillNum = std::stoi(characters[user]->GetCharacterInfo().skill4[1]);
			animator.Play(std::to_string((int)type), skillNum);
			break;
		}
	}
	SetOrigin(Origins::BC);
}


std::vector<int> Character::CheckAvailableSkill(int pos)
{
	std::vector<int>buf;
	for (int i = 0; i < 4; i++) {
		if (skillSlot->GetRange(i)[4 - pos] == 1)
		{
			buf.push_back(i);
		};
	}
	return buf;
}

std::vector<short>& Character::GetSkillRange(int skillnum)
{
	return skillSlot->GetRange(skillnum);
}
