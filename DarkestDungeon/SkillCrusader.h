#pragma once
#include "Skill.h"

struct SkillCrusader : public Skill
{
	SkillCrusader() :Skill() {
		skillrange1 = { 1,
		0, 0, 1, 1,
		1, 1, 0, 0 };
		skillrange2 = { 1,
		0, 0, 1, 1,
		1, 1, 0, 0 };
		skillrange3 = { 0,
		0, 0, 1, 1,
		1, 1, 1, 1 };
		skillrange4 = { 3,
		0, 0, 1, 1,
		1, 1, 0, 0 };
	}

	void skill1(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = characters[user]->GetCharacterInfo().minDamage;
		int maxDamage = characters[user]->GetCharacterInfo().minDamage;
		int accuracy = characters[user]->GetCharacterInfo().accuracy;
		int critical = characters[user]->GetCharacterInfo().critical;
		int damage = 1.15 * Utils::RandomRange(minDamage, maxDamage);
		if (Utils::RollTheDice((critical + 5) / 100)) {
			damage = Utils::Truncate(damage * 1.5f);
			accuracy = 300;
		}
		monsters[target]->OnHit(damage, accuracy + 85);
		monsters[target]->PlayMiddleEffect("blood");

	}
	void skill2(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = characters[user]->GetCharacterInfo().minDamage;
		int maxDamage = characters[user]->GetCharacterInfo().minDamage;
		int accuracy = characters[user]->GetCharacterInfo().accuracy;
		int critical = characters[user]->GetCharacterInfo().critical;
		int damage = Utils::RandomRange(minDamage, maxDamage);
		if (Utils::RollTheDice((critical + 5) / 100)) {
			damage = Utils::Truncate(damage * 1.5f);
			accuracy = 300;
		}
		if (monsters[target]->OnHit(damage * 0.5f, accuracy + 90))
		{
			monsters[target]->OnDebuffed(DebuffType::Stun, accuracy + 100, 0, 1);
			monsters[target]->PlayMiddleEffect("crusader_stun_target");
		}	
	}
	void skill3(
		std::vector<CharacterContainer*>characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int heal = Utils::RandomRange(3, 4);
		if (Utils::RollTheDice(0.12f)) {
			heal = Utils::Truncate(heal * 1.5f);
		}
		characters[target]->OnHeal(heal);
		characters[target]->PlayBottomEffect("crusader_heal_target");
	}
	void skill4(
		std::vector<CharacterContainer*>characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = characters[user]->GetCharacterInfo().minDamage;
		int maxDamage = characters[user]->GetCharacterInfo().minDamage;
		int accuracy = characters[user]->GetCharacterInfo().accuracy;
		int critical = characters[user]->GetCharacterInfo().critical;
		int currentTarget = target;
		for (int i = 0; i < 2; i++) {
			if (monsters[currentTarget]->IsAlive()) {
				int damage = Utils::RandomRange(minDamage, maxDamage);
				float critDice = Utils::RandomValue();
				if (Utils::RollTheDice((critical + 5) / 100)) {
					damage = Utils::Truncate(damage * 1.5f);
					accuracy = 300;
				}
				if (monsters[currentTarget]->OnHit(Utils::Truncate(damage * 0.6f), accuracy + 90))
				{
					monsters[currentTarget]->PlayMiddleEffect("blood");
				}

			}
			if (monsters[currentTarget]->GetPos() == 4) {
				currentTarget = FindMonster(monsters, 5);
			}
			else {
				currentTarget = FindMonster(monsters, 4);
			}

		}

	}
};