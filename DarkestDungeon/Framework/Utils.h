#pragma once
class Utils
{
private:
	static std::mt19937 generator;
	static const float PI;

public:

	static void Init();

	static int RandomRange(int min, int max);
	static float RandomRange(float min, float max);
	static float RandomValue(); //0.0f ~ 1.0f

	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();

	static float Clamp(float value, float min, float max);

	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins preset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Text& text, Origins preset);

};

