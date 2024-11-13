#pragma once
#include "Singleton.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class ResourceTableManager :
    public Singleton<ResourceTableManager>
{
    friend class Singleton<ResourceTableManager>;
private:
	json PATH;
	std::unordered_map <std::string, std::string> resourceTable;
	std::string err = "";
public:
	void init();
	bool Load(const std::string& scene);
	bool UnLoad(const std::string& scene);
	sf::Texture& GetTex(const std::string& texKey);
	sf::Font& GetFont(const std::string& fontKey);
	sf::SoundBuffer& GetSound(const std::string& soundKey);

	std::string& GetPath(const std::string& key);
};

#define RES_TABLE_MGR (ResourceTableManager::Instance())
#define GET_TEX(X) (RES_TABLE_MGR.GetTex(X))
#define GET_FONT(X) (RES_TABLE_MGR.GetFont(X))
#define GET_SOUND(X) (RES_TABLE_MGR.GetSound(X))
