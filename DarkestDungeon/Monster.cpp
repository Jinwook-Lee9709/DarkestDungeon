#include "stdafx.h"
#include "Monster.h"
#include "Character.h"
#include "SkillCrusader.h"
#include "Skill.h"
#include "Slot.h"

Monster::Monster(const std::string& name)
	: GameObject(name)
{
}

void Monster::Monster(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Monster::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Monster::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Monster::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Monster::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Monster::Init()
{
	skillSlot = new Slot();
	animator.SetTarget(&body);
}

void Monster::Release()
{
}

void Monster::Reset()
{
	animator.Play("crusader_idle");

}

void Monster::Update(float dt)
{
	animator.Update(dt);

}

void Monster::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Monster::SetToIdle()
{
}

void Monster::SetToCombat()
{
}

void Monster::SetToWalk()
{
}

void Monster::OnHit(int damage)
{
}

void Monster::Reset(const CharacterInfo& info)
{
	type = info.type;
	SetSlot(info);
}

void Monster::SetSlot(const CharacterInfo& info)
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

void Monster::AddSkill(int num)
{

	switch (num) {
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

void Monster::UseSkill(std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target, int num)
{
	skillSlot->UseSkill(characters, monsters, user, target, num);
	int skillNum;
	switch (num) {
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