#pragma once
#include "Singleton.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class SceneResourceManager :
    public Singleton<SceneResourceManager>
{
    friend class Singleton<SceneResourceManager>;
private:
	json PATH;
	std::unordered_map <std::string, std::string> resourceTable;

public:
	void init();
	bool Load(const std::string& scene);
	bool UnLoad(const std::string& scene);
	sf::Texture& GetTex(const std::string& texKey);
	sf::Font& GetFont(const std::string& fontKey);
	sf::SoundBuffer& GetSound(const std::string& soundKey);
};

#define SCENE_RES_MGR (SceneResourceManager::Instance())
