#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(const std::string& name)
	:name(name), originPreset(Origins::TL), origin(0.f, 0.f), scale(1.f, 1.f)
{
	
}

GameObject::~GameObject()
{
}

void GameObject::FlipX(bool flag)
{
	if (flag == false) {
		scale.x = abs(scale.x);
	}
	else {
		scale.x = -abs(scale.x);
	}
}

void GameObject::FlipY(bool flag)
{
}

void GameObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = { 0.f, 0.f };
}

void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Reset()
{
}



void GameObject::Update(float dt)
{
}

void GameObject::Draw(sf::RenderWindow& window)
{
}
