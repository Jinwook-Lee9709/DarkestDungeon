#pragma once
#include "AnimationClip.h"

class Animator
{
protected:
	sf::Sprite* sprite;
	AnimationClip* currentClip;

	bool isPlaying;
	int currentFrame = 0;
	int totalFrame = 0;

	float frameDuration;
	float accumTime;
public:
	Animator() = default;
	~Animator() = default;

	void SetTarget(sf::Sprite* target) { sprite = target; }
	
	void Update(float dt);

	void Play(const std::string& clipId);
	void Play(AnimationClip* clip);

	void Stop();

	void SetFrame(const AnimationFrame& frame);
	void SetRect(const AnimationFrame& frame);

	const std::string& GetCurrentClipId() const
	{
		if (currentClip == nullptr)
			return "";
		return currentClip->id;
	}
};