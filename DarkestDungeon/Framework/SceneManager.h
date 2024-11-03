#pragma once
#include "stdafx.h"

class Scene;
class SceneManager :public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;
protected:
	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::Dev1;
	SceneIds currentScene;

	SceneIds nextScene = SceneIds::None;

	SceneManager() = default;
	~SceneManager() = default; 

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	void OnPreDraw();
	void OnPostDraw();
public:
	void Init();
	void Release();

	Scene* GetCurrentScene() const { return scenes[(int)currentScene]; }
	SceneIds GetCurrentSceneId() const { return currentScene;  }
	void ChangeScene(SceneIds id);

	void Update(float dt);
	void LateUpdate(float dt);

	void Draw(sf::RenderWindow& window);

};

#define SCENE_MGR (SceneManager::Instance())

