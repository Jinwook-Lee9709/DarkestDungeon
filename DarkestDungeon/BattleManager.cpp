#include "stdafx.h"
#include "BattleManager.h"
#include "SceneDev1.h"
#include "CharacterContainer.h"
#include "MonsterContainer.h"
#include "UiDungeon.h"
#include "ShadowRect.h"


BattleManager::BattleManager(SceneDev1* scene)
	:currentScene(scene)
{
    views = currentScene->GetViews();
}

void BattleManager::Init()
{
    std::ifstream file("tables/monster_table.json", std::ios::in);
    if (!file) {
        std::cerr << "Failed to Read File";
    }
    monsterTable = json::parse(file);
    //calculate coord for attack animation
    sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
    sf::Vector2f zoomedsize = 0.8f * FRAMEWORK.GetWindowSizeF();
    sf::Vector2f block1 = { zoomedsize.x / 5 , size.y * 0.62f };
    sf::Vector2f block2 = { zoomedsize.x / 10 , size.y * 0.62f };
    for (int i = 0; i < 4; i++)
    {
        sf::Vector2f coord = { size.x * 9 / 10 - (i+1) * block1.x, block1.y };
        zoomedChracterPos.push_back(coord);
    }
    for (int i = 0; i < 4; i++)
    {
        sf::Vector2f coord = { size.x / 2 - (i + 1) * block2.x, block2.y };
        zoomedContainerPos.push_back(coord);
    }
    for (int i = 0; i < 4; i++)
    {
        sf::Vector2f coord = { size.x / 2 + (i + 1) * block2.x, block2.y };
        zoomedContainerPos.push_back(coord);
    }
   

}

void BattleManager::Reset(std::vector<CharacterContainer*>* characters,
    std::vector<MonsterContainer*>* monsters, UiDungeon* ui, std::vector<int>* chracterOrder)
{
    beforeStatus = Status::None;
    currentStatus = Status::JudgeTurn;
    this->characters = characters;
    this->monsters = monsters;
    this->ui = ui;
    this->characterOrder = chracterOrder;
    SetMonsterInfo();
    shadow = dynamic_cast<ShadowRect*>(currentScene->FindGo("shadow"));
}


void BattleManager::Update(float dt)
{
    switch (currentStatus)
    {
    case Status::JudgeTurn:
        UpdateJudgeTurn(dt);
        break;
    case Status::ApplyDebuff:
        UpdateApplyDebuff(dt);
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
    case Status::FillEmptyPos:
        UpdateFillEmptyPos(dt);
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
    beforeStatus = Status::None;
    ui->ChangeSkillButtonTexture((*characters)[currentCharacter]->GetCharacterInfo());
    ui->ChangeCharacterInfoText((*characters)[currentCharacter]->GetCharacterInfo());
    ui->DeactivateAllSkillButton();
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
        if ((*characters)[currentCharacter]->IsAlive())
        {
            ui->ChangeSkillButtonTexture((*characters)[currentCharacter]->GetCharacterInfo());
            ui->ChangeCharacterInfoText((*characters)[currentCharacter]->GetCharacterInfo());
            orderQueue.pop();
            beforeStatus = Status::JudgeTurn;
            currentStatus = Status::ApplyDebuff;
            isCharacterTurn = true;
        }
        else
        {
            orderQueue.pop();
        }
      
    }
    else
    {
        currentMonster = orderQueue.front()-4;
        if ((*monsters)[currentMonster]->IsAlive())
        {
            orderQueue.pop();
            beforeStatus = Status::JudgeTurn;
            currentStatus = Status::ApplyDebuff;
            isCharacterTurn = false;
        }
        else
        {
            orderQueue.pop();
        }

    }
  
}

void BattleManager::UpdateApplyDebuff(float dt)
{
    if (beforeStatus == Status::JudgeTurn)
    {
        isStuned = false;
        timer = 0;
        duration = 0;
        if (isCharacterTurn)
        {
            int count;
            if (count = (*characters)[currentCharacter]->CheckDebuffCount() > 0)
            {
               
                duration = 1.f * count;
                (*characters)[currentCharacter]->ApplyDebuff();
                if ((*characters)[currentCharacter]->IsStuned()) {
                    (*characters)[currentCharacter]->EndStun();
                    isStuned = true;
                }
                else {
                    isStuned = false;
                }
            }

        }
        else 
        {
            int count;
            if (count = (*monsters)[currentMonster]->CheckDebuffCount() > 0)
            {
                timer = 0;
                duration = 1.f * count;
                (*monsters)[currentMonster]->ApplyDebuff();
                if ((*monsters)[currentMonster]->IsStuned()) {
                    (*monsters)[currentMonster]->EndStun();
                    isStuned = true;
                }
                else {
                    isStuned = false;
                }
            }
        }
        beforeStatus = Status::None;
    }

    timer += dt;
    if (timer > duration)
    {
        if (isStuned)
        {
            beforeStatus = Status::ApplyDebuff;
            currentStatus = Status::JudgeTurn;
        }
        else
        {
            if (isCharacterTurn) {
                beforeStatus = Status::ApplyDebuff;
                currentStatus = Status::CharacterTurn;
            }
            else {
                beforeStatus = Status::ApplyDebuff;
                currentStatus = Status::MonsterTurn;
            }
           
        }
    }
    
}

void BattleManager::UpdateCharacterTurn(float dt)
{
    UpdateMonsterPanel();
    if (beforeStatus == Status::ApplyDebuff){
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
                        if (range[i] == 1 && (*characters)[(*characterOrder)[i-1]]->IsAlive())
                        {
                            availabe[skill] = true;
                        }
                    }
                    if (range[0] == 2)
                    {
                        if (range[i] == 1 && (*characters)[(*characterOrder)[i - 1]]->IsAlive())
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
            ui->ChangeSkillButtonActive(vec);
            beforeStatus = Status::None;
        }
        else {
            std::vector<bool> vec(4, false);
            ui->ChangeSkillButtonActive(vec);
            beforeStatus = Status::None;
        }
        (*characters)[currentCharacter]->ActiavteTargetUi(TargetUi::SELECT);
    }
    if (ui->CheckSkillClick() != 0) {
        selectedSkill = ui->CheckSkillClick();
        beforeStatus = Status::CharacterTurn;
        currentStatus = Status::SkillSelected;
    };


    //if (InputManager::GetKeyDown(sf::Keyboard::Num1))
    //{
    //    (*characters)[currentCharacter]->UseSkill(*characters, *monsters, currentCharacter, 0, 2);
    //    currentStatus = Status::JudgeTurn;
    //}

    //if (InputManager::GetKeyDown(sf::Keyboard::Num2))
    //{
    //    ChangeMonsterPos(1, 2);
    //}
}

void BattleManager::UpdateSkillSelected(float dt)
{
    UpdateMonsterPanel();
    if (beforeStatus == Status::CharacterTurn || beforeStatus == Status::SkillSelected) {
        ResetTargetUi();
        ChangeTargetUi();
        (*characters)[currentCharacter]->ActiavteTargetUi(TargetUi::SELECT);
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
                    if ((*monsters)[monsterOrder[i - 5]]->IsClicked(currentScene->ScreenToWorld(InputManager::GetMousePosition())) 
                        && range[i] == 1)
                    {
                        (*characters)[currentCharacter]->UseSkill(*characters, *monsters, currentCharacter, monsterOrder[i - 5], selectedSkill);
                        characterTargetInfo = monsterOrder[i - 5];
                        ResetTargetUi();
                        ui->DeactivateSelectBox();       
                        ui->HideMonsterInfoPanel();
                        beforeStatus = Status::SkillSelected;
                        currentStatus = Status::CharacterAnimate;
                        return;
                    }
                }
            }
            if (range[0] == 0 || range[0] == 2) {
                for (int i = 0; i < 4; i++)
                {
                    if ((*characters)[(*characterOrder)[i]]->IsClicked(currentScene->ScreenToWorld(InputManager::GetMousePosition())) && range[i + 5] == 1)
                    {
                        (*characters)[currentCharacter]->UseSkill(*characters, *monsters, currentCharacter, (*characterOrder)[i], selectedSkill);
                        characterTargetInfo = (*characterOrder)[i];
                        ResetTargetUi();
                        ui->DeactivateSelectBox();
                        ui->HideMonsterInfoPanel();
                        beforeStatus = Status::SkillSelected;
                        currentStatus = Status::CharacterAnimate;
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
                if (character->IsClicked(currentScene->ScreenToWorld(InputManager::GetMousePosition())) && character->IsAlive() && i != currentCharacter)
                {
                    currentScene->ChangeCharacterPos(currentCharacter, i);
                    ResetTargetUi();
                    ui->DeactivateSelectBox();
                    ui->HideMonsterInfoPanel();
                    beforeStatus = Status::SkillSelected;
                    currentStatus = Status::CharacterAnimate;
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

    if (beforeStatus == Status::SkillSelected)
    {
        timer = 0;
        duration = 2.f;
        beforeStatus = Status::None;
        ui->DeactivateAllSkillButton();
        if (selectedSkill != 5)
        {
            AnimateView(true);
        }
    }
    if (selectedSkill != 5)
    {
        if (timer < 0.2f)
        {
            float sub = 2 * dt;
            elapsedZoom += 2 * dt;
            if (elapsedZoom > 0.4f)
            {
                sub -= elapsedZoom - 0.4f;
            }
            views[1]->zoom(1 - sub);
            zoomSnapshot.push(1 - sub);
            sf::Vector2f randomCoord = Utils::RandomOnUnitCircle();
            sf::Vector2f multiplyCoord = { randomCoord.x * 10 , randomCoord.y * 10 };
            views[1]->setCenter(views[2]->getCenter() + multiplyCoord);
        }
            views[1]->move({ -30 * dt,0.f });
    }
    timer += dt;
    if (timer > 1.8f && !moveCamera)
    {
        for (auto& character : (*characters))
        {
            character->MoveToCoord(currentScene->GetCharacterPos()[character->GetPos()]);
            character->sortingLayer = SortingLayers::Foreground;
        }
        for (auto& monster : (*monsters))
        {
            monster->MoveToCoord(currentScene->GetMonsterPos()[monster->GetPos() - 4]);
            monster->sortingLayer = SortingLayers::Foreground;
        }
        shadow->SetToInvisible();
        moveCamera = true;
    }
    if (timer > 1.8f)
    {
        if (!zoomSnapshot.empty())
        {
            views[1]->zoom(1 / zoomSnapshot.front());
            zoomSnapshot.pop();
        }
    }
    if (timer > duration) {
        timer = 0;
        (*characters)[currentCharacter]->SetToIdle();
        for (auto& monster : (*monsters))
        {
            monster->SetToIdle();
        }
        beforeStatus == Status::CharacterAnimate;
        currentStatus = Status::FillEmptyPos;
        if (selectedSkill != 5)
        {
            ResetView();
        }
    }
}

void BattleManager::UpdateMonsterTurn(float dt)
{
    if (!monsterSkillSelected)
    {
        std::vector<int> skills = (*monsters)[currentMonster]->CheckAvailableSkill();
        if (!skills.empty()) 
        {
            std::map<int, std::vector<int>> targetMap;
            for (auto skill : skills)
            {
                std::vector<int> targetList;
                std::vector<short> range = (*monsters)[currentMonster]->GetSkillRange(skill);
                for (int i = 0; i < 4; i++)
                {

                    if (range[8 - i] == 1 && (*characters)[(*characterOrder)[i]]->IsAlive()) 
                    {
                        targetList.push_back(i);
                    }
                }
                targetMap.insert({ skill, targetList });
            }
            if (!targetMap.empty()) 
            {
                int selectedSkill = Utils::RandomRange(0, targetMap.size() - 1);
                auto targetInfo = targetMap.begin();
                for (int i = 0; i < selectedSkill; i++) { targetInfo++; }
                int target = Utils::RandomRange(0, targetInfo->second.size());

                monsterTargetInfo.clear();
                monsterTargetInfo.push_back(monsterOrder[currentMonster]);
                monsterTargetInfo.push_back((*characterOrder)[target]);
                monsterTargetInfo.push_back(targetInfo->first + 1);
                monsterSkillSelected = true;
                /*(*monsters)[currentMonster]->UseSkill(*characters, *monsters, monsterOrder[currentMonster], (*chracterOrder)[target], targetInfo->first + 1);*/
            }
        }
    }
    else 
    {
        if (!animationPlaying)
        {
            json j = (*monsters)[currentMonster]->GetMonsterInfo();
            std::string str = "skill" + std::to_string(monsterTargetInfo[2]);
            std::vector<std::string> str2 = j[str];
            std::string skillName = STRING_TABLE->Get(str2[0]);
            if ((*monsters)[currentMonster]->GetSkillRange(monsterTargetInfo[2] - 1)[0] == 1) {
                (*characters)[monsterTargetInfo[1]]->ActiavteTargetUi(TargetUi::ENEMY);
            }
            else {

            }
            ui->PlaySkillNameFrame(skillName);
            timer = 0;
            duration = 2.f;
            animationPlaying = true;
        }
        else {
            timer += dt;
            if (timer > duration)
            {
                timer = 0;
                monsterSkillSelected = false;
                animationPlaying = false;
                ui->DeactivateSkillNameFrame();
                beforeStatus = Status::MonsterTurn;
                currentStatus = Status::MonsterAnimate;

            }
        }
        
    }
   


}


void BattleManager::UpdateMonsterAnimate(float dt)
{

    if (beforeStatus == Status::MonsterTurn)
    {
        ResetTargetUi();
        (*monsters)[currentMonster]->UseSkill(*characters, *monsters,
            monsterTargetInfo[0], monsterTargetInfo[1], monsterTargetInfo[2]);
        beforeStatus = Status::None;
        timer = 0;
        duration = 2.f;
        AnimateView(false);
    }
    if (timer < 0.2f)
    {
        float sub = 2 * dt;
        elapsedZoom += 2 * dt;
        if (elapsedZoom > 0.4f)
        {
            sub -= elapsedZoom - 0.4f;
        }
        views[1]->zoom(1 - sub);
        zoomSnapshot.push(1 - sub);

        sf::Vector2f randomCoord = Utils::RandomOnUnitCircle();
        sf::Vector2f multiplyCoord = { randomCoord.x * 10 , randomCoord.y * 10 };
        views[1]->setCenter(views[2]->getCenter() + multiplyCoord);
    }
    views[1]->move({ 30 * dt, 0.f });
    if (timer > 1.8f && !moveCamera)
    {
        for (auto& character : (*characters))
        {
            character->MoveToCoord(currentScene->GetCharacterPos()[character->GetPos()]);
            character->sortingLayer = SortingLayers::Foreground;
        }
        for (auto& monster : (*monsters))
        {
            monster->MoveToCoord(currentScene->GetMonsterPos()[monster->GetPos() - 4]);
            monster->sortingLayer = SortingLayers::Foreground;
        }
        shadow->SetToInvisible();
        moveCamera = true;
    }
    if (timer > 1.8f)
    {
        if (!zoomSnapshot.empty())
        {
            views[1]->zoom(1 / zoomSnapshot.front());
            zoomSnapshot.pop();
        }
    }
    timer += dt;
    if (timer > duration)
    {
        timer = 0;
        (*monsters)[currentMonster]->SetToIdle();
        for (auto& character : (*characters))
        {
            character->SetToIdle();
        }
        currentStatus = Status::FillEmptyPos;
        ResetView();
    }
   
}

void BattleManager::UpdateFillEmptyPos(float dt)
{
    bool flag = false;
    do {
        flag = false;
        for (int i = 0; i < 3; i++)
        {
            if (!(*characters)[(*characterOrder)[i]]->IsAlive() && (*characters)[(*characterOrder)[i + 1]]->IsAlive())
            {
                currentScene->ChangeCharacterPos(i, i + 1);
                flag = true;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            if (!(*monsters)[monsterOrder[i]]->IsAlive() && (*monsters)[monsterOrder[i + 1]]->IsAlive())
            {
                ChangeMonsterPos(monsterOrder[i], monsterOrder[i + 1]);
                flag = true;
            }
        }
    } while (flag);

    currentStatus = Status::JudgeTurn;
}

void BattleManager::UpdateMonsterPanel()
{
    bool flag = false;
    int i = 0;
    for (auto*& monster : (*monsters))
    {
        if (flag = monster->IsHover(currentScene->ScreenToWorld(InputManager::GetMousePosition()))
            && monster->IsActive())
        {
            break;
        }
        i++;
    }
    if (ui->IsInfoPanelActive() && !flag)
    {
        ui->HideMonsterInfoPanel();
    }
    else if (!ui->IsInfoPanelActive() && flag && (*monsters)[i]->IsAlive())
    {
        ui->ShowMonsterInfoPanel((*monsters)[i]->GetMonsterInfo());
    }
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
                if ((*characters)[(*characterOrder)[i]]->IsAlive() && range[i + 5] == 1)
                {
                    (*characters)[(*characterOrder)[i]]->ActiavteTargetUi(TargetUi::HEAL);
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

void BattleManager::ChangeMonsterPos(int first, int second)
{
    auto monsterPos = currentScene->GetMonsterPos();
    int firstPos = (*monsters)[first]->GetPos();
    int secondPos = (*monsters)[second]->GetPos();
    sf::Vector2f firstCoord = monsterPos[firstPos - 4];
    sf::Vector2f secondCoord = monsterPos[secondPos - 4];
    (*monsters)[first]->ChangePos(secondPos);
    (*monsters)[second]->ChangePos(firstPos);
    (*monsters)[first]->MoveToCoord(secondCoord);
    (*monsters)[second]->MoveToCoord(firstCoord);
    monsterOrder[firstPos - 4] = second;
    monsterOrder[secondPos - 4] = first;
}

void BattleManager::AnimateView(bool isCharacter)
{
    if (isCharacter)
    {
        std::vector<short> range = (*characters)[currentCharacter]->GetSkillRange(selectedSkill - 1);
        if (range[0] == 0) {
            if ((*characters)[currentCharacter]->GetPos() > (*characters)[characterTargetInfo]->GetPos())
            {
                (*characters)[characterTargetInfo]->MoveToCoordDouble(zoomedChracterPos[1]);
                (*characters)[characterTargetInfo]->sortingLayer = SortingLayers::Popup;
                (*characters)[currentCharacter]->MoveToCoordDouble(zoomedChracterPos[2]);
                (*characters)[currentCharacter]->sortingLayer = SortingLayers::Popup;
            }
            else
            {
                (*characters)[characterTargetInfo]->MoveToCoordDouble(zoomedChracterPos[2]);
                (*characters)[characterTargetInfo]->sortingLayer = SortingLayers::Popup;
                (*characters)[currentCharacter]->MoveToCoordDouble(zoomedChracterPos[1]);
                (*characters)[currentCharacter]->sortingLayer = SortingLayers::Popup;
            }
        }
        if (range[0] == 1) {
            (*characters)[currentCharacter]->MoveToCoordDouble(zoomedContainerPos[0]);
            (*characters)[currentCharacter]->sortingLayer = SortingLayers::Popup;
            (*monsters)[characterTargetInfo]->MoveToCoordDouble(zoomedContainerPos[4]);
            (*monsters)[characterTargetInfo]->sortingLayer = SortingLayers::Popup;
        }
        if (range[0] == 2) {
            int j = 0;
            for (int i = 0; i < 4; i++)
            {
                if (range[5 + i] == 1 && (*characters)[(*characterOrder)[i]]->IsAlive())
                {
                    (*characters)[(*characterOrder)[i]]->MoveToCoordDouble(zoomedChracterPos[j]);
                    (*characters)[(*characterOrder)[i]]->sortingLayer = SortingLayers::Popup;
                    j++;
                }
            }
        }
        if (range[0] == 3) {
            (*characters)[currentCharacter]->MoveToCoordDouble(zoomedContainerPos[0]);
            (*characters)[currentCharacter]->sortingLayer = SortingLayers::Popup;
            int j = 0;
            for (int i = 0; i < 4; i++)
            {
                if (range[5 + i] == 1 && (*monsters)[(monsterOrder[i])]->IsAlive())
                {
                    (*monsters)[monsterOrder[i]]->MoveToCoordDouble(zoomedContainerPos[j + 4]);
                    (*monsters)[monsterOrder[i]]->sortingLayer = SortingLayers::Popup;
                    j++;
                }
            }
        }

        views[1]->setRotation(2.f);
    }
    else
    {
        std::vector<short> range = (*monsters)[currentMonster]->GetSkillRange(monsterTargetInfo[2]-1);
        if (range[0] == 1) {
            (*monsters)[currentMonster]->MoveToCoordDouble(zoomedContainerPos[4]);
            (*monsters)[currentMonster]->sortingLayer = SortingLayers::Popup;
            (*characters)[monsterTargetInfo[1]]->MoveToCoordDouble(zoomedContainerPos[0]);
            (*characters)[monsterTargetInfo[1]]->sortingLayer = SortingLayers::Popup;
        }
        if (range[0] == 3) {
            (*monsters)[currentMonster]->MoveToCoordDouble(zoomedContainerPos[4]);
            (*monsters)[currentMonster]->sortingLayer = SortingLayers::Popup;
            int j = 0;
            for (int i = 0; i < 4; i++)
            {
                if (range[5 + i] == 1 && (*monsters)[(monsterOrder[i])]->IsAlive())
                {
                    (*characters)[(*characterOrder)[i]]->MoveToCoordDouble(zoomedContainerPos[j]);
                    (*characters)[(*characterOrder)[i]]->sortingLayer = SortingLayers::Popup;
                    j++;
                }
            }
        }
        views[1]->setRotation(-2.f);
    }
    elapsedZoom = 0;
    views[1]->setCenter(views[0]->getCenter());
    moveCamera = false;
    shadow->SetToVisible();
}

void BattleManager::ResetView()
{
 
    while (!zoomSnapshot.empty())
    {
        views[1]->zoom(1/zoomSnapshot.front());
        zoomSnapshot.pop();
    }



}


