#pragma once
class SpriteGo;
class TextGo;

enum class PlayerTextIndex {
	ACCURACY,
	CRITICAL,
	DAMAGE,
	DODGE,
	PROTECT,
	SPEED,
	HP,
	STRESS,
	COUNT
};

class UiDungeon : public GameObject
{
private:
	bool instanceChk = false;

	std::vector<SpriteGo*> fixedUi;
	std::vector<TextGo*> fixedText;

	SpriteGo* skill[7];
	std::string SkillTexId[4][4];

	std::unordered_map<PlayerTextIndex, TextGo*> playerText;

	SpriteGo* inventory;


	sf::Vector2f windowSize;
public:
	UiDungeon(const std::string& name = "");
	~UiDungeon() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetSpriteInfo(SpriteGo* obj, const Origins& origin,
		const sf::Vector2f pos, const int& order,
		const bool& flipX = false, const bool& flipY = false);




	void InitFixedUi(const sf::Vector2f& windowSize);
	void InitSkillUi(const sf::Vector2f& windowSize);
	void InitPlayerTextUi(const sf::Vector2f& windowSize);

	void CheckSkillClick();
};
