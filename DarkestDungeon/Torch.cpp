#include "stdafx.h"
#include "Torch.h"

Torch::Torch(const std::string& name)
	: GameObject(name)
{
}

void Torch::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sf::Vector2f windowsize = FRAMEWORK.GetWindowSizeF();
	torchSprite.setPosition(position - sf::Vector2f( 0.f, windowsize.y * 0.38f ));
	Utils::SetOrigin(torchSprite, Origins::MC);
	vignetteOverlay.SetPosition(FRAMEWORK.GetWindowSizeF() * 0.5f);
	vignetteOverlay.SetOrigin(Origins::MC);
}
void Torch::Init()
{

}
void Torch::Reset()
{
	animator.SetTarget(&torchSprite);
	torchLevel = 4;
	UpdateEffect();
	position = FRAMEWORK.GetWindowSizeF() * 0.5f;
	SetPosition(position);
}

void Torch::Update(float dt)
{
	animator.Update(dt);

	if (InputManager::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = (sf::Vector2f)InputManager::GetMousePosition();
		if (torchSprite.getGlobalBounds().contains(mousePos))
		{
			IncreaseLevel();
		}
	}
	if (InputManager::GetMouseButtonDown(sf::Mouse::Right))
	{
		sf::Vector2f mousePos = (sf::Vector2f)InputManager::GetMousePosition();
		if (torchSprite.getGlobalBounds().contains(mousePos))
		{
			DecreaseLevel();
		}
	}

}

void Torch::Draw(sf::RenderWindow& window)
{
	vignetteOverlay.Draw(window);
	window.draw(torchSprite);
}

void Torch::IncreaseLevel()
{
	if (torchLevel < 4)
	{
		torchLevel++;
		SOUND_MGR.PlaySfx("torch_add");
	}
	UpdateEffect();
}

void Torch::DecreaseLevel()
{
	if (torchLevel > 0)
	{
		torchLevel--;
		SOUND_MGR.PlaySfx("torch_end");
	}
	UpdateEffect();
}

void Torch::UpdateEffect()
{
	animator.Play("torch" + std::to_string(torchLevel));
	vignetteOverlay.ChangeTexture("overlay" + std::to_string(torchLevel));
}
