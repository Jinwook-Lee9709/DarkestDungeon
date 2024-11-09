#pragma once

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

using json = nlohmann::json;