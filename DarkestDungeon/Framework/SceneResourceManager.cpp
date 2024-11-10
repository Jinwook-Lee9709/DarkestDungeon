#include "stdafx.h"
#include "SceneResourceManager.h"

void SceneResourceManager::init()
{
	RES_MGR(sf::Texture);
	RES_MGR(sf::Font);
	RES_MGR(sf::SoundBuffer);
	std::ifstream file("Config/PATH.json", std::ios::in);
	if (!file) {
		std::cerr << "Failed to Read File";
	}
	PATH = json::parse(file);
	file.close();
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

sf::Texture& SceneResourceManager::GetTex(const std::string& scene, const std::string& textureId)
{
	auto path = PATH["scene"][scene]["Texture"][textureId];
	return 	RES_MGR(sf::Texture).Get(path);
}

sf::Font& SceneResourceManager::GetFont(const std::string& scene, const std::string& fontId)
{
	auto path = PATH["scene"][scene]["Font"][fontId];
	return 	RES_MGR(sf::Font).Get(path);
}

sf::SoundBuffer& SceneResourceManager::GetSound(const std::string& scene, const std::string& soundId)
{
	auto path = PATH["scene"][scene]["Sound"][soundId];
	return 	RES_MGR(sf::SoundBuffer).Get(path);
}
