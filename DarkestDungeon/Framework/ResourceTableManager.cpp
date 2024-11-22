#include "stdafx.h"
#include "ResourceTableManager.h"
#include "AnimationClip.h"

void ResourceTableManager::Init()
{
	RES_MGR(sf::Texture);
	RES_MGR(sf::Font);
	RES_MGR(sf::SoundBuffer);
	RES_MGR(sf::Shader);
	RES_MGR(AnimationClip);
	std::ifstream file1("Config/PATH.json", std::ios::in);
	if (!file1) {
		std::cerr << "Failed to Read File";
	}
	PATH = json::parse(file1);
	file1.close();
	std::ifstream file2("animation/animations.json", std::ios::in);
	if (!file2) {
		std::cerr << "Failed to Read File";
	}
	ANIMATION = json::parse(file2);
	file2.close();

}

bool ResourceTableManager::LoadCharacterAnimation(const CharacterType& character)
{
	auto animations = ANIMATION["Character"][std::to_string((int)character)];
	for (auto& animation : animations) {
		RES_MGR(AnimationClip).Load(animation["ID"]);
		RES_MGR(sf::Texture).Load(animation["TEX_ID"]);
		if (resourceTable.find(animation["ID"]) == resourceTable.end()) {
			resourceTable.insert({ (std::string)animation["ID"]
			,(std::string)animation["TEX_ID"] });
		}
	}
	return false;
}

bool ResourceTableManager::LoadMonsterAnimation()
{
	auto monsters = ANIMATION["Monster"][Variables::SelectedDungeon];
	for (auto& animations : monsters) {
		for (auto& animation : animations) {
			RES_MGR(AnimationClip).Load(animation["ID"]);
			RES_MGR(sf::Texture).Load(animation["TEX_ID"]);
			if (resourceTable.find(animation["ID"]) == resourceTable.end()) {
				resourceTable.insert({ (std::string)animation["ID"]
				,(std::string)animation["TEX_ID"] });
			}
		}
	}
	return false;
}

bool ResourceTableManager::LoadEffectAnimation()
{
	auto effects = ANIMATION["Effect"];
	for (auto& animation : effects) {
		RES_MGR(AnimationClip).Load(animation["ID"]);
		RES_MGR(sf::Texture).Load(animation["TEX_ID"]);
		if (resourceTable.find(animation["ID"]) == resourceTable.end()) {
			resourceTable.insert({ (std::string)animation["ID"]
			,(std::string)animation["TEX_ID"] });
			
		}
	}
	return false;
}

bool ResourceTableManager::LoadSkillIcon(const std::string& skillName)
{
	std::string path = PATH["Skill_icon"][skillName];
	if (!RES_MGR(sf::Texture).Load(path)) {
		std::cout << "LoadFail:" << path << std::endl;
	}
	resourceTable.insert({ skillName, path });
	return false;
}

bool ResourceTableManager::LoadPortrait(const std::string& portraitName)
{
	std::string path = PATH["Character_Portrait"][portraitName];
	if (!RES_MGR(sf::Texture).Load(path)) {
		std::cout << "LoadFail:" << path << std::endl;
	}
	resourceTable.insert({ portraitName, path });
	return false;
}

bool ResourceTableManager::LoadScene(const std::string& scene)
{
	auto it = PATH["scene"][scene]["Texture"].begin();
	while (it != PATH["scene"][scene]["Texture"].end()) {
		if (!RES_MGR(sf::Texture).Load(it.value())) {
		std::cout << "LoadFail:" << it.value() << std::endl;
		}
		else
		{
			if (resourceTable.find(it.key()) == resourceTable.end()) {
				resourceTable.insert({ it.key(), it.value() });
			}
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
			if (resourceTable.find(it.key()) == resourceTable.end()) {
				resourceTable.insert({ it.key(), it.value() });
			}
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
			if (resourceTable.find(it.key()) == resourceTable.end()) {
				resourceTable.insert({ it.key(), it.value() });
			}
		}
		it++;

	}

	return true;
}

bool ResourceTableManager::UnLoadScene(const std::string& scene)
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



AnimationClip& ResourceTableManager::GetAnim(const std::string& AnimId)
{
	auto it = resourceTable.find(AnimId);
	if (it == resourceTable.end()) {
		std::cout << "No Value matched with Id: " << AnimId << std::endl;
	}
	return 	RES_MGR(AnimationClip).Get(it->first);
}

AnimationClip& ResourceTableManager::GetCharacterSkillAnim(const std::string& type, const int& AnimCode)
{
	std::string strAnimCode = "SKILL" + std::to_string(AnimCode);
	std::string AnimId = ANIMATION["Character"][type][strAnimCode]["ID"].get<std::string>();

	auto it = resourceTable.find(AnimId);
	if (it == resourceTable.end()) {
		std::cout << "No Value matched with Id: " << AnimId << std::endl;
	}
	return 	RES_MGR(AnimationClip).Get(it->first);
}

AnimationClip& ResourceTableManager::GetCharacterAnim(const std::string& type, const std::string& AnimCode)
{
	std::string AnimId = ANIMATION["Character"][type][AnimCode]["ID"].get<std::string>();
	auto it = resourceTable.find(AnimId);
	if (it == resourceTable.end()) {
		std::cout << "No Value matched with Id: " << AnimId << std::endl;
	}
	return 	RES_MGR(AnimationClip).Get(it->first);
}


AnimationClip& ResourceTableManager::GetMonsterSkillAnim(const std::string& type, const int& AnimCode)
{
	std::string strAnimCode = "SKILL" + std::to_string(AnimCode);
	std::string AnimId = ANIMATION["Monster"][Variables::SelectedDungeon][type][strAnimCode]["ID"].get<std::string>();

	auto it = resourceTable.find(AnimId);
	if (it == resourceTable.end()) {
		std::cout << "No Value matched with Id: " << AnimId << std::endl;
	}
	return 	RES_MGR(AnimationClip).Get(it->first);
}

AnimationClip& ResourceTableManager::GetMonsterAnim(const std::string& type, const std::string& AnimCode)
{
	std::string AnimId = ANIMATION["Monster"][Variables::SelectedDungeon][type][AnimCode]["ID"].get<std::string>();

	auto it = resourceTable.find(AnimId);
	if (it == resourceTable.end()) {
		std::cout << "No Value matched with Id: " << AnimId << std::endl;
	}
	return 	RES_MGR(AnimationClip).Get(it->first);
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
