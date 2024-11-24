#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SkillTooltip.h"

SceneDev2::SceneDev2()
	: Scene(SceneIds::Dev2)
{

}

void SceneDev2::Init()
{
	//RES_TABLE_MGR.LoadScene("Dev1");
	//worldView.setSize(FRAMEWORK.GetWindowSizeF());
	//worldView.setCenter(FRAMEWORK.GetWindowSizeF() * 0.5f);
	//CharacterInfo a;
	//a.skill1 = { "plague_doctor_ability_one", "0" };
	//a.skill2 = { "plague_doctor_ability_one", "0" };
	//a.skill3 = { "plague_doctor_ability_one", "0" };
	//a.skill4 = { "plague_doctor_ability_one", "0" };
	//ui = AddGo(new SkillTooltip());
	//ui->SetPosition({ 960.f, 540.f });
	//ui->Set(a,0, 1);
	Scene::Init();
}

void SceneDev2::Enter()
{
	std::cout << "SceneDev2:: Enter()" << std::endl;

	Scene::Enter();
}

void SceneDev2::Exit()
{
	std::cout << "SceneDev2:: Exit()" << std::endl;

	Scene::Exit();

}

void SceneDev2::Update(float dt)
{
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}