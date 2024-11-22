#pragma once
#include "Singleton.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class AnimationClip;

class ResourceTableManager :
    public Singleton<ResourceTableManager>
{
    friend class Singleton<ResourceTableManager>;
private:
	json PATH;
	json ANIMATION;
	std::unordered_map <std::string, std::string> resourceTable;
	std::string err = "";
public:
	void Init();
	bool LoadCharacterAnimation(const CharacterType& character);
	bool LoadMonsterAnimation();
	bool LoadEffectAnimation();
	bool LoadSkillIcon(const std::string& skillName);
	bool LoadPortrait(const std::string& portraitName);
	bool LoadScene(const std::string& scene);
	bool UnLoadScene(const std::string& scene);

	sf::Texture& GetTex(const std::string& texKey);
	sf::Font& GetFont(const std::string& fontKey);
	sf::SoundBuffer& GetSound(const std::string& soundKey);
	AnimationClip& GetAnim(const std::string& AnimId);
	AnimationClip& GetCharacterSkillAnim(const std::string& type, const int& AnimCode);
	AnimationClip& GetCharacterAnim(const std::string& type, const std::string& AnimCode);

	AnimationClip& GetMonsterSkillAnim(const std::string& type, const int& AnimCode);
	AnimationClip& GetMonsterAnim(const std::string& type, const std::string& AnimCode);

	std::string& GetPath(const std::string& key);

	json& GetAnimationList() { return ANIMATION; }
};

#define RES_TABLE_MGR (ResourceTableManager::Instance())
#define GET_TEX(X) (RES_TABLE_MGR.GetTex(X))
#define GET_FONT(X) (RES_TABLE_MGR.GetFont(X))
#define GET_SOUND(X) (RES_TABLE_MGR.GetSound(X))
#define GET_SHADER(X) (RES_TABLE_MGR.GetShader(X))
#define GET_ANIM(X) (RES_TABLE_MGR.GetAnim(X))
