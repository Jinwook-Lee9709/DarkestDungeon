#pragma once

class SceneDev1;
class CharacterContainer;
class UiDungeon;
class SpriteGo;
class ShadowRect;

class ExploreManager : public GameObject
{
public:
	enum class Status
	{
		None,
		Start,
		Idle,
		EnterRoom,
	};
protected:
	SceneDev1* currentScene;

	UiDungeon* ui;
	std::vector<sf::View*> views;
	std::vector<CharacterContainer*>* characters;
	std::vector<int>* characterOrder;

	std::vector<sf::Vector2f>* characterContainerPos;
	std::vector<sf::Vector2f>* monsterContainerPos;
	
	std::vector<SpriteGo*> doors;
	std::pair<float, float> playableBounds;
	std::pair<float, float> cameraCenterBounds;
	std::pair<float, float> cameraThreshold;
	Status currentStatus;
	Status beforeStatus;

	ShadowRect* shadow;
	
	float sfxTimer = 0;
	float sfxDuration = 0.6f;

	SpriteGo* background;
	float cameraDistance;
	bool isMoving;
public:
	ExploreManager()= default;
	ExploreManager(SceneDev1* scene);
	~ExploreManager() = default;

	void StartExploreMode();

	void Init() override;
	void Release() override;
	void Reset(std::vector<CharacterContainer*>* characters, UiDungeon* ui, std::vector<int>* chracterOrder);
	void Update(float dt) override;
	void UpdateIdle(float dt);
	void UpdateEnterRoom(float dt);

	void Draw(sf::RenderWindow& window) override;

	void SetCorridorInfo();
	void SetCorridorBackground();
};

