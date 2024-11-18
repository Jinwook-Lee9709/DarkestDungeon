#pragma once

class StringTable : public DataTable
{
public:
	static std::string Undefined;
protected:
	std::unordered_map<std::string, std::string> table;

	std::string filePath = "tables/string_table.csv";



public:
	StringTable() : DataTable(DataTable::Types::String) { };
	~StringTable() = default;

	bool Load() override;
	void Release() override;

	const std::string& Get(const std::string& id);

};