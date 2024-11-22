#pragma once
#include <list>

enum class Axis {
	horizontal,
	vertical
};

struct AxisInfo {
	Axis axis;
	std::list<int> positive;
	std::list<int> negative;
	float sensi = 1.5f;
	float value;

	void SetKey(bool positive, int code)
	{
		if (positive) 
		{
			this->positive.push_back(code);
		}
		else {
			this->negative.push_back(code);
		}
	}
};



class InputManager
{
private:
	static std::list<int> downKeys;
	static std::list<int> heldKeys;
	static std::list<int> upKeys;

	static sf::Vector2i mousePosition;

	static std::unordered_map<Axis, AxisInfo> axisInfoMap;
public:


	static void Init();
	static void Clear();

	static void UpdateEvent(const sf::Event& ev);
	static void Update(float dt);

	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);

	static bool GetMouseButtonDown(sf::Mouse::Button button);
	static bool GetMouseButton(sf::Mouse::Button button);
	static bool GetMouseButtonUp(sf::Mouse::Button button);

	static sf::Vector2i GetMousePosition() { return mousePosition; }

	static float GetAxis(Axis axis);
	static float GetAxisRaw(Axis axis);
private:
	static bool Contains(const std::list<int>& list, int code);
	static void Remove(std::list<int>& list, int code);
};

