#pragma once

class Scene
{
protected:
	SceneIds id;
	std::list<GameObject*> gameObjects;
	std::list<GameObject*> addGameObjects;
	std::list<GameObject*> removeGameObjects;

	sf::View uiView;
	sf::View worldView;

public:
	Scene(SceneIds id);
	virtual ~Scene() = default;

	virtual void Init();
	virtual void Release();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void LateUpdate(float dt);

	virtual void OnPreDraw();
	virtual void Draw(sf::RenderWindow& window);
	virtual void OnPostDraw();


	template<typename T>
	T* AddGo(T* obj)
	{
		addGameObjects.push_back(obj);
		/*if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end()) {
			gameObjects.push_back(obj);
		}*/
		return obj;
	}

	virtual void RemoveGo(GameObject* obj);

	virtual GameObject* FindGo(const std::string& name);
	virtual int FindGoAll(const std::string& name, std::list<GameObject*>& list);
	
	void ApplyAddGo();
	void ApplyDeleteGo();

	sf::Vector2f ScreenToWorld(sf::Vector2i screenPos); //��ũ�� ��ǥ�� ���� ����������
	sf::Vector2i WorldToScreen(sf::Vector2f worldPos); //���� ��ǥ�� ��ũ�� ����������
	sf::Vector2f ScreenToUi(sf::Vector2i screenPos); //��ũ�� ��ǥ�� ���� ����������
	sf::Vector2i UiToScreen(sf::Vector2f worldPos);
};
