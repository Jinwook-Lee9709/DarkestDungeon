#include "stdafx.h"
#include "AnimationClip.h"

bool AnimationClip::loadFromFile(const std::string& fileId)
{
	rapidcsv::Document Doc("animation/animation.csv");
	auto row =  Doc.GetRow<std::string>(fileId);
	id = fileId;
	loopType = (AnimationLoopTypes)std::stoi(row[2]);
	fps = std::stoi(row[3]);
	int width = std::stoi(row[6]);
	int height = std::stoi(row[7]);
	int sheetWidth = width * std::stoi(row[4]);

	frames.clear();


	sf::IntRect texCoord = { 0, 0, width, height };
	for (int i = 0; i < std::stoi(row[5]); i++) 
	{
		frames.push_back({row[1], texCoord});
		texCoord.left += width;
		if (texCoord.left == sheetWidth)
		{
			texCoord.left = 0;
			texCoord.height += height;
		}
	}
	return true;
}
