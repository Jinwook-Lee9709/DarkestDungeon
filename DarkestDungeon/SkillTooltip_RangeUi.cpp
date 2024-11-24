#include "stdafx.h"
#include "SkillTooltip_RangeUi.h"

SkillTooltip_RangeUi::SkillTooltip_RangeUi(const std::string& name)
	: GameObject(name)
{
	for (int i = 0; i < 8; i++)
	{
		sf::CircleShape obj;
		obj.setRadius(4);
		Utils::SetOrigin(obj, Origins::MC);
		circles.push_back(obj);
	}
	for (int i = 0; i < 3; i++)
	{
		sf::RectangleShape obj;
		obj.setSize({ 17.f, 2.f });
		Utils::SetOrigin(obj, Origins::MC);
		bars.push_back(obj);
	}
}

void SkillTooltip_RangeUi::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void SkillTooltip_RangeUi::Draw(sf::RenderWindow& window)
{
	for (auto& circle : circles)
	{
		window.draw(circle);
	}
	for (auto& bar : bars)
	{
		window.draw(bar);
	}
}

void SkillTooltip_RangeUi::Set(std::vector<short> range)
{
	for (auto& circle : circles)
	{
		circle.setFillColor(sf::Color::Transparent);
	}
	for (auto& bar : bars)
	{
		bar.setFillColor(sf::Color::Transparent);
	}
	if (range[0] == 1 || range[0] == 3)
	{
		for (int i = 0; i < 4; i++)
		{
			if (range[i + 1] == 1)
			{
				circles[i].setFillColor(sf::Color(161, 153, 94, 255));
			}
			else
			{
				circles[i].setFillColor(sf::Color(50, 48, 47, 255));
			}
			
			sf::Vector2f newPos = position;
			newPos += {(i * 14.f) - 55.f, 0.f};
			circles[i].setPosition(newPos);

		}
		for (int i = 4; i < 8; i++)
		{
			if (range[i + 1] == 1)
			{
				circles[i].setFillColor(sf::Color(139, 21, 3, 255));
			}
			else
			{
				circles[i].setFillColor(sf::Color(50, 48, 47, 255));
			}
			sf::Vector2f newPos = position;
			newPos += {13.f + ((i - 4) * 14.f), 0.f};
			circles[i].setPosition(newPos);

			if (range[0] == 3 && (i - 4) > 0 && (range[i] == 1) && (range[i + 1] == 1))
			{
				sf::Vector2f newPos = ((circles[i - 1].getPosition() + circles[i].getPosition()) / 2.f);

				bars[i - 5].setFillColor(sf::Color(139, 21, 3, 255));
				bars[i - 5].setPosition(newPos);
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (range[i + 5] == 1)
			{
				circles[i].setFillColor(sf::Color(161, 153, 94, 255));
			}
			else
			{
				circles[i].setFillColor(sf::Color(50, 48, 47, 255));
			}
			sf::Vector2f newPos = position;
			newPos += {(i * 14.f) - 21.f, 0.f};
			circles[i].setPosition(newPos);

			if (range[0] == 2 && i > 0 && (range[i + 4] == 1) && (range[i + 5] == 1))
			{
				sf::Vector2f newPos = ((circles[i - 1].getPosition() + circles[i].getPosition()) / 2.f);

				bars[i - 1].setFillColor(sf::Color(161, 153, 94, 255));
				bars[i - 1].setPosition(newPos);
			}
		}

	}
}
