#include "stdafx.h"
#include "SoundMgr.h"

void SoundMgr::Init(int totalChannels)
{
	for (int i = 0; i < totalChannels; ++i)
	{
		waiting.push_back(new sf::Sound());
	}
}

void SoundMgr::Release()
{
	for (auto sound : waiting)
	{
		delete sound;
	}
	waiting.clear();
	for (auto sound : playing)
	{
		delete sound;
	}
	playing.clear();
}

void SoundMgr::Update(float dt)
{
	auto it = playing.begin();
	if (bgmStoping)
	{
		float volume = Utils::Clamp(bgm.getVolume() - 50*dt, 0, 100);
		bgm.setVolume(volume);
		if (volume == 0)
		{
			bgm.stop();
		}
	}


	while (it != playing.end()) 
	{
		if ((*it)->getStatus() == sf::Sound::Stopped)
		{
			waiting.push_back(*it);
			it = playing.erase(it);
		}
		else {
			it++;
		}
	}
	if (InputManager::GetKeyDown(sf::Keyboard::Num6))
	{
		if (bgmVolume > 0)
		{
			bgmVolume -= 10;
			bgm.setVolume(bgmVolume);
		}

	}
	if (InputManager::GetKeyDown(sf::Keyboard::Num7))
	{
		if (bgmVolume < 100)
		{
			bgmVolume += 10;
			bgm.setVolume(bgmVolume);
		}
	}
	if (InputManager::GetKeyDown(sf::Keyboard::Num8))
	{
		if (sfxVolume > 0)
		{
			sfxVolume -= 10;
			for (auto& sound : playing)
			{
				sound->setVolume(sfxVolume);
			}

		}
	}
	if (InputManager::GetKeyDown(sf::Keyboard::Num9))
	{
		if (sfxVolume < 100)
		{
			sfxVolume += 10;
			for (auto& sound : playing)
			{
				sound->setVolume(sfxVolume);
			}
		}
	}

}

void SoundMgr::PlayBgm(std::string id, bool loop)
{
	PlayBgm(GET_SOUND(id), loop);
}

void SoundMgr::PlayBgm(sf::SoundBuffer& buffer, bool loop)
{
	bgmStoping = false;
	bgm.stop();
	bgm.setVolume(bgmVolume);
	bgm.setLoop(loop);
	bgm.setBuffer(buffer);
	bgm.play();
}

void SoundMgr::StopBgm()
{
	bgmStoping = true;
}

void SoundMgr::PlaySfx(std::string id, bool loop)
{

	PlaySfx(GET_SOUND(id), loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
	sf::Sound* sound = nullptr;

	if (waiting.empty())
	{
		sound = playing.front();
		playing.pop_front();
		sound->stop();
	}
	else {
		sound = waiting.front();
		waiting.pop_front();
	}
	sound->setVolume(sfxVolume);
	sound->setBuffer(buffer);
	sound->setLoop(loop);
	sound->play();
	playing.push_back(sound);
}



void SoundMgr::SetSfxVolume(float v)
{
	sfxVolume = v;
	for (auto sound : playing)
	{
		sound->setVolume(v);
	}
}

void SoundMgr::StopAllSfx()
{
	for (auto sound : playing)
	{
		sound->stop();
		waiting.push_back(sound);
	}
	playing.clear();
}
