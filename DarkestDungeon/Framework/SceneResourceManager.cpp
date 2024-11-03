#include "stdafx.h"
#include "SceneResourceManager.h"

void SceneResourceManager::init()
{
	RES_MGR(sf::Texture);
	RES_MGR(sf::Font);
	RES_MGR(sf::SoundBuffer);
	std::ifstream file("Config/PATH.json", std::ios::in);
	PATH = json::parse(file);
}

bool SceneResourceManager::Load(const std::string& scene)
{
	for (auto path : PATH["scene"][scene]["Texture"]) {
		if (!RES_MGR(sf::Texture).Load(path)) {
		std::cout << "LoadFail:" << path << std::endl;
		}
	}
	for (auto path : PATH["scene"][scene]["Font"]) {
		if (!RES_MGR(sf::Font).Load(path)) {
			std::cout << "LoadFail:" << path << std::endl;
		}
	}

	for (auto path : PATH["scene"][scene]["Sound"]) {
		if (!RES_MGR(sf::SoundBuffer).Load(path)) {
			std::cout << "LoadFail:" << path << std::endl;
		}
	}

	return true;
}

bool SceneResourceManager::UnLoad(const std::string& scene)
{
	for (auto path : PATH["scene"][scene]["Texture"]) {
		if (!RES_MGR(sf::Texture).UnLoad(path)) {
			std::cout << "UnLoadFail:" << path << std::endl;
		}
	}
	for (auto path : PATH["scene"][scene]["Font"]) {
		if (!RES_MGR(sf::Font).UnLoad(path)) {
			std::cout << "UnLoadFail:" << path << std::endl;
		}
	}

	for (auto path : PATH["scene"][scene]["Sound"]) {
		if (!RES_MGR(sf::SoundBuffer).UnLoad(path)) {
			std::cout << "UnLoadFail:" << path << std::endl;
		}
	}
	return true;
}
