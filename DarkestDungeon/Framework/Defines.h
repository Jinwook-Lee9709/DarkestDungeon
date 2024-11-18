#pragma once

using json = nlohmann::json;

enum class SortingLayers
{
	Background,
	Test,
	Foreground,
	Default,
	UI,

};

enum class SceneIds
{
	None = -1,
	Dev1,
	Dev2,
	Game,
	Count,
};

enum class Origins
{
	TL, TC, TR, 
	ML, MC, MR, 
	BL, BC, BR,
	Custom
};

enum class Sides
{
	Left,
	Right,
	None
};

enum class DebufType
{
	Stun,
	Bleeding,
	Poison
};

enum class CharacterType
{
	Crusader,
};
enum class MonsterType
{
	Skeleton_militia,
};


struct CharacterInfo
{
	std::string name;
	CharacterType type;
	int hp;
	int maxHp;
	int stress;
	int speed;
	int dodge;
	float accuracy;
	float critical;
	float minDamage;
	float maxDamage;
	float protect;
	std::vector<std::string> skill1;
	std::vector<std::string> skill2;
	std::vector<std::string> skill3;
	std::vector<std::string> skill4;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(CharacterInfo
		, name, type, hp, maxHp, stress, speed, dodge,
		accuracy, critical, minDamage, maxDamage, protect, skill1, skill2, skill3, skill4);
};

enum class TargetUi
{
	SELECT,
	ENEMY,
	HEAL,
	CHANGEPOS
};