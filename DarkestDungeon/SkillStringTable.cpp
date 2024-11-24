#include "stdafx.h"
#include "SkillStringTable.h"

bool SkillStringTable::Load()
{
	std::ifstream file1(filePath, std::ios::in);
	if (!file1) {
		std::cerr << "Failed to Read File";
	}
	TABLE = json::parse(file1);
	file1.close();
	return false;
}

void SkillStringTable::Release()
{
	TABLE.clear();
}

const json& SkillStringTable::Get(const std::string& skill_id)
{
	return TABLE[skill_id];
}
