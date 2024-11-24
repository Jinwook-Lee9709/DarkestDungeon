#pragma once
#include "Skill.h"

struct SkillVestal : public Skill
{
	SkillVestal():Skill() {
		skillrange1 = { 1,
		0, 0, 1, 1,
		1, 1, 0, 0 };
		skillrange2 = { 1,
		1, 1, 0, 0,
		1, 1, 1, 1 };
		skillrange3 = { 0,
		1, 1, 0, 0,
		1, 1, 1, 1 };
		skillrange4 = { 2,
		1, 1, 1, 0,
		1, 1, 1, 1 };
	}

	void skill1(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = characters[user]->GetCharacterInfo().minDamage;
		int maxDamage = characters[user]->GetCharacterInfo().minDamage;
		int accuracy = characters[user]->GetCharacterInfo().accuracy;
		int critical = characters[user]->GetCharacterInfo().critical;
		int damage = Utils::Truncate(1.f * Utils::RandomRange(minDamage, maxDamage));
		if (Utils::RollTheDice(critical / 100)) {
			damage = Utils::Truncate(damage * 1.5f);
			accuracy = 300;
			SOUND_MGR.PlaySfx("crit_hero");
		}
		if (monsters[target]->OnHit(damage, accuracy + 85))
		{
			SOUND_MGR.PlaySfx("bleed_onset");
		}
		monsters[target]->PlayMiddleEffect("blood");
		SOUND_MGR.PlaySfx("vst_macebash");
	}
	void skill2(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int minDamage = characters[user]->GetCharacterInfo().minDamage;
		int maxDamage = characters[user]->GetCharacterInfo().minDamage;
		int accuracy = characters[user]->GetCharacterInfo().accuracy;
		int critical = characters[user]->GetCharacterInfo().critical;
		int damage = Utils::Truncate(0.75f * Utils::RandomRange(minDamage, maxDamage));
		if (Utils::RollTheDice((critical + 5) / 100)) {
			damage = Utils::Truncate(damage * 1.5f);
			accuracy = 300;
			SOUND_MGR.PlaySfx("crit_hero");
		}
		if (monsters[target]->OnHit(damage, accuracy + 85))
		{
			characters[user]->OnHeal(3);
			characters[user]->PlayBottomEffect("vestal_heal_target");
		}
		monsters[target]->PlayMiddleEffect("vestal_judgement_target");
		SOUND_MGR.PlaySfx("vst_judgement");
		SOUND_MGR.PlaySfx("heal_dot");
	}
	void skill3(
		std::vector<CharacterContainer*>characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		int heal = Utils::RandomRange(4, 5);
		if (Utils::RollTheDice(0.12f)) {
			heal = Utils::Truncate(heal * 1.5f);
		}
		characters[target]->OnHeal(heal);
		characters[target]->PlayBottomEffect("vestal_heal_target");
		SOUND_MGR.PlaySfx("vst_divinegrace");
	}
	void skill4(
		std::vector<CharacterContainer*>characters, std::vector<MonsterContainer*> monsters, short user, short target
	) override {
		for (int i = 0; i < 4; i++)
		{
			int heal = Utils::RandomRange(4, 5);
			if (Utils::RollTheDice(0.12f)) {
				heal = Utils::Truncate(heal * 1.5f);
			}
			characters[i]->OnHeal(heal);
			characters[i]->PlayBottomEffect("vestal_heal_target");
		}
		SOUND_MGR.PlaySfx("vst_godscom");
	}
};


