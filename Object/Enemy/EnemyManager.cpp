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
		m_pEnemyNormal.push_back(std::make_shared<EnemyNormal>());
		m_pEnemyNormal[i]->Init();
	}
}

void EnemyManager::Update()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->Update();
	}
}

void EnemyManager::Draw()
{
	for (auto& enemyNormal : m_pEnemyNormal)
	{
		enemyNormal->Draw();
	}
}

VECTOR EnemyManager::SetNormalPos(int num)
{
	for (int i = 0; i < num; i++)
	{
		return m_pEnemyNormal[i]->SetPos();
	}
}

int EnemyManager::SetNormalNum()
{
	for (auto& size : m_pEnemyNormal)
	{
		return m_pEnemyNormal.size();
	}
}
