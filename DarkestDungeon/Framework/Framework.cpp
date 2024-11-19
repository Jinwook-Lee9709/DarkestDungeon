#include "stdafx.h"
#include "SpriteGo.h"


void Framework::Init(int width, int height, const std::string& name)
{
	window.create(sf::VideoMode(width, height), name, sf::Style::Fullscreen);
    RES_TABLE_MGR.Init();
    DATATABLE_MGR.Init();
    SCENE_MGR.Init();
    InputManager::Init();
    Utils::Init();

}

void Framework::Do()
{

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        realDeltaTime = deltaTime;
        deltaTime *= timeScale;

        realTime += realDeltaTime;
        time += deltaTime;
        
        frameTimer += realDeltaTime;
        InputManager::Clear();
        //Evenet Loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            InputManager::UpdateEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        InputManager::Update(deltaTime);

        //Update
        if (InputManager::GetKeyDown(sf::Keyboard::H))
        {
            Variables::isDrawHitBox = !Variables::isDrawHitBox;
        }
        SCENE_MGR.Update(deltaTime);
        SCENE_MGR.LateUpdate(deltaTime);
        //Draw

        if (frameTimer > 1.f / frameRate) {
            window.clear();
            SCENE_MGR.Draw(window);
            frameTimer = 0.f;
            window.display();
        }


    }
}

void Framework::Release()
{
    SCENE_MGR.Release();
    DATATABLE_MGR.Release();
}
