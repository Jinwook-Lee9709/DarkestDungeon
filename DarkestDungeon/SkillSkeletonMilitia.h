#pragma once
#include "Skill.h"

struct SkillSkeletonMilitia : public Skill
{
	SkillSkeletonMilitia() :Skill() {
		skillrange1 = { 1,
		1, 1, 1, 0,
		0, 1, 1, 1 };
		skillrange2 = { 1,
		0, 0, 0, 1,
		1, 1, 0, 0 };
	}

	void skill1(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = monsters[user]->GetMonsterInfo().minDamage;
		int maxDamage = monsters[user]->GetMonsterInfo().minDamage;
		int accuracy = monsters[user]->GetMonsterInfo().accuracy;
		int critical = monsters[user]->GetMonsterInfo().critical;
		int damage = Utils::RandomRange(minDamage, maxDamage);
		float critDice = Utils::RandomValue();
		if (critDice < (critical + 5) / 100) {
			damage = Utils::Truncate(damage * 1.5f);
			accuracy = 300;
		}
		characters[target]->OnHit(damage, accuracy + 82.5);
		characters[target]->PlayMiddleEffect("blood");
	}
	void skill2(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = monsters[user]->GetMonsterInfo().minDamage;
		int maxDamage = monsters[user]->GetMonsterInfo().minDamage;
		int accuracy = monsters[user]->GetMonsterInfo().accuracy;
		int critical = monsters[user]->GetMonsterInfo().critical;
		int damage = Utils::RandomRange(minDamage, maxDamage);
		float critDice = Utils::RandomValue();
		if (critDice < (critical + 5) / 100) {
			damage = Utils::Truncate(damage * 1.5f);
			accuracy = 300;
		}
		if (characters[target]->OnHit(damage * 0.5f, accuracy + 90))
		{
			characters[target]->OnDebuffed(DebuffType::Stun, accuracy + 100);
			characters[target]->PlayMiddleEffect("blood");
		}
		
	}

};