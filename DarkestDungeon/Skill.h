#pragma once
#include "stdafx.h"
#include "CharacterContainer.h"
#include "MonsterContainer.h"

struct Skill {

	virtual void skill1(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) {}
	virtual void skill2(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) {}
	virtual void skill3(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) {}
	virtual void skill4(
		std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> monsters, short user, short target
	) {}

	std::vector<std::string> description;

	std::vector<short> skillrange1;
	std::string description1;
	
	std::vector<short> skillrange2;
	std::string description2;

	std::vector<short> skillrange3;
	std::string description3;

	std::vector<short> skillrange4;
	std::string description4;


	virtual int FindMonster(std::vector<MonsterContainer*> monsters, int pos) {
		for (int i = 0; i < 4; i++) {
			if (monsters[i]->GetPos() == pos) {
				return i;
			}
		}
		return -1;
	}
};
