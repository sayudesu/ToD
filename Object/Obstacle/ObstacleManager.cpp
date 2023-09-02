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
}

void ObstacleManager::Draw()
{
	for (auto& obstacle : m_pObstacle)
	{
		obstacle->Draw();
	}
}

void ObstacleManager::SetTarGetPos(VECTOR pos)
{
	for (auto& obstacle : m_pObstacle)
	{
		obstacle->SetTarGetPos(pos);
	}
}

VECTOR ObstacleManager::GetPos(int num)
{
	return m_pObstacle[num]->GetPos();
}

std::vector<std::vector<CollData>> ObstacleManager::GetCollDatas()
{
	std::vector<std::vector<CollData>> collData{};

	// ƒf[ƒ^‚ð•Û‘¶
	for (auto& obstacle : m_pObstacle)
	{
		collData.push_back(obstacle->GetCollDatas());
	}

	return collData;
}

int ObstacleManager::GetNormalNum()
{
	return static_cast<int>(m_pObstacle.size());
}
