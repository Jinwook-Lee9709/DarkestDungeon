#pragma once

class DebuffIcon : public GameObject
{
protected:
	std::vector<SpriteGo*> icons;
public:
	DebuffIcon(const std::string& name = "");
	~DebuffIcon() = default;

	void SetPosition(const sf::Vector2f& pos) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Insert(const DebuffType& type);
	void Delete(const DebuffType& type);
	bool IsExist(const DebuffType& type);
};
