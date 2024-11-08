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
public:
	void init();
	bool Load(const std::string& scene);
	bool UnLoad(const std::string& scene);
	sf::Texture& GetTex(const std::string& scene, const std::string& textureId);
	sf::Font& GetFont(const std::string& scene, const std::string& textureId);
	sf::SoundBuffer& GetSound(const std::string& scene, const std::string& textureId);
};

#define SCENE_RES_MGR (SceneResourceManager::Instance())
