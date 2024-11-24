#pragma once
#include "DataTable.h"
class SkillStringTable :public DataTable
{
protected:
	json TABLE;

	std::string filePath = "tables/skill_string_table.json";
public:
	SkillStringTable() : DataTable(DataTable::Types::SkillString) {};
	~SkillStringTable() = default;

	bool Load() override;
	void Release() override;

	const json& Get(const std::string& skill_id);
};

