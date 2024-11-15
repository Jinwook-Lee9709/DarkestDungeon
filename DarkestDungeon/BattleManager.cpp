#include "stdafx.h"
#include "BattleManager.h"
#include "SceneDev1.h"
#include "CharacterContainer.h"
#include "MonsterContainer.h"
#include "UiDungeon.h"


BattleManager::BattleManager(SceneDev1* scene)
	:currenScene(scene)
{

}

void BattleManager::Init()
{
}

void BattleManager::Reset(std::vector<CharacterContainer*>* characters,
    std::vector<MonsterContainer*>* monsters, UiDungeon* ui)
{
    this->characters = characters;
    this->monsters = monsters;
    this->ui = ui;
}


void BattleManager::Update(float dt)
{
    switch (currentStatus)
    {
    case Status::JudgeTurn:
        UpdateJudgeTurn(dt);
        break;

    case Status::CharacterTurn:
        UpdateCharacterTurn(dt);
        break;

    case Status::SkillSelected:
        UpdateSkillSelected(dt);
        break;

    case Status::ItemSelected:
        UpdateItemSelected(dt);
        break;

    case Status::CharacterAnimate:
        UpdateCharacterAnimate(dt);
        break;

    case Status::MonsterTurn:
        UpdateMonsterTurn(dt);
        break;

    case Status::MonsterAnimate:
        UpdateMonsterAnimate(dt);
        break;

    default:
        break;
    }
}

void BattleManager::UpdateJudgeTurn(float dt)
{
    if (orderQueue.empty()) {
        std::priority_queue<std::pair< int, int >, std::vector<std::pair<int, int>>,Compare> sortingQueue;
        int index[8] = { -1 };//index for check Order by Pos
        int i = 0;
        for (auto& character : *characters)
        {
            if (character->IsAlive()) {
                CharacterInfo& info = character->GetCharacterInfo();
                int pos = character->GetPos();
                sortingQueue.push(std::pair<int, int>(info.speed, character->GetPos()));
                index[pos] = i;
            }
            i++;
        }
        int size = sortingQueue.size();
        for (int j = 0; j < size; j++) {
            std::pair<int, int> it = sortingQueue.top();
            sortingQueue.pop();
            orderQueue.push(index[it.second]);
        }
    }
    if (orderQueue.front() < 4 )
    {
        currentCharacter = orderQueue.front();
        ui->ChangeSkill((*characters)[currentCharacter]->GetCharacterInfo());
        orderQueue.pop();
        currentStatus = Status::CharacterTurn;
    }
    else
    {
        currentMonster = orderQueue.front()-4;
        orderQueue.pop();
        currentStatus = Status::MonsterTurn;
    }
 
}

void BattleManager::UpdateCharacterTurn(float dt)
{
    if (InputManager::GetKeyDown(sf::Keyboard::Num1))
    {
        (*characters)[currentCharacter]->UseSkill(*characters, *monsters, currentCharacter, 3, 2);
        currentStatus = Status::JudgeTurn;
    }
}

void BattleManager::UpdateSkillSelected(float dt)
{
}

void BattleManager::UpdateItemSelected(float dt)
{
}

void BattleManager::UpdateCharacterAnimate(float dt)
{
}

void BattleManager::UpdateMonsterTurn(float dt)
{
}

void BattleManager::UpdateMonsterAnimate(float dt)
{
}


