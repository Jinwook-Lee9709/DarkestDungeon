#pragma once
#include "stdafx.h"

class Framework: public Singleton<Framework>
{
	friend Singleton<Framework>;
private:
	Framework() = default;
	virtual ~Framework() = default;

	Framework(const Framework& other) = delete;
	Framework operator= (const Framework& other) = delete;

	sf::RenderWindow window;
	
	sf::Clock clock;
	float timeScale = 1.f;

	float time = 0.f;
	float deltaTime = 0.f;
	float realTime = 0.f;
	float realDeltaTime = 0.f;

	int frameRate = 60;
	float frameTimer = 0;
public:

	float GetTime()			 const { return time; }
	float GetdeltaTime()	 const { return deltaTime; }
	float GetRealTime()		 const { return realTime; }
	float GetRealDeltaTime() const { return realDeltaTime; }

	void SetTimeScale(float newTimeScale) { timeScale = newTimeScale; }
	float GetTimeScale() { return timeScale; }


	sf::Vector2u GetWindowSize() const { return window.getSize(); }
	sf::Vector2f GetWindowSizeF() const { return (sf::Vector2f)window.getSize(); }
	sf::FloatRect GetWindowBoudns() const
	{
		auto size = GetWindowSize();
		return sf::FloatRect(0.f, 0.f, size.x, size.y);
	}

	virtual void Init(int width, int height, const std::string& name);
	virtual void Do();
	virtual void Release();


};

#define FRAMEWORK (Framework::Instance())