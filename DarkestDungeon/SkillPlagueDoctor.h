#pragma once
#include "Skill.h"

struct SkillPlagueDoctor : public Skill
{
	SkillPlagueDoctor() :Skill() {
		skillrange1 = { 1,
		1, 1, 1, 0,
		1, 1, 0, 0 };
		skillrange2 = { 3,
		1, 1, 0, 0,
		0, 0, 1, 1 };
		skillrange3 = { 3,
		1, 1, 0, 0,
		0, 0, 1, 1 };
		skillrange4 = { 0,
		1, 1, 0, 0,
		1, 1, 1, 1 };
	}

	void skill1(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = characters[user]->GetCharacterInfo().minDamage;
		int maxDamage = characters[user]->GetCharacterInfo().minDamage;
		int accuracy = characters[user]->GetCharacterInfo().accuracy;
		int critical = characters[user]->GetCharacterInfo().critical;
		int damage = Utils::Truncate(0.2f * Utils::RandomRange(minDamage, maxDamage));
		if (Utils::RollTheDice((critical + 5) / 100)) {
			damage = Utils::Truncate(damage * 1.5f);
			accuracy = 300;
		}
		if (monsters[target]->OnHit(damage, accuracy + 95))
		{
			monsters[target]->OnDebuffed(DebuffType::Blight, accuracy + 95, 5, 3);
		}
		monsters[target]->PlayBottomEffect("plagueDoctor_blast_target");
	}
	void skill2(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = characters[user]->GetCharacterInfo().minDamage;
		int maxDamage = characters[user]->GetCharacterInfo().minDamage;
		int accuracy = characters[user]->GetCharacterInfo().accuracy;
		int critical = characters[user]->GetCharacterInfo().critical;
		int currentTarget = target;
		for (int i = 0; i < 2; i++) {
			if (monsters[currentTarget]->IsAlive()) {
				int damage = Utils::Truncate(0.1f * Utils::RandomRange(minDamage, maxDamage));
				if (Utils::RollTheDice(critical / 100)) {
					damage = Utils::Truncate(damage * 1.5f);
					accuracy = 300;
				}
				if (monsters[currentTarget]->OnHit(damage, accuracy + 95))
				{
					monsters[currentTarget]->OnDebuffed(DebuffType::Blight, accuracy + 95, 4, 3);
				}
				monsters[currentTarget]->PlayBottomEffect("plagueDoctor_plagueGrenade_target");
			}
			if (monsters[currentTarget]->GetPos() == 6)
			{
				currentTarget = FindMonster(monsters, 7);
			}
			else
			{
				currentTarget = FindMonster(monsters, 6);
			}

		}

	}
	void skill3(
		std::vector<CharacterContainer*>characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = characters[user]->GetCharacterInfo().minDamage;
		int maxDamage = characters[user]->GetCharacterInfo().minDamage;
		int accuracy = characters[user]->GetCharacterInfo().accuracy;
		int critical = characters[user]->GetCharacterInfo().critical;
		int currentTarget = target;
		for (int i = 0; i < 2; i++) {
			if (monsters[currentTarget]->IsAlive()) {
				int damage = 0;
				if (Utils::RollTheDice(critical / 100)) {
					accuracy = 300;
				}
				if (monsters[currentTarget]->OnHit(damage, accuracy + 95))
				{
					monsters[currentTarget]->OnDebuffed(DebuffType::Stun, accuracy + 95);
				}
				monsters[currentTarget]->PlayBottomEffect("plagueDoctor_stunGrenade_target");
			}
			if (monsters[currentTarget]->GetPos() == 6)
			{
				currentTarget = FindMonster(monsters, 7);
			}
			else
			{
				currentTarget = FindMonster(monsters, 6);
			}

		}
	}
	void skill4(
		std::vector<CharacterContainer*>characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int heal = Utils::RandomRange(3, 4);
		if (Utils::RollTheDice(0.12f)) {
			heal = Utils::Truncate(heal * 1.5f);
		}
		characters[target]->OnHeal(heal);
		characters[target]->PlayBottomEffect("plagueDoctor_heal_target");
		characters[target]->CureDebuff(DebuffType::Bleed);
		characters[target]->CureDebuff(DebuffType::Blight);
	}
};


