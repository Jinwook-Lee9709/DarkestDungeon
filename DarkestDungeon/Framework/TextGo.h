#pragma once
#include "stdafx.h"

class TextGo : public GameObject
{
protected:
	sf::Text text;
	std::string font;
public:
	TextGo(const std::string& font, const std::string& str);
	~TextGo() = default;

	TextGo(const std::string& font);

	virtual void SetText(const std::string& str);
	virtual void SetFontSize(int size);
	virtual void ChangeFont(const std::string& str);
	virtual void SetOutline(int tickness, sf::Color color);
	virtual void SetColor(sf::Color color);

	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin);

	void Reset() override;
	void SetPosition(const sf::Vector2f& pos)override;
	void SetString(const std::string str);
	void SetStringByTable(const std::string str);
	void SetCharacterSize(int size);
	void Draw(sf::RenderWindow& window)override;



};

