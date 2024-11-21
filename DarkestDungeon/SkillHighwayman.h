#pragma once
#include "Skill.h"

struct SkillHighwayman : public Skill
{
	SkillHighwayman():Skill() {
		skillrange1 = { 1,
		0, 1, 1, 1,
		1, 1, 0, 0 };
		skillrange2 = { 1,
		0, 1, 1, 1,
		0, 1, 1, 1 };
		skillrange3 = { 1,
		0, 0, 0, 1,
		1, 0, 0, 0 };
		skillrange4 = { 3,
		0, 1, 1, 0,
		1, 1, 1, 0 };
	}

	void skill1(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = characters[user]->GetCharacterInfo().minDamage;
		int maxDamage = characters[user]->GetCharacterInfo().minDamage;
		int accuracy = characters[user]->GetCharacterInfo().accuracy;
		int critical = characters[user]->GetCharacterInfo().critical;
		int damage = Utils::Truncate(1.15f * Utils::RandomRange(minDamage, maxDamage));
		if (Utils::RollTheDice((critical + 5) / 100)) {
			damage = Utils::Truncate(damage * 1.5f);
			accuracy = 300;
		}
		if (monsters[target]->OnHit(damage, accuracy + 85))
		{
			monsters[target]->PlayMiddleEffect("blood");
		}
		
	}
	void skill2(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = characters[user]->GetCharacterInfo().minDamage;
		int maxDamage = characters[user]->GetCharacterInfo().minDamage;
		int accuracy = characters[user]->GetCharacterInfo().accuracy;
		int critical = characters[user]->GetCharacterInfo().critical;
		int damage = Utils::Truncate(0.85f * Utils::RandomRange(minDamage, maxDamage));
		if (Utils::RollTheDice((critical + 7.5) / 100)) {
			damage = Utils::Truncate(damage * 1.5f);
			accuracy = 300;
		}
		if (monsters[target]->OnHit(damage, accuracy + 85))
		{
			monsters[target]->PlayMiddleEffect("highwayman_shot_target");
		}
	}
	void skill3(
		std::vector<CharacterContainer*>characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = characters[user]->GetCharacterInfo().minDamage;
		int maxDamage = characters[user]->GetCharacterInfo().minDamage;
		int accuracy = characters[user]->GetCharacterInfo().accuracy;
		int critical = characters[user]->GetCharacterInfo().critical;
		int damage = Utils::Truncate(1.5f * Utils::RandomRange(minDamage, maxDamage));
		if (Utils::RollTheDice((critical + 5) / 100)) {
			damage = Utils::Truncate(damage * 1.5f);
			accuracy = 300;
		}
		if (monsters[target]->OnHit(damage, accuracy + 95))
		{
			monsters[target]->PlayMiddleEffect("highwayman_grapeshot_target");
		}
	}
	void skill4(
		std::vector<CharacterContainer*>characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = characters[user]->GetCharacterInfo().minDamage;
		int maxDamage = characters[user]->GetCharacterInfo().minDamage;
		int accuracy = characters[user]->GetCharacterInfo().accuracy;
		int critical = characters[user]->GetCharacterInfo().critical;
		int currentTarget = target;
		for (int i = 0; i < 3; i++) {
			if (monsters[currentTarget]->IsAlive()) {
				int damage = Utils::Truncate(0.5f * Utils::RandomRange(minDamage, maxDamage));
				if (Utils::RollTheDice((critical - 9) / 100)) {
					damage = Utils::Truncate(damage * 1.5f);
					accuracy = 300;
				}
				if (monsters[currentTarget]->OnHit(damage, accuracy + 75))
				{
					monsters[currentTarget]->PlayMiddleEffect("highwayman_grapeshot_target");
				}
			}
			if (monsters[currentTarget]->GetPos() == 4) 
			{
				currentTarget = FindMonster(monsters, 5);
			}
			else if(monsters[currentTarget]->GetPos() == 5) 
			{
				currentTarget = FindMonster(monsters, 6);
			}
			else
			{
				currentTarget = FindMonster(monsters, 4);
			}

		}
	}
};


