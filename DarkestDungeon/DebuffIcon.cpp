#include "stdafx.h"
#include "DebuffIcon.h"

DebuffIcon::DebuffIcon(const std::string& name)
	: GameObject(name)
{
	
}

void DebuffIcon::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sf::Vector2f positionBuf = position;
	for (auto& icon : icons)
	{
		icon->SetPosition(positionBuf);
		positionBuf.x += 20.f;
	}

}


void DebuffIcon::Init()
{
}

void DebuffIcon::Release()
{
	for (auto& icon : icons)
	{
		delete(icon);
	}
	icons.clear();
}

void DebuffIcon::Reset()
{
	for (int i = 0; i < 5; i++)
	{
		auto obj = new SpriteGo();
		obj->SetActive(false);
		icons.push_back(obj);
	}
}

void DebuffIcon::Update(float dt)
{
}

void DebuffIcon::Draw(sf::RenderWindow& window)
{
	for (auto& icon : icons)
	{
		if (icon->IsActive())
		{
			icon->Draw(window);
		}
	}
}

void DebuffIcon::Insert(const DebuffType& type)
{
	if (IsExist(type))
	{
		return;
	}
	std::string texId;
	switch (type)
	{
		case DebuffType::Stun:
		{
			texId = "tray_stun";
			break;
		}
		case DebuffType::Blight:
		{
			texId = "tray_poison";
			break;
		}
		case DebuffType::Bleed:
		{
			texId = "tray_bleed";
			break;
		}
	}
	for (auto& icon : icons)
	{
		if (!icon->IsActive())
		{
			icon->ChangeTexture(texId);
			icon->SetActive(true);
			return;
		}
	}


}

void DebuffIcon::Delete(const DebuffType& type)
{
	std::string texId;
	switch (type)
	{
		case DebuffType::Stun:
		{
			texId = "tray_stun";
			break;
		}
		case DebuffType::Blight:
		{
			texId = "tray_poison";
			break;
		}
		case DebuffType::Bleed:
		{
			texId = "tray_bleed";
			break;
		}
	}

	for (int i =0; i < icons.size();i ++)
	{
		if (texId == icons[i]->GetTexId())
		{
			icons[i]->SetActive(false);
		}
		if (i < icons.size() - 1)
		{
			if (!icons[i]->IsActive() && icons[i+1]->IsActive())
			{
				icons[i]->ChangeTexture(icons[i + 1]->GetTexId());
				icons[i + 1]->SetActive(false);
			}
		}
	}
}

bool DebuffIcon::IsExist(const DebuffType& type)
{
	std::string texId;
	switch (type)
	{
		case DebuffType::Stun:
		{
			texId = "tray_stun";
			break;
		}
		case DebuffType::Blight:
		{
			texId = "tray_poison";
			break;
		}
		case DebuffType::Bleed:
		{
			texId = "tray_bleed";
			break;
		}
	}


	for (auto& icon : icons)
	{
		if (texId == icon->GetTexId())
		{
			return true;
		}
	}
	return false;
}
