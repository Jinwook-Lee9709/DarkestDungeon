#include "stdafx.h"

std::list<int> InputManager::downKeys;
std::list<int> InputManager::heldKeys;
std::list<int> InputManager::upKeys;
sf::Vector2i InputManager::mousePosition;

std::unordered_map<Axis, AxisInfo> InputManager::axisInfoMap;

void InputManager::Init()
{
	AxisInfo infoH;
	infoH.axis = Axis::horizontal;
	infoH.SetKey(true, sf::Keyboard::D);
	infoH.SetKey(true, sf::Keyboard::Right);
	infoH.SetKey(false, sf::Keyboard::A);
	infoH.SetKey(false, sf::Keyboard::Left);
	axisInfoMap.insert({ Axis::horizontal, infoH });

	AxisInfo infoV;
	infoV.axis = Axis::vertical;
	infoV.SetKey(true, sf::Keyboard::S);
	infoV.SetKey(true, sf::Keyboard::Down);
	infoV.SetKey(false, sf::Keyboard::W);
	infoV.SetKey(false, sf::Keyboard::Up);
	axisInfoMap.insert({ Axis::vertical, infoV });
}

void InputManager::Clear()
{
	upKeys.clear();
	downKeys.clear();
}



bool InputManager::Contains(const std::list<int>& list, int code)
{
	return std::find(list.begin(), list.end(), code) != list.end();
}

void InputManager::Remove(std::list<int>& list, int code)
{
	list.remove(code);
}

void InputManager::UpdateEvent(const sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
	{
		int code = ev.key.code;
		if (!Contains(heldKeys, code))
		{
			heldKeys.push_back(code);
			downKeys.push_back(code);
		}
	}
	break;
	case sf::Event::KeyReleased:
	{
		int code = ev.key.code;
		Remove(heldKeys, code);
		upKeys.push_back(code);
	}
	break;
	case sf::Event::MouseButtonPressed:
	{
		int code = sf::Keyboard::KeyCount + ev.mouseButton.button;
		if (!Contains(heldKeys, code))
		{
			heldKeys.push_back(code);
			downKeys.push_back(code);
		}
	}
	break;
	case sf::Event::MouseButtonReleased:
	{
		int code = sf::Keyboard::KeyCount + ev.mouseButton.button;
		Remove(heldKeys, code);
		upKeys.push_back(code);
	}
	break;
	case sf::Event::MouseMoved:
		mousePosition.x = ev.mouseMove.x;
		mousePosition.y = ev.mouseMove.y;
		break;
	}
}

void InputManager::Update(float dt)
{
	for (auto& pair : axisInfoMap)
	{
		auto& axisInfo = pair.second;
		float raw = GetAxisRaw(axisInfo.axis);
		float dir = raw;
		if (dir == 0.f && axisInfo.value != 0.f)
		{
			dir = axisInfo.value > 0 ? -3.f : 3.f;
		}
		axisInfo.value += dir * axisInfo.sensi * dt;
		axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f);
		float stopThreshold = std::abs(dir * axisInfo.sensi * dt);
		if (raw == 0.f && std::abs(axisInfo.value) < stopThreshold)
		{
			axisInfo.value = 0.f;
		}
		;
	}

}


bool InputManager::GetKeyDown(sf::Keyboard::Key key)
{
	return Contains(downKeys, key);
}

bool InputManager::GetKey(sf::Keyboard::Key key)
{
	return Contains(downKeys, key) || Contains(heldKeys, key);
}

bool InputManager::GetKeyUp(sf::Keyboard::Key key)
{
	return Contains(upKeys, key);
}

bool InputManager::GetMouseButtonDown(sf::Mouse::Button button)
{
	return Contains(downKeys, sf::Keyboard::KeyCount + button);
}

bool InputManager::GetMouseButton(sf::Mouse::Button button)
{
	int code = sf::Keyboard::KeyCount + button;
	return Contains(downKeys, code) || Contains(heldKeys, code);
}

bool InputManager::GetMouseButtonUp(sf::Mouse::Button button)
{
	return Contains(upKeys, sf::Keyboard::KeyCount + button);
}

float InputManager::GetAxis(Axis axis)
{
	auto axisInfo = axisInfoMap.find(axis);
	if (axisInfo == axisInfoMap.end()) {
		return 0.f;
	}
	else {
		return axisInfo->second.value;
	}
}

float InputManager::GetAxisRaw(Axis axis)
{
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end()) {
		return 0.f;
	}
	auto& axisInfo = findIt->second;
	auto it = heldKeys.rbegin();
	while (it != heldKeys.rend()) {
		int code = *it;
		if (Contains(axisInfo.positive, code)) {
			return 1.f;
		}
		if (Contains(axisInfo.negative, code)) {
			return -1.f;
		}
		++it;
	}
	return 0.f;
}


