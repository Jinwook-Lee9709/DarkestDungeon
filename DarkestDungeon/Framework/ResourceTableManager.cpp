#include "stdafx.h"
#include "ResourceTableManager.h"

void ResourceTableManager::init()
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

bool ResourceTableManager::Load(const std::string& scene)
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
	it = PATH["scene"][scene]["Font"].begin();
	while (it != PATH["scene"][scene]["Font"].end()) {
		if (!RES_MGR(sf::Font).Load(it.value())) {
			std::cout << "LoadFail:" << it.value() << std::endl;
		}
		else
		{
			resourceTable.insert({ it.key(), it.value() });
		}
		it++;
		
	}
	it = PATH["scene"][scene]["Sound"].begin();
	while (it != PATH["scene"][scene]["Sound"].end()) {
		if (!RES_MGR(sf::SoundBuffer).Load(it.value())) {
			std::cout << "LoadFail:" << it.value() << std::endl;
		}
		else
		{
			resourceTable.insert({ it.key(), it.value() });
		}
		it++;

	}

	return true;
}

bool ResourceTableManager::UnLoad(const std::string& scene)
{
	auto it = PATH["scene"][scene]["Texture"].begin();
	while (it != PATH["scene"][scene]["Texture"].end()) {
		if (!RES_MGR(sf::Texture).UnLoad(it.value())) {
			std::cout << "UnLoadFail:" << it.value() << std::endl;
		}
		else
		{
			resourceTable.erase({ it.key(), it.value() });
		}
		it++;
	}
	it = PATH["scene"][scene]["Font"].begin();
	while (it != PATH["scene"][scene]["Font"].end()) {
		if (!RES_MGR(sf::Font).UnLoad(it.value())) {
			std::cout << "UnLoadFail:" << it.value() << std::endl;
		}
		else
		{
			resourceTable.erase({ it.key(), it.value() });
		}
		it++;
	}
	it = PATH["scene"][scene]["Sound"].begin();
	while (it != PATH["scene"][scene]["Sound"].end()) {
		if (!RES_MGR(sf::SoundBuffer).UnLoad(it.value())) {
			std::cout << "UnLoadFail:" << it.value() << std::endl;
		}
		else
		{
			resourceTable.erase({ it.key(), it.value() });
		}
		it++;
	}
	return true;
}

sf::Texture& ResourceTableManager::GetTex(const std::string& texKey)
{
	auto it = resourceTable.find(texKey);
	if (it == resourceTable.end()) {
		std::cout << "No Value matched with Key: " << texKey << std::endl;
	}
	return 	RES_MGR(sf::Texture).Get(it->second);
}

sf::Font& ResourceTableManager::GetFont(const std::string& fontKey)
{
	auto it = resourceTable.find(fontKey);
	if (it == resourceTable.end()) {
		std::cout << "No Value matched with Key: " << fontKey << std::endl;
	}
	return 	RES_MGR(sf::Font).Get(it->second);
}

sf::SoundBuffer& ResourceTableManager::GetSound(const std::string& soundKey)
{
	auto it = resourceTable.find(soundKey);
	if (it == resourceTable.end()) {
		std::cout << "No Value matched with Key: " << soundKey << std::endl;
	}
	return 	RES_MGR(sf::SoundBuffer).Get(it->second);
}

std::string& ResourceTableManager::GetPath(const std::string& key)
{
	auto it = resourceTable.find(key);
	if (it == resourceTable.end()) {
		std::cout << "Can't find" << key << " in Resource table!";
		return err;
	}
	return resourceTable.find(key)->second;
}
