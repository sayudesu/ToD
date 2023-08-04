#include "ObstacleManager.h"
#include "../../Object/Obstacle/ObstacleNormalShot.h"

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
	m_pObstacle.push_back(std::make_shared<ObstacleNormalShot>(pos));
	m_pObstacle[m_count]->Init();
}

void ObstacleManager::Update()
{
	for (auto& obstacle : m_pObstacle)
	{
		obstacle->Update();
	}

	auto enemies = std::remove_if(m_pObstacle.begin(), m_pObstacle.end(), [](const std::shared_ptr<ObstacleBase>& enemies)
		{
			return enemies->GetErase();
		});
	m_pObstacle.erase(enemies, m_pObstacle.end());
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
