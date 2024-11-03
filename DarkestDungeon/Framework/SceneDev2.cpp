#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "TextGo.h"

SceneDev2::SceneDev2()
	: Scene(SceneIds::Dev2)
{

}

void SceneDev2::Init()
{
	std::cout << "SceneDev2:: Init()" << std::endl;

	AddGo(new SpriteGo("graphics/Desert.png"));
	GameObject* obj2 = AddGo(new TextGo("fonts/Sansation.ttf"));
	obj2->SetOrigin(Origins::TC);
	obj2->SetPosition({ 1920 / 2, 20 });
	Scene::Init();
}

void SceneDev2::Enter()
{
	std::cout << "SceneDev2:: Enter()" << std::endl;

	RES_MGR(sf::Texture).Load("graphics/Desert.png");

	Scene::Enter();
}

void SceneDev2::Exit()
{
	std::cout << "SceneDev2:: Exit()" << std::endl;

	Scene::Exit();

	RES_MGR(sf::Texture).UnLoad("graphics/Desert.png");
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);
	if (InputManager::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}