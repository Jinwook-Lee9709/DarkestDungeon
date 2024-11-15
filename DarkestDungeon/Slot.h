#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include <bitset>
#include "Skill.h"



class Slot
{
private:
	std::vector <std::function<void(std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*>enemys, short user, short target)>> skills;
	std::vector <std::vector<short>> ranges;
public:
	void InsertSkill(
		std::function<void(std::vector<CharacterContainer*> characters, std::vector<MonsterContainer*> enemys, short user, short target)> func, std::vector<short> ranges)
	{
		this->skills.push_back(func);
		this->ranges.push_back(ranges);
	}
	void UseSkill(std::vector<CharacterContainer*>& characters, std::vector<MonsterContainer*>& enemys, short user, short target, int i) {
		skills[i](characters, enemys, user, target);
	}
	std::vector<short> GetTarget(int i) {
		std::vector<short> range = ranges[i];
	}
};