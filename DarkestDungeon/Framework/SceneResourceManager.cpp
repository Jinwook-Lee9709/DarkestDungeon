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
	auto it = PATH["scene"][scene]["Texture"].begin();
	while (it != PATH["scene"][scene]["Texture"].end()) {
		if (!RES_MGR(sf::Texture).Load(it.value())) {
		std::cout << "LoadFail:" << it.value() << std::endl;
		}
		else
		{
			resourceTable.insert({it.key(), it.value()});
		}
		it++;
	}
	for (auto& path : PATH["scene"][scene]["Font"]) {
		if (!RES_MGR(sf::Font).Load(path)) {
			std::cout << "LoadFail:" << path << std::endl;
		}
		
	}

	for (auto& path : PATH["scene"][scene]["Sound"]) {
		if (!RES_MGR(sf::SoundBuffer).Load(path)) {
			std::cout << "LoadFail:" << path << std::endl;
		}
	
	}

	return true;
}

bool SceneResourceManager::UnLoad(const std::string& scene)
{
	for (auto& path : PATH["scene"][scene]["Texture"]) {
		if (!RES_MGR(sf::Texture).UnLoad(path)) {
			std::cout << "UnLoadFail:" << path << std::endl;
		}
	}
	for (auto& path : PATH["scene"][scene]["Font"]) {
		if (!RES_MGR(sf::Font).UnLoad(path)) {
			std::cout << "UnLoadFail:" << path << std::endl;
		}
	}

	for (auto& path : PATH["scene"][scene]["Sound"]) {
		if (!RES_MGR(sf::SoundBuffer).UnLoad(path)) {
			std::cout << "UnLoadFail:" << path << std::endl;
		}
	}
	return true;
}

sf::Texture& SceneResourceManager::GetTex(const std::string& texKey)
{
	auto it = resourceTable.find(texKey);
	return 	RES_MGR(sf::Texture).Get(it->second);
}

sf::Font& SceneResourceManager::GetFont(const std::string& fontKey)
{
	auto it = resourceTable.find(fontKey);
	return 	RES_MGR(sf::Font).Get(it->second);
}

sf::SoundBuffer& SceneResourceManager::GetSound(const std::string& soundKey)
{
	auto it = resourceTable.find(soundKey);
	return 	RES_MGR(sf::SoundBuffer).Get(it->second);
}
