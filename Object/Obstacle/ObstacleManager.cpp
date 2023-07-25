#include "ObstacleManager.h"
#include "Object/Obstacle/ObstacleShot.h"

ObstacleManager::ObstacleManager():
	m_count(-1)
{
}

ObstacleManager::~ObstacleManager()
{
}

void ObstacleManager::Init()
{
}

void ObstacleManager::End()
{
}

void ObstacleManager::Create(VECTOR pos)
{
	m_count++;
	m_pObstacle.push_back(std::make_shared<ObstacleShot>(pos));
	m_pObstacle[m_count]->Init();
}

void ObstacleManager::Update()
{
	for (auto& obstacle : m_pObstacle)
	{
		obstacle->Update();
	}
}

void ObstacleManager::Draw()
{
	for (auto& obstacle : m_pObstacle)
	{
		obstacle->Draw();
	}
}

void ObstacleManager::GetTarGetPos(VECTOR pos)
{
	for (auto& obstacle : m_pObstacle)
	{
		obstacle->GetTarGetPos(pos);
	}
}
