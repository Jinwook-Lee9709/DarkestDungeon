#include "stdafx.h"
#include "StringTable.h"
#include "rapidcsv.h"

std::string StringTable::Undefined = "Undefined Id";

bool StringTable::Load()
{
	Release();

	rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));
	for (int i = 0; i < doc.GetRowCount(); ++i)
	{
		std::vector<std::string> strings = doc.GetRow<std::string>(i);
		auto it = table.find(strings[0]);
		if (it != table.end())
		{
			std::cout << "스트링 테이블 키 중복!" << std::endl;
			return false;
		}
		table[strings[0]] = strings[1];
	}

	return true;
}

void StringTable::Release()
{
	table.clear();
}

const std::string& StringTable::Get(const std::string& id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		return Undefined;
	}
	//return find->second;
	return (find->second);
}
