#include "EnemyManager.h"
#include "EnemyNormal.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
}

void EnemyManager::End()
{
}

void EnemyManager::Create(int num)
{
	for (int i = 0; i < num; i++)
	{
		m_pEnemy.push_back(std::make_shared<EnemyNormal>());
		m_pEnemy[i]->Init();
	}
}

void EnemyManager::Update()
{
	for (auto& enemyNormal : m_pEnemy)
	{
		enemyNormal->Update();
	}
}

void EnemyManager::Draw()
{
	for (auto& enemyNormal : m_pEnemy)
	{
		enemyNormal->Draw();
	}
}
