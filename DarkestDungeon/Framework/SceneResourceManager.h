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
};

#define SCENE_RES_MGR (SceneResourceManager::Instance())
