#include "scenes/GameScene.h"

bool GameScene::Init()
{
    LOG_CORE_INFO("GameScene::Init");
    
    // Player
    m_Player = Instantiate<Player>();

    

    return true;
}

void GameScene::Update()
{
    //LOG_CORE_INFO("GameScene::Update");
    m_Player->Update();
}

void GameScene::Render() const
{
    //LOG_CORE_INFO("GameScene::Render");
}

void GameScene::Term()
{
    LOG_CORE_INFO("GameScene::Term");
}