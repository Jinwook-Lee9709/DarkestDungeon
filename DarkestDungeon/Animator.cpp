#include "stdafx.h"
#include "Animator.h"

void Animator::Update(float dt)
{
	if (!isPlaying) {
		return;
	}
	accumTime += dt;
	if (accumTime < frameDuration)
		return;

	currentFrame++;
	accumTime = 0;
	
	if (currentFrame == totalFrame) {
		switch (currentClip->loopType) {
		case AnimationLoopTypes::Single:
			currentFrame = -1;
			isPlaying = false;
			return;
			break;
		case AnimationLoopTypes::Loop:
			currentFrame = 0;
			break;
		}
	}
	std::cout << currentClip->frames[currentFrame].texCoord.top << std::endl;
	SetRect(currentClip->frames[currentFrame]);
}

void Animator::Play(const std::string& clipId)
{
	Play(&GET_ANIM(clipId));
}

void Animator::Play(AnimationClip* clip)
{
	isPlaying = true;
	currentClip = clip;
	totalFrame = clip->frames.size();
	currentFrame = 0;

	frameDuration = 1.f / clip->fps;
	accumTime = 0.f;
	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::Stop()
{
	isPlaying = false;
}

void Animator::SetFrame(const AnimationFrame& frame)
{
	sprite->setTexture(GET_TEX(frame.texId));
	sprite->setTextureRect(frame.texCoord);
}

void Animator::SetRect(const AnimationFrame& frame)
{
	sprite->setTextureRect(frame.texCoord);
}