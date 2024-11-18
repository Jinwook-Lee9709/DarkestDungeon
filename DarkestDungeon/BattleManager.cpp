#include "stdafx.h"
#include "BattleManager.h"
#include "SceneDev1.h"
#include "CharacterContainer.h"
#include "MonsterContainer.h"
#include "UiDungeon.h"


BattleManager::BattleManager(SceneDev1* scene)
	:currentScene(scene)
{

}

void BattleManager::Init()
{
    std::ifstream file("tables/monster_table.json", std::ios::in);
    if (!file) {
        std::cerr << "Failed to Read File";
    }
    monsterTable = json::parse(file);
}

void BattleManager::Reset(std::vector<CharacterContainer*>* characters,
    std::vector<MonsterContainer*>* monsters, UiDungeon* ui, std::vector<int>* chracterOrder)
{
    beforeStatus = Status::None;
    currentStatus = Status::JudgeTurn;
    this->characters = characters;
    this->monsters = monsters;
    this->ui = ui;
    this->chracterOrder = chracterOrder;
    SetMonsterInfo();
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

void BattleManager::SetMonsterInfo()
{
    monsterOrder.clear();
    for (int i = 0; i < 4; i++) {
        (*monsters)[i]->SetPosition(currentScene->GetMonsterPos()[i]);
        (*monsters)[i]->ChangePos(i + 4);
        monsterOrder.push_back(i);
        json info = monsterTable["0"]["Monster" + std::to_string(i + 1)];
        (*monsters)[i]->SetStatus(info);
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
        for (auto& montser : *monsters)
        {
            if (montser->IsAlive()) {
                MonsterInfo& info = montser->GetMonsterInfo();
                int pos = montser->GetPos();
                sortingQueue.push(std::pair<int, int>(info.speed, montser->GetPos()));
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
        beforeStatus = Status::JudgeTurn;
        currentStatus = Status::CharacterTurn;
    }
    else
    {
        currentMonster = orderQueue.front()-4;
        orderQueue.pop();
        beforeStatus = Status::JudgeTurn;
        currentStatus = Status::MonsterTurn;
    }
  
}

void BattleManager::UpdateCharacterTurn(float dt)
{
    if (beforeStatus == Status::JudgeTurn){
        std::vector<int> skills = (*characters)[currentCharacter]->CheckAvailableSkill();
        if (!skills.empty()) {
            bool availabe[4] = { false };
            std::vector<bool> vec;
            for (auto skill : skills)
            {
                std::vector<short> range = (*characters)[currentCharacter]->GetSkillRange(skill);
                for (int i = 1; i < 5; i++)
                {
                    if (range[0] == 0) 
                    {
                        if (range[i] == 1 && (*characters)[(*chracterOrder)[i-1]]->IsAlive())
                        {
                            availabe[skill] = true;
                        }
                    }
                    if (range[0] == 1 || range[0] == 3)
                    {
                      
                        if (range[i+4] == 1 && (*monsters)[(monsterOrder)[i-1]]->IsAlive())
                        {
                            availabe[skill] = true;
                        }
                        

                    }
                    
                }
            }
            for (int i = 0; i < 4; i++) {
                vec.push_back(availabe[i]);
            }
            ui->ChangeSkillActive(vec);
            beforeStatus = Status::None;
        }
        else {
            std::vector<bool> vec(4, false);
            ui->ChangeSkillActive(vec);
            beforeStatus = Status::None;
        }
       

    }
    if (ui->CheckSkillClick() != 0) {
        selectedSkill = ui->CheckSkillClick();
        beforeStatus = Status::CharacterTurn;
        currentStatus = Status::SkillSelected;
    };


    if (InputManager::GetKeyDown(sf::Keyboard::Num1))
    {
        (*characters)[currentCharacter]->UseSkill(*characters, *monsters, currentCharacter, 0, 2);
        currentStatus = Status::JudgeTurn;
    }
}

void BattleManager::UpdateSkillSelected(float dt)
{
    if (beforeStatus == Status::CharacterTurn || beforeStatus == Status::SkillSelected) {
        ResetTargetUi();
        ChangeTargetUi();
        beforeStatus = Status::None;
    }
    if (ui->CheckSkillClick() != 0) {
        selectedSkill = ui->CheckSkillClick();
        beforeStatus = Status::SkillSelected;
        return;
    };
    if (InputManager::GetMouseButtonDown(sf::Mouse::Left))
    {
        if(selectedSkill < 5 && selectedSkill > 0)
        {
            std::vector<short> range = (*characters)[currentCharacter]->GetSkillRange(selectedSkill - 1);
            if (range[0] == 1 || range[0] == 3) {
                for (int i = 5; i < 9; i++)
                {
                    if ((*monsters)[monsterOrder[i - 5]]->IsClicked() && range[i] == 1)
                    {
                        (*characters)[currentCharacter]->UseSkill(*characters, *monsters, currentCharacter, monsterOrder[i - 5], selectedSkill);
                        ResetTargetUi();
                        ui->DeactivateSelectBox();
                        currentStatus = Status::JudgeTurn;
                        return;
                    }
                }
            }
            if (range[0] == 0 || range[0] == 2) {
                for (int i = 0; i < 4; i++)
                {
                    if ((*characters)[(*chracterOrder)[i]]->IsClicked() && range[i + 5] == 1)
                    {
                        (*characters)[currentCharacter]->UseSkill(*characters, *monsters, currentCharacter, (*chracterOrder)[i], selectedSkill);
                        ResetTargetUi();
                        ui->DeactivateSelectBox();
                        currentStatus = Status::JudgeTurn;
                        return;
                    }
                }
            }
        }
        else if (selectedSkill == 5) 
        {
            for (int i = 0; i < 4; i++)
            {
                CharacterContainer* character = (*characters)[i];
                if (character->IsClicked() && character->IsAlive() && i != currentCharacter)
                {
                    currentScene->ChangeCharacterPos(currentCharacter, i);
                    ResetTargetUi();
                    ui->DeactivateSelectBox();
                    currentStatus = Status::JudgeTurn;
                    return;
                }
            }
        }

       ResetTargetUi();
       ui->DeactivateSelectBox();
       beforeStatus = Status::SkillSelected;
       currentStatus = Status::CharacterTurn;
    }
}

void BattleManager::UpdateItemSelected(float dt)
{
}

void BattleManager::UpdateCharacterAnimate(float dt)
{
}

void BattleManager::UpdateMonsterTurn(float dt)
{
    std::vector<int> skills = (*monsters)[currentMonster]->CheckAvailableSkill();
    if (!skills.empty()) {
        std::map<int, std::vector<int>> targetMap;
        for (auto skill : skills)
        {
            std::vector<int> targetList;
            std::vector<short> range = (*monsters)[currentMonster]->GetSkillRange(skill);
            for (int i = 5; i < 9; i++)
            {

                if (range[i] == 1 && (*characters)[(*chracterOrder)[i - 5]]->IsAlive()) {
                    targetList.push_back(i - 5);
                }
            }
            targetMap.insert({ skill, targetList });
        }
        if (!targetMap.empty()) {
            int selectedSkill = Utils::RandomRange(0, targetMap.size() - 1);
            auto targetInfo = targetMap.begin();
            for (int i = 0; i < selectedSkill; i++) { targetInfo++; }
            int target = Utils::RandomRange(0, targetInfo->second.size());
            
            (*monsters)[currentMonster]->UseSkill(*characters, *monsters, monsterOrder[target], (*chracterOrder)[target], targetInfo->first + 1);
            
        }
    }
    currentStatus = Status::JudgeTurn;

}

void BattleManager::UpdateMonsterAnimate(float dt)
{
}

void BattleManager::ResetTargetUi()
{
    for (int i = 0; i < 4; i++)
    {
        (*characters)[i]->DeactiavteTargetUi();
        (*monsters)[i]->DeactiavteTargetUi();
    }
}

void BattleManager::ChangeTargetUi()
{
    if (selectedSkill < 5) {
        std::vector<short> range = (*characters)[currentCharacter]->GetSkillRange(selectedSkill - 1);
        if (range[0] == 1 || range[0] == 3) {
            for (int i = 0; i < 4; i++)
            {
                if ((*monsters)[monsterOrder[i]]->IsAlive() && range[i + 5] == 1)
                {
                    (*monsters)[monsterOrder[i]]->ActiavteTargetUi(TargetUi::ENEMY);
                }
            }
        }
        if (range[0] == 0 || range[0] == 2) {
            for (int i = 0; i < 4; i++)
            {
                if ((*characters)[(*chracterOrder)[i]]->IsAlive() && range[i + 5] == 1)
                {
                    (*characters)[(*chracterOrder)[i]]->ActiavteTargetUi(TargetUi::HEAL);
                }
            }
        }
    }
    else if (selectedSkill == 5)
    {
       
        for (int i = 0; i < 4; i++)
        {
            std::cout << currentCharacter;
            if ((*characters)[i]->IsAlive() && i != currentCharacter)
            {
                (*characters)[i]->ActiavteTargetUi(TargetUi::CHANGEPOS);
            }
        }
    }
  
}


