#include "stdafx.h"
#include "Scene.h"

Scene::Scene(SceneIds id)
	:id(id)
{

}
//씬이 생성될 때
void Scene::Init()
{
	ApplyAddGo();
	ApplyDeleteGo();
	for (auto obj : gameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		obj->Release();
		delete obj;
	}
	gameObjects.clear();
}
//씬을 다시 불러올 때
void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
}

void Scene::Exit()
{
	ApplyAddGo();
	ApplyDeleteGo();
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		obj->Update(dt);
	}
}

void Scene::LateUpdate(float dt)
{

}

void Scene::OnPreDraw()
{
}

void Scene::Draw(sf::RenderWindow& window)
{
	std::priority_queue<GameObject*, std::vector<GameObject*>, DrawOrderComparer> drawQueue;
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		drawQueue.push(obj);
	}
	while (!drawQueue.empty()) 
	{
		GameObject* obj = (drawQueue.top());
		obj->Draw(window);
		drawQueue.pop();
	}
}

void Scene::OnPostDraw()
{
	ApplyAddGo();
	ApplyDeleteGo();
}



void Scene::RemoveGo(GameObject* obj)
{
	removeGameObjects.push_back(obj);
}

GameObject* Scene::FindGo(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	return nullptr;
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list)
{
	int cnt = 0;
	list.clear();
	/*std::find_if(gameObjects.begin(), gameObjects.end(),
		[&](GameObject* obj) {
			if (obj->GetName() == name) {
				cnt++;
				list.push_front(obj);
			}
			return false;
		});*/
	for (auto obj : gameObjects) {
		if (obj->GetName() == name)
		{
			cnt++;
			list.push_front(obj);
		}
	}
	return cnt;
}

void Scene::ApplyAddGo()
{
	for (auto go : addGameObjects)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) == gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	addGameObjects.clear();
}

void Scene::ApplyDeleteGo()
{
	for (auto go : removeGameObjects)
	{
		gameObjects.remove(go);
	}
	removeGameObjects.clear();
}

//template <typename T>
//T* AddGo(T* obj)
//{
//	if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
//	{
//		gameObjects.push_back(obj);
//	}
//	return obj;
//}
